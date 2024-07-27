//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2024 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <array>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// Class to manage the memory to be used for handler-based custom allocation.
// It contains a single block of memory which may be returned for allocation
// requests. If the memory is in use when an allocation request is made, the
// allocator delegates allocation to the global heap.
//Chinese ：类用于管理用于基于处理程序的自定义分配的内存。
//它包含一个内存块，可以用于分配请求。
//如果在分配请求时内存正在使用，则分配器将分配委托给全局堆。

class handler_memory
{
public:
  handler_memory()
    : in_use_(false)
  {
  }
//Chinese ：删除拷贝构造函数和赋值运算符
  handler_memory(const handler_memory&) = delete;//禁止对象拷贝
  handler_memory& operator=(const handler_memory&) = delete;//禁止对象赋值

  void* allocate(std::size_t size)
  {
    if (!in_use_ && size < sizeof(storage_))
    {
      in_use_ = true;
      return &storage_;
    }
    else
    {
      return ::operator new(size);
    }
  }

  void deallocate(void* pointer)
  {
    if (pointer == &storage_)
    {
      in_use_ = false;
    }
    else
    {
      ::operator delete(pointer);
    }
  }

private:
  // Storage space used for handler-based custom memory allocation.
  //用于基于处理程序的自定义内存分配的存储空间。
  //这里的typename关键字用于告诉编译器std::aligned_storage<1024>::type是一个类型

  typename std::aligned_storage<1024>::type storage_;

  // Whether the handler-based custom allocation storage has been used.
  bool in_use_;
};

// The allocator to be associated with the handler objects. This allocator only
// needs to satisfy the C++11 minimal allocator requirements.
//Chinese ：与处理程序对象关联的分配器。此分配器只需要满足C++11最小分配器要求。
template <typename T>
class handler_allocator
{
public:
  using value_type = T;

  explicit handler_allocator(handler_memory& mem)
    : memory_(mem)
  {
  }

  template <typename U>
  handler_allocator(const handler_allocator<U>& other) noexcept
    : memory_(other.memory_)
  {
  }

  bool operator==(const handler_allocator& other) const noexcept
  {
    return &memory_ == &other.memory_;
  }

  bool operator!=(const handler_allocator& other) const noexcept
  {
    return &memory_ != &other.memory_;
  }

  T* allocate(std::size_t n) const
  {
    return static_cast<T*>(memory_.allocate(sizeof(T) * n));
  }

  void deallocate(T* p, std::size_t /*n*/) const
  {
    return memory_.deallocate(p);
  }

private:
//Chinese ：声明handler_memory为handler_allocator的友元类
//template <typename> 
  template <typename> friend class handler_allocator;

  // The underlying memory.
  handler_memory& memory_;
};

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket socket)
    : socket_(std::move(socket))
  {
  }

  void start()
  {
    do_read();
  }

private:
  void do_read()
  {
    auto self(shared_from_this());
    //boost::asio::async_read_some 用于异步读取数据 通过socket_套接字
    socket_.async_read_some(boost::asio::buffer(data_),
    //boost::asio::bind_allocator 用于绑定自定义的内存分配器
        boost::asio::bind_allocator(
          handler_allocator<int>(handler_memory_),
          [this, self](boost::system::error_code ec, std::size_t length)
          {
            if (!ec)
            {
              do_write(length);
            }
          }));
  }

  void do_write(std::size_t length)
  {
    auto self(shared_from_this());//获取当前对象的shared_ptr
    //self 为当前对象的shared_ptr 用于保证当前对象在异步操作完成之前不被销毁
    //boost::asio::async_write 用于异步写入数据 通过socket_套接字
    boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
        boost::asio::bind_allocator(
          handler_allocator<int>(handler_memory_),
          [this, self](boost::system::error_code ec, std::size_t /*length*/)
          {
            if (!ec)
            {
              do_read();
            }
          }));
  }

  // The socket used to communicate with the client.
  //client通信的套接字。
  tcp::socket socket_;

  // Buffer used to store data received from the client.
  //用于存储从客户端接收的数据的缓冲区。
  std::array<char, 1024> data_;

  // The memory to use for handler-based custom memory allocation.
  //用于基于处理程序的自定义内存分配的内存。
  handler_memory handler_memory_;
};

class server
{
public:
  server(boost::asio::io_context& io_context, short port)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
  {
    do_accept();
  }

private:
  void do_accept()
  {
    acceptor_.async_accept(
        [this](boost::system::error_code ec, tcp::socket socket)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket))->start();
          }

          do_accept();
        });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Usage: server <port>\n";
      return 1;
    }

    boost::asio::io_context io_context;
    server s(io_context, std::atoi(argv[1]));
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}