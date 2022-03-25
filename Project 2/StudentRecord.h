#pragma once
#include <iostream>
#include <string>
using std::string;

struct StudentRecord
{
    unsigned int ID;
    string name;
    unsigned short age;

    StudentRecord(const unsigned int ID, const string name, const unsigned short age);
    void Display() const;
};