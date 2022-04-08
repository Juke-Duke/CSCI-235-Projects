#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <climits>
using std::string, std::vector;

enum class ErrorType
{
    ILLEGAL_INPUT,
    ILLEGAL_COMMAND,
    ILLEGAL_FIELD,
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

    bool IsSeperator(const char& arg) const;
    bool IsValidOperator(const char& operation) const;
    bool IsValidCommand(const string& arg) const;
    bool IsValidField(const string& arg) const;
    bool IsNumber(const string& num) const;
    bool UIntOverflow(const string& num) const;
    bool UShortOverflow(const string& num) const;
    void ErrorMessage(const ErrorType error) const;

    vector<string> ValidateParse(const vector<string>& parsedCommand) const;

public:
    vector<string> operator()(const string& commandInput) const;
};
