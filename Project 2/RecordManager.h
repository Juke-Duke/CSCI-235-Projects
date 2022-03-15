#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StudentRecord.h"
using std::string, std::vector, std::fstream;

class RecordManager
{
private:
    vector<StudentRecord*> students;

    void AssembleStudents();

    bool ADD(unsigned int ID, string name, unsigned short age);
    bool FIND(unsigned int ID, char relation);
    bool FIND(string name, char relation);
    bool FIND(unsigned short age, char relation);
    bool REMOVE(unsigned int ID, char relation);
    bool REMOVE(string name, char relation);
    bool REMOVE(unsigned short age, char relation);
    bool STOP();
    
    void UpdateRecords();

public:
    vector<StudentRecord> GetStudents();
    bool Process(vector<string>& parsedCommand);
};