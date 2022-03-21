#include "CommandParser.h"

bool CommandParser::IsSeperator(char& arg) 
    { return arg == ' ' || arg == '\t'; }

bool CommandParser::IsValidOperator(char& operation)
    { return operation == '=' || operation == '>' || operation == '<'; }

bool CommandParser::IsValidCommand(string& arg)
{
    for (string command : commands)
        if (arg == command)
            return true;
    
    return false;
}

bool CommandParser::IsValidField(string& arg)
{
    for (string field : fields)
        if (arg == field)
            return true;
    
    return false;
}

bool CommandParser::UIntOverflow(string& num)
{
    string uIntMax = std::to_string(UINT_MAX);
    if (num.size() > uIntMax.size())
    {
        ErrorMessage(ErrorType::ID_OVERFLOW);
        return true;
    }
    else if (num.size() == uIntMax.size())
    {
        for (int j = 0; j < num.size(); ++j)
            if (num[j] - '0' > uIntMax[j] - '0')
            {
                ErrorMessage(ErrorType::ID_OVERFLOW);
                return true;
            }
    }

    return false;
}

bool CommandParser::UShortOverflow(string& num)
{
    string uShortMax = std::to_string(USHRT_MAX);
    if (num.size() > uShortMax.size())
    {
        ErrorMessage(ErrorType::AGE_OVERFLOW);
        return true;
    }
    else if (num.size() == uShortMax.size())
    {
        for (int j = 0; j < num.size(); ++j)
            if (num[j] - '0' > uShortMax[j] - '0')
            {
                ErrorMessage(ErrorType::AGE_OVERFLOW);
                return true;
            }
    }

    return false;
}

void CommandParser::ErrorMessage(ErrorType error)
{
    switch(error)
    {
    case ErrorType::ILLEGAL_INPUT :
        std::cout << "ERROR: The given input is not written correctly." << std::endl;
        break;
    
    case ErrorType::ILLEGAL_COMMAND :
        std::cout << "ERROR: The given command is not available." << std::endl;
        break;

    case ErrorType::ILLEGAL_FIELD :
        std::cout << "ERROR: The given field is not available." << std::endl;
        break;
    
    case ErrorType::INVALID_NAME :
        std::cout << "ERROR: The given name is not valid." << std::endl;
        break;
    
    case ErrorType::ID_OVERFLOW :
        std::cout << "ERROR: The given ID value is too large." << std::endl;
        break;
    
    case ErrorType::AGE_OVERFLOW :
        std::cout << "The given age value is too large." << std::endl;
        break;
    
    case ErrorType::INVALID_OPERATION :
        std::cout  << "The given operation is invalid and cannot be executed." << std::endl;
        break;
    }
}

vector<string> CommandParser::operator()(string commandInput)
{
    vector<string> parsedCommand;
    string arg;
    int argPos = 0;

    for (char& c : commandInput)
    {
        
    }



    return parsedCommand;
}