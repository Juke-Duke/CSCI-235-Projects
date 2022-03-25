#include "StudentRecord.h"

StudentRecord::StudentRecord(const unsigned int ID, const string name, const unsigned short age) : 
    ID(ID), name(name), age(age) {}

void StudentRecord::Display() const { std::cout << ID << ' ' << name << ' ' << age << '\n'; }