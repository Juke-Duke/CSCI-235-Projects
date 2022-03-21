#include "StudentRecord.h"

StudentRecord::StudentRecord(unsigned int ID, string name, unsigned short age) : 
    ID(ID), name(name), age(age) {}

void StudentRecord::Print() { std::cout << ID << ' ' << name << ' ' << age << '\n'; }