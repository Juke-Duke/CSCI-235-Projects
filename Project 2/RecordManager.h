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

    void ADD(unsigned int ID, string name, unsigned short age);
    void FIND(unsigned int ID, char relation);
    void FIND(string name);
    void FIND(unsigned short age, char relation);
    void REMOVE(unsigned int ID, char relation);
    void REMOVE(string name);
    void REMOVE(unsigned short age, char relation);
    void STOP();

public:
    RecordManager();
    vector<StudentRecord> GetStudents() const;
    bool Process(vector<string>& parsedCommand);
};