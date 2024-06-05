//
//  ex12_33.h
//  Exercise 12.33
//
//  Created by pezy on 1/1/15.
//  Copyright (c) 2015 pezy. All rights reserved.
//
//  In Chapter 15 we’ll extend our query system and will need some additional members
//  in the QueryResult class.
//  Add members named [begin] and [end] that return iterators into the set of line numbers
//  returned by a given query, and a member named [get_file] that
//  returns a shared_ptr to the file in the QueryResult object.

#ifndef CP5_ex12_33_h
#define CP5_ex12_33_h

#include "ex12_22.h"
using std::shared_ptr;

#include <iostream>
#include <fstream>
#include <map>
#include <set>

class QueryResult;
class TextQuery {
public:
    TextQuery(std::ifstream &);
    QueryResult query(const string&) const;
private:
    shared_ptr<StrBlob> input;
    std::map<string, shared_ptr<std::set<StrBlob::size_type>>> result;
};

class QueryResult {
public:
    using ResultIter = std::set<StrBlob::size_type>::iterator;
    friend std::ostream& print(std::ostream &, const QueryResult&);
public:
    QueryResult(const string &s, shared_ptr<std::set<StrBlob::size_type>> set, shared_ptr<StrBlob> v) : word(s), nos(set), input(v) {}
    ResultIter begin() const { return nos->begin(); }
    ResultIter end() const { return nos->end(); }
    shared_ptr<StrBlob> get_file() const { return input; }
private:
    string word;
    shared_ptr<std::set<StrBlob::size_type>> nos;
    shared_ptr<StrBlob> input;
};

std::ostream& print(std::ostream &, const QueryResult&);

#endif
