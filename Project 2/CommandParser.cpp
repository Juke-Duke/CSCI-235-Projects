#include "CommandParser.h"

bool CommandParser::IsSperator(char& arg) 
    { return arg == ' ' || arg == '\t'; }

bool CommandParser::IsValidCommand(string& arg)
{
    for (string& command : commands)
        if (arg == command)
            return true;
    
    return false;
}

void CommandParser::ErrorMessage(ErrorType error)
{
    switch(error)
    {
    case ErrorType::ILLEGAL_INPUT :
        std::cout << "The given input is not written correctly." << std::endl;
        break;
    
    case ErrorType::ILLEGAL_COMMAND :
        std::cout << "The given command is not available." << std::endl;
        break;
    
    case ErrorType::ILLEGAL_NAME :
        std::cout << "The given name is not valid." << std::endl;
        break;
    
    case ErrorType::ID_OVERFLOW :
        std::cout << "The given ID value is too large." << std::endl;
        break;
    
    case ErrorType::AGE_OVERFLOW :
        std::cout << "The given age value is too large." << std::endl;
        break;
    }
}

vector<string> CommandParser::operator()(string& commandInput)
{
    vector<string> parsedCommand;
    string arg;
    int argPos = 1, i = 0;

    // First loop for command keyword
    while (i < commandInput.size())
    {
        if (!IsSperator(commandInput[i]) || !isalpha(commandInput[i]))
        {
            ErrorMessage(ErrorType::ILLEGAL_INPUT);
            return {};
        }
        else if (IsSperator(commandInput[i]) && arg.size() != 0)
        {
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

    if (parsedCommand[0] == "ADD")
    {
        bool quoteOn = false;
        while (i < commandInput.size())
        {
            if (argPos == 1 || argPos == 3)
            {
                if (!IsSperator(commandInput[i]) || !isdigit(commandInput[i]))
                {
                    ErrorMessage(ErrorType::ILLEGAL_INPUT);
                    return {};
                }
                else if (IsSperator(commandInput[i]) && arg.size() != 0)
                {
                    if (argPos == 1)
                    {
                        string uIntMax = std::to_string(UINT_MAX);
                        if (arg.size() > uIntMax.size())
                        {
                            ErrorMessage(ErrorType::ID_OVERFLOW);
                            return {};
                        }
                        else if (arg.size() == uIntMax.size())
                        {
                            for (int j = 0; j < arg.size(); ++j)
                                if (arg[j] - '0' > uIntMax[j] - '0')
                                {
                                    ErrorMessage(ErrorType::ID_OVERFLOW);
                                    return {};
                                }
                        }
                    }
                    else if (argPos == 3)
                    {
                        string uShortMax = std::to_string(UINT_MAX);
                        if (arg.size() > uShortMax.size())
                        {
                            ErrorMessage(ErrorType::AGE_OVERFLOW);
                            return {};
                        }
                        else if (arg.size() == uShortMax.size())
                        {
                            for (int j = 0; j < arg.size(); ++j)
                                if (arg[j] - '0' > uShortMax[j] - '0')
                                {
                                    ErrorMessage(ErrorType::AGE_OVERFLOW);
                                    return {};
                                }
                        }
                    }

                    parsedCommand.push_back(arg);
                    arg = "";
                    ++argPos;
                }

                if (isdigit(commandInput[i]))
                    arg += commandInput[i];
            }
            else if (argPos == 2)
            {
                if (arg.size() == 0 && (!IsSperator(commandInput[i]) || !isalpha(commandInput[i]) 
                || commandInput[i] != '\"'))
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
                else if (IsSperator(commandInput[i]) && arg.size() != 0)
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
    else if (parsedCommand[0] == "FIND" || parsedCommand[0] == "REMOVE")
    {
        while (i < commandInput.size())
        {
            
        }
    }


}