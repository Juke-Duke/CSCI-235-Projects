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

bool CommandParser::ShortOverflow(string& num)
{
    string uShortMax = std::to_string(UINT_MAX);
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
    int i = 0;

    while (i < commandInput.size())
    {
        if (!IsSeperator(commandInput[i]) && !isalpha(commandInput[i]))
        {
            ErrorMessage(ErrorType::ILLEGAL_INPUT);
            return {};
        }
        else if (i == commandInput.size() - 1 || (IsSeperator(commandInput[i]) && arg.size() != 0))
        {
            if (i == commandInput.size() - 1 && isalpha(commandInput[i]))
                arg += commandInput[i];

            if (!IsValidCommand(arg))
            {
                ErrorMessage(ErrorType::ILLEGAL_COMMAND);
                return {};
            }
            
            parsedCommand.push_back(arg);
            arg = "";
            ++i;
            break;
        }

        if (isalpha(commandInput[i]))
            arg += commandInput[i];
        ++i;
    }

    int argPos = 1;
    if (parsedCommand[0] == "ADD")
    {
        bool quoteOn = false;
        while (i < commandInput.size())
        {
            if (argPos == 1 || argPos == 3)
            {
                if (!IsSeperator(commandInput[i]) && !isdigit(commandInput[i]))
                {
                    ErrorMessage(ErrorType::ILLEGAL_INPUT);
                    return {};
                }
                else if (IsSeperator(commandInput[i]) && arg.size() != 0)
                {
                    if (argPos == 1 && UIntOverflow(arg))
                        return {};
                    else if (argPos == 3 && ShortOverflow(arg))
                        return {};
                    
                    parsedCommand.push_back(arg);
                    arg = "";
                    ++argPos;
                }

                if (isdigit(commandInput[i]))
                    arg += commandInput[i];
                
                if (isdigit(commandInput[i]) == commandInput.size() - 1)
                    parsedCommand.push_back(arg);
            }
            else if (argPos == 2)
            {
                if (arg.size() == 0 && !IsSeperator(commandInput[i]) && !isalpha(commandInput[i]) && commandInput[i] != '\"')
                {
                    ErrorMessage(ErrorType::ILLEGAL_INPUT);
                    return {};
                }
                else if (commandInput[i] == '\"')
                {
                    if (arg.size() == 0)
                    {
                        quoteOn = true;
                        ++i;
                        continue;
                    }
                    else
                    {
                        quoteOn = false;
                        parsedCommand.push_back(arg);
                        arg = "";
                        ++argPos;
                    }
                }
                else if (IsSeperator(commandInput[i]) && arg.size() != 0)
                {
                    if (!quoteOn)
                    {
                        parsedCommand.push_back(arg);
                        arg = "";
                        ++argPos;
                    }
                    else
                    {
                        arg += commandInput[i];
                        ++i;
                        continue;
                    }
                }

                if (!isdigit(commandInput[i]))
                    arg += commandInput[i];
            }

            ++i;
        }
    }

    return parsedCommand;
}