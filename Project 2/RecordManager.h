#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StudentRecord.h"
using std::string, std::vector;

class RecordManager
{
private:
    vector<StudentRecord> students;

    void AssembleStudents();

    void ADD(const unsigned int& ID, const string& name, const unsigned short& age);
    void FIND(const unsigned int& ID, const char& relation);
    void FIND(const string& name, const char& relation);
    void FIND(const unsigned short& age, const char& relation);
    void REMOVE(const unsigned int& ID, const char& relation);
    void REMOVE(const string& name, const char& relation);
    void REMOVE(const unsigned short& age, const char& relation);
    void STOP();

public:
    RecordManager();
    bool Process(vector<string> parsedCommand);
};