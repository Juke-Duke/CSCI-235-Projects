#include "StudentRecord.h"

StudentRecord::StudentRecord(const unsigned int ID, const string name, const unsigned short age) : 
    ID(ID), name(name), age(age) {}

void StudentRecord::Display() const { std::cout << std::setw(10); std::cout << ID << std::setw(51) << name << std::setw(6) << age << '\n'; }