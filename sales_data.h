#pragma once
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include<string>
class Sales_data
{
private:
    /* data */
    std::string bookNo;
    unsigned units_sold;
    double revenue;
public:
    Sales_data(/* args */)=default;
    Sales_data(const std::string &s,unsigned n,double p):bookNo(s),units_sold(n),revenue(p*n){}
    ~Sales_data();
    explicit Sales_data(const std::string &s):bookNo(s){}
    explicit Sales_data(std::istream&);
};

Sales_data::Sales_data(/* args */)
{
}

Sales_data::~Sales_data()
{
}

#endif //SALES_DATA_H
