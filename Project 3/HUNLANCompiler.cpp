#include "HUNLANCompiler.h"

bool HUNLANCompiler::IsSeperator(const char& token) const { return token == ' ' || token == '\t'; }

bool HUNLANCompiler::IsValidOperator(const char& operation) const { return operation == '=' || operation == '+' || operation == '-' || operation == '*'; }

bool HUNLANCompiler::IsValidCommand(const string& token) const { return token == "NUMBER" || token == "STRING" || token == "PRINT"; }

bool HUNLANCompiler::IsNumber(const string& num) const
{
    for (char digit : num)
        if (!isdigit(digit))
            return false;
    
    return true;
}

unsigned long HUNLANCompiler::NumberValue(const string& numName) const
{
    for (Variable<unsigned long> num : numbers)
    {
        if (num.name == numName)
            return num.value;

        return -1;
    }
}

string HUNLANCompiler::StringValue(const string& strName) const
{
    for (Variable<string> str : strings)
    {
        if (str.name == strName)
            return str.value;

        return "";
    }
}

void HUNLANCompiler::ErrorMessage(const ErrorType error, const size_t& lineNumber) const
{
    switch (error)
    {
        case ErrorType::ILLEGAL_INTIALIZATION:
            std::cout << "Line " << lineNumber << ": ERROR: Incorrect initialization of variable." << std::endl;
            break;

        case ErrorType::ILLEGAL_PRINT:
            std::cout << "Line " << lineNumber << ": ERROR: The print statement is illegal." << lineNumber << std::endl;
            break;

        case ErrorType::ILLEGAL_VARIABLE_NAME:
            std::cout << "Line " << lineNumber << ": ERROR: Illegal variable name." << std::endl;
            break;

        case ErrorType::ILLEAL_REDEFINITON:
            std::cout << "Line " << lineNumber << ": ERROR: Redefinition of existing variable is illegal." << std::endl;
            break;
    }
}

vector<string> HUNLANCompiler::operator()(const string& line, size_t& lineNumber) const
{
    vector<string> parsedLine;
    string token;
    bool inQuotes = false;
    int quoteCount = 0;

    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == '#')
        {
            if (inQuotes)
                token += line[i];
            else
                break;
        }
        else if (line[i] == '"' && quoteCount < 2)
        {
            if (inQuotes)
            {
                token += line[i];
                parsedLine.push_back(token);
                token.clear();
            }

            inQuotes = !inQuotes;
            token += line[i];
            ++quoteCount;
        }
        else if  (line[i] == '"' && quoteCount >= 2)
        {
            token += line[i];
            parsedLine.push_back(token);
            token.clear();
        }
        else if (inQuotes)
            token += line[i];
        else if (IsSeperator(line[i]))
        {
            if (!token.empty())
                parsedLine.push_back(token);
            token.clear();
        }
        else if (IsValidOperator(line[i]))
        {
            if (!token.empty())
            {
                parsedLine.push_back(token);
                token.clear();
            }
            
            token += line[i];
            parsedLine.push_back(token);
            token.clear();
        }
        else
            token += line[i];
    }

    if (!token.empty())
        parsedLine.push_back(token);
    
    return ValidateParse(parsedLine, lineNumber);
}

vector<string> HUNLANCompiler::ValidateParse(const vector<string>& parsedLine, size_t& lineNumber) const
{
    if (parsedLine.empty())
    {
        return {};
    }
    else if (IsValidCommand(parsedLine[0]))
    {
        if ((parsedLine[0] == "NUMBER" || parsedLine[0] == "STRING") && parsedLine.size() != 3)
        {
            ErrorMessage(ErrorType::ILLEGAL_INTIALIZATION, lineNumber);
            return {};
        }
        else if (parsedLine[0] == "PRINT" && parsedLine.size() != 2)
        {
            ErrorMessage(ErrorType::ILLEGAL_PRINT, lineNumber);
            return{};
        }
        else if (!isalpha(parsedLine[1][0]))
        {
            ErrorMessage(ErrorType::ILLEGAL_VARIABLE_NAME, lineNumber);
            return {};
        }
        else if ((parsedLine[0] == "NUMBER" && NumberValue(parsedLine[1]) != -1) || (parsedLine[0] == "STRING" && StringValue(parsedLine[1]) != ""))
        {
            ErrorMessage(ErrorType::ILLEAL_REDEFINITON, lineNumber);
            return {};
        }
    }
    else if (parsedLine[1][0] == '=')
    {
        if (NumberValue(parsedLine[0]) == -1 && StringValue(parsedLine[0]) == "")
        {
            ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber);
            return {};
        }
        else if (NumberValue(parsedLine[0]) != -1 && (!IsNumber(parsedLine[2]) || NumberValue(parsedLine[2]) != -1))
        {
            ErrorMessage(ErrorType::ILLEGAL_INTIALIZATION, lineNumber);
            return {};
        }
        else if (StringValue(parsedLine[0]) != "" && ((parsedLine[2][0] != '"' && parsedLine[2][parsedLine[2].size() - 1] != '"') || StringValue(parsedLine[2]) != ""))
        {
            ErrorMessage(ErrorType::ILLEGAL_INTIALIZATION, lineNumber);
            return {};
        }
    }
}