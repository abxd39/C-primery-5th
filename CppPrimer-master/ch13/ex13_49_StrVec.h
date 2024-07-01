#ifndef CP5_STRVEC_H_
#define CP5_STRVEC_H_

#include <memory>
#include <string>
#include <initializer_list>

#ifndef _MSC_VER
#define NOEXCEPT noexcept
#else
#define NOEXCEPT
#endif

class StrVec
{
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	//拷贝赋值运算符
	StrVec& operator=(const StrVec&);
	StrVec(StrVec&&) NOEXCEPT;
	//移动赋值运算符
	StrVec& operator=(StrVec&&) NOEXCEPT;
	//第三种赋值运算符
	StrVec &operator=(std::initializer_list<std::string>);
	~StrVec();

	void push_back(const std::string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }

	std::string& at(size_t pos) { return *(elements + pos); }
	const std::string& at(size_t pos) const { return *(elements + pos); }

	void reserve(size_t new_cap);
	void resize(size_t count);
	void resize(size_t count, const std::string&);

private:
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void chk_n_alloc() { if (size() == capacity()) reallocate(); }
	void reallocate();
	void alloc_n_move(size_t new_cap);
	void range_initialize(const std::string*, const std::string*);

private:
	std::string *elements;
	std::string *first_free;
	std::string *cap;
	std::allocator<std::string> alloc;
};

#endif

