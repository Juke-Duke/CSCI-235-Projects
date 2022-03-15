#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
using std::string, std::vector;

enum class ErrorType
{
    ILLEGAL_INPUT,
    ILLEGAL_COMMAND,
    ILLEGAL_NAME,
    ID_OVERFLOW,
    AGE_OVERFLOW,
    MISSING_FIELDS,
    EXCESS_FIELDS,
};

class CommandParser
{
private:
    string commands[4] = {"ADD", "FIND", "REMOVE", "STOP"};
    string fields[3] = {"id", "name", "age"};
    bool IsSperator(char& arg);
    bool IsValidCommand(string& arg);
    bool IsValidField(string& arg);
    void ErrorMessage(ErrorType error);

public:
    vector<string> operator()(string& commandInput);
};