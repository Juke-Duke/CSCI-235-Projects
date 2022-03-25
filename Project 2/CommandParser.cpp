#include "CommandParser.h"

bool CommandParser::IsSeperator(const char& arg) const
    { return arg == ' ' || arg == '\t'; }

bool CommandParser::IsValidOperator(const char& operation) const
    { return operation == '=' || operation == '>' || operation == '<'; }

bool CommandParser::IsValidCommand(const string& arg) const
{
    for (string command : commands)
        if (arg == command)
            return true;
    
    return false;
}

bool CommandParser::IsValidField(const string& arg) const
{
    for (string field : fields)
        if (arg == field)
            return true;
    
    return false;
}

bool CommandParser::IsNumber(const string& num) const
{
    for (char digit : num)
        if (!isdigit(digit))
            return false;
    
    return true;
}

bool CommandParser::UIntOverflow(const string& num) const
{
    string uIntMax = std::to_string(UINT_MAX);
    if (num.size() > uIntMax.size())
        return true;
    else if (num.size() == uIntMax.size())
    {
        for (int j = 0; j < num.size(); ++j)
            if (num[j] - '0' > uIntMax[j] - '0')
                return true;
    }

    return false;
}

bool CommandParser::UShortOverflow(const string& num) const
{
    string uShortMax = std::to_string(USHRT_MAX);
    if (num.size() > uShortMax.size())
        return true;
    else if (num.size() == uShortMax.size())
    {
        for (int j = 0; j < num.size(); ++j)
            if (num[j] - '0' > uShortMax[j] - '0')
                return true;
    }

    return false;
}

void CommandParser::ErrorMessage(const ErrorType error) const
{
    switch(error)
    {
    case ErrorType::ILLEGAL_INPUT :
        std::cout << "ERROR: The given input is invalid." << std::endl;
        break;
    
    case ErrorType::ILLEGAL_COMMAND :
        std::cout << "ERROR: The given command is not available." << std::endl;
        break;

    case ErrorType::ILLEGAL_FIELD :
        std::cout << "ERROR: The given field is not available." << std::endl;
        break;
    
    case ErrorType::ID_OVERFLOW :
        std::cout << "ERROR: The given ID value is not a valid number or is too large." << std::endl;
        break;
    
    case ErrorType::AGE_OVERFLOW :
        std::cout << "ERROR: The given age value is not a valid number or is too large." << std::endl;
        break;
    
    case ErrorType::INVALID_OPERATION :
        std::cout  << "ERROR: The given operation is invalid and cannot be executed." << std::endl;
        break;
    }
}

vector<string> CommandParser::operator()(const string commandInput) const
{
    vector<string> parsedCommand;
    string arg;
    bool inQuotes = false;

    for (int i = 0; i < commandInput.size(); ++i)
    {
        if (commandInput[i] == '"')
        {
            inQuotes = !inQuotes;
            continue;
        }
        if (inQuotes)
            arg += commandInput[i];
        else if (IsSeperator(commandInput[i]))
        {
            if (!arg.empty())
                parsedCommand.push_back(arg);
            arg.clear();
        }
        else if (IsValidOperator(commandInput[i]))
        {
            if (!arg.empty())
            {
                parsedCommand.push_back(arg);
                arg.clear();
            }
            
            arg += commandInput[i];
            parsedCommand.push_back(arg);
            arg.clear();
        }
        else
            arg += commandInput[i];
    }

    if (!arg.empty())
        parsedCommand.push_back(arg);
        
    return ValidateParse(parsedCommand);
}

vector<string> CommandParser::ValidateParse(const vector<string>& parsedCommand) const
{
    if (parsedCommand.size() == 0 || parsedCommand.size() > 4)
    {
        ErrorMessage(ErrorType::ILLEGAL_INPUT);
        return {};
    }
    else if (!IsValidCommand(parsedCommand[0]))
    {
        ErrorMessage(ErrorType::ILLEGAL_COMMAND);
        return {};
    }    

    if (parsedCommand[0] == "ADD")
    {
        if (parsedCommand.size() != 4)
        {
            ErrorMessage(ErrorType::ILLEGAL_INPUT);
            return {};
        }
        else if (!IsNumber(parsedCommand[1]) || UIntOverflow(parsedCommand[1]))
        {
            ErrorMessage (ErrorType::ID_OVERFLOW);
            return {};
        }
        else if (!IsNumber(parsedCommand[3]) || UShortOverflow(parsedCommand[3]))
        {
            ErrorMessage (ErrorType::AGE_OVERFLOW);
            return {};
        }
    }
    else if (parsedCommand[0] == "FIND" || parsedCommand[0] == "REMOVE")
    {
        if (parsedCommand.size() != 4)
        {
            ErrorMessage(ErrorType::ILLEGAL_INPUT);
            return {};
        }
        else if (!IsValidField(parsedCommand[1]))
        {
            ErrorMessage(ErrorType::ILLEGAL_FIELD);
            return {};
        }
        else if (!IsValidOperator(parsedCommand[2][0]))
        {
            ErrorMessage(ErrorType::INVALID_OPERATION);
            return {};
        }
        if (parsedCommand[1] == "id" && (!IsNumber(parsedCommand[3]) || UIntOverflow(parsedCommand[3])))
        {
            ErrorMessage(ErrorType::ID_OVERFLOW);
            return {};
        }
        else if (parsedCommand[1] == "age" && (!IsNumber(parsedCommand[3]) || UShortOverflow(parsedCommand[3])) )
        {
            ErrorMessage(ErrorType::AGE_OVERFLOW);
            return {};
        }
    }
    else if (parsedCommand[0] == "STOP")
    {
        if (parsedCommand.size() != 1)
        {
            ErrorMessage(ErrorType::ILLEGAL_INPUT);
            return {};
        }
    }

    return parsedCommand;
}
