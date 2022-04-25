#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <unordered_map>
using std::string, std::vector, std::unordered_map;

enum class ErrorType
{
    INVALID_COMMAND,
    EXCESS_TOKENS,
    NUMBER_OVERFLOW,
    ILLEGAL_NUMBER_DECLERATION,
    ILLEGAL_STRING_DECLERATION,
    ILLEGAL_NUMBER_INTIALIZATION,
    ILLEGAL_STRING_INTIALIZATION,
    ILLEGAL_VARIABLE_NAME,
    ILLEGAL_REDEFINITON,
    UNDEFINED_VARIABLE,
    ILLEGAL_ARITHMETIC,
    ILLEGAL_STRING_ARITHMETIC,
    ILLEGAL_PRINT
};

class HUNLANCompiler
{
private:
    unordered_map<string, long long> numbers;
    unordered_map<string, string> strings;

    bool IsSeperator(const char& token) const;
    bool IsEscapeSequence(const char& token) const;
    bool IsValidOperator(const char& operation) const;
    bool IsValidKeyword(const string& token) const;
    bool IsNumber(const string& num) const;
    bool IsValidVariableName(const string& name) const;
    bool IsValidArithmetic(const vector<string>& expression, const size_t& lineNumber) const;
    long long CalculateArithmetic(const vector<string>& expression);
    bool LongLongOverflow(const string& num) const;
    char EscapeCharacter(const char& token) const;
    bool NumberExists(const string& variable) const;
    bool StringExists(const string& variable) const;
    long long NumberValueOf(const string& numName);
    string StringValueOf(const string& strName);
    void ErrorMessage(const ErrorType error, const size_t& lineNumber, const string& undefined = "") const;
    vector<string> ValidateParse(const vector<string>& parsedLine, const size_t& lineNumber) const;

public:
    vector<string> operator()(const string& line, const size_t& lineNumber) const;
    bool Execute(const vector<string>& validLine);
};