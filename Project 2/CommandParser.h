#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
using std::string, std::vector;

enum class ErrorType
{
    ILLEGAL_INPUT,
    ILLEGAL_COMMAND,
    ILLEGAL_FIELD,
    INVALID_NAME,
    ID_OVERFLOW,
    AGE_OVERFLOW,
    INVALID_OPERATION,
    MISSING_FIELDS,
    EXCESS_FIELDS,
};

class CommandParser
{
private:
    const string 
    commands[4] = {"ADD", "FIND", "REMOVE", "STOP"},
    fields[3] = {"id", "name", "age"};

    bool IsSeperator(char& arg);
    bool IsValidOperator(char& operation);
    bool IsValidCommand(string& arg);
    bool IsValidField(string& arg);
    bool UIntOverflow(string& num);
    bool ShortOverflow(string& num);
    void ErrorMessage(ErrorType error);


public:
    vector<string> operator()(string commandInput);
};