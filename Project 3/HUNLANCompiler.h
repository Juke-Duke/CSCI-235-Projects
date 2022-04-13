#include "Variable.cpp"
#include <iostream>
#include <string>
#include <vector>
using std::string, std::vector;

enum class ErrorType
{
    ILLEGAL_INTIALIZATION,
    ILLEGAL_VARIABLE_NAME,
    ILLEAL_REDEFINITON,
    UNDEFINED_VARIABLE,
    ILLEGAL_PRINT,
};

class HUNLANCompiler 
{
private:
    vector<Variable<unsigned long>> numbers;
    vector<Variable<string>> strings;

    unsigned long NumberValue(const string& numName) const;
    string StringValue(const string& strName) const;
    bool IsSeperator(const char& token) const;
    bool IsValidOperator(const char& operation) const;
    bool IsValidCommand(const string& token) const;
    bool IsNumber(const string& num) const;
    void ErrorMessage(const ErrorType error, const size_t& lineNumber) const;

    vector<string> ValidateParse(const vector<string>& parsedLine, size_t& lineNumber) const;
    void ExecuteCommand(const vector<string>& validLine) const;

public:
    vector<string> operator()(const string& line, size_t& lineNumber) const;
};