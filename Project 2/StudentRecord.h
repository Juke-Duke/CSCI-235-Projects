#pragma once
#include <string>
using std::string;

struct StudentRecord
{
    unsigned int ID;
    string name;
    unsigned short age;

    StudentRecord(unsigned int ID, string name, unsigned short age);
};