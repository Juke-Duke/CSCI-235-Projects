#include "HUNLANCompiler.h"

bool HUNLANCompiler::IsSeperator(const char& token) const { return token == ' ' || token == '\t'; }

bool HUNLANCompiler::IsValidOperator(const char& operation) const { return operation == '+' || operation == '-' || operation == '*'; }

bool HUNLANCompiler::IsValidKeyword(const string& token) const { return token == "NUMBER" || token == "STRING" || token == "PRINT"; }

bool HUNLANCompiler::IsEscapeSequence(const char& token) const 
{ 
    return 
    token == '\\' 
    || token == '?'
    || token == 'n'
    || token == 'a'
    || token == 'b'
    || token == 'f'
    || token == 'r'
    || token == 't'
    || token == 'v';
}

char HUNLANCompiler::EscapeCharacter(const char& token) const
{
    switch (token)
    {
    case '\\': return '\\';
    case '?': return '\?';
    case 'n': return '\n';
    case 'a': return '\a';
    case 'b': return '\b';
    case 'f': return '\f';
    case 'r': return '\r';
    case 't': return '\t';
    case 'v': return '\v';
    }

    return ' ';
}

bool HUNLANCompiler::IsNumber(const string& num) const
{
    for (char digit : num)
        if (!isdigit(digit))
            return false;
    
    return true;
}

bool HUNLANCompiler::IsValidVariableName(const string& name) const
{
    if (name[0] != '_' && !isalpha(name[0]))
        return false;

    for (int i = 1; i < name.size(); ++i)
        if (!isalnum(name[i]) && name[i] != '_')
            return false;
    
    return true;
}

bool HUNLANCompiler::IsValidArithmetic(const vector<string>& expression, const size_t& lineNumber) const
{
    for (int i = 2; i < expression.size(); ++i)
    {
        if (i % 2 == 0 && StringExists(expression[i]))
        {
            ErrorMessage(ErrorType::ILLEGAL_STRING_ARITHMETIC, lineNumber);
            return false;
        }
        else if (i % 2 == 0 && IsValidOperator(expression[i][0]) || IsValidOperator(expression[expression.size() - 1][0]))
        {
            ErrorMessage(ErrorType::ILLEGAL_ARITHMETIC, lineNumber);
            return false;
        }
        else if (i % 2 == 0 && (!IsNumber(expression[i]) && !NumberExists(expression[i])))
        {
            ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, expression[i]);
            return false;
        }
        else if (i % 2 == 0 && IsNumber(expression[i]) && LongLongOverflow(expression[i]))
        {
            ErrorMessage(ErrorType::NUMBER_OVERFLOW, lineNumber);
            return false;
        }
        else if (i % 2 == 1 && !IsValidOperator(expression[i][0]))
        {
            ErrorMessage(ErrorType::ILLEGAL_ARITHMETIC, lineNumber);
            return false;
        }
    }
    
    return true;
}

long long HUNLANCompiler::CalculateArithmetic(const vector<string>& expression)
{
    vector<string> cleanedExpression;
    for (int i = 2; i < expression.size(); ++i)
    {
        if (i % 2 == 0)
        {
            long long num = 0;
            if (IsNumber(expression[i]))
                num = std::stoll(expression[i]);
            else
                num = NumberValueOf(expression[i]);
            
            if (expression[i - 1][0] == '*')
            {
                num *= stoll(cleanedExpression[cleanedExpression.size() - 1]);
                cleanedExpression[cleanedExpression.size() - 1] = std::to_string(num);
            }
            else
                cleanedExpression.push_back(std::to_string(num));
        }
        else if (i % 2 == 1)
        {
            if (expression[i][0] == '*')
                continue;
            else
                cleanedExpression.push_back(expression[i]);
        }
    }

    long long result = stoll(cleanedExpression[0]);
    for (int i = 1; i < cleanedExpression.size(); i += 2)
    {
        if (cleanedExpression[i][0] == '+')
            result += stoll(cleanedExpression[i + 1]);
        else if (cleanedExpression[i][0] == '-')
            result -= stoll(cleanedExpression[i + 1]);
    }
    
    return result;
}

bool HUNLANCompiler::LongLongOverflow(const string& num) const
{
    string uIntMax = std::to_string(LLONG_MAX);
    if (num.size() > uIntMax.size())
        return true;
    else if (num.size() == uIntMax.size())
        for (int j = 0; j < num.size(); ++j)
            if (num[j] - '0' > uIntMax[j] - '0')
                return true;

    return false;
}

bool HUNLANCompiler::NumberExists(const string& numName) const { return numbers.find(numName) != numbers.end(); }

bool HUNLANCompiler::StringExists(const string& strName) const { return strings.find(strName) != strings.end(); }

long long HUNLANCompiler::NumberValueOf(const string& numName) { return numbers[numName]; }

string HUNLANCompiler::StringValueOf(const string& strName) { return strings[strName]; }

void HUNLANCompiler::ErrorMessage(const ErrorType error, const size_t& lineNumber, const string& undefined) const
{
    switch (error)
    {
        case ErrorType::INVALID_COMMAND:
            std::cout << "\nLine " << lineNumber << ": ERROR: Invalid commands.\n" << std::endl;
            break;

        case ErrorType::EXCESS_TOKENS:
            std::cout << "\nLine " << lineNumber << ": ERROR: Too many arguments.\n" << std::endl;
            break;

        case ErrorType::NUMBER_OVERFLOW:
            std::cout << "\nLine " << lineNumber << ": ERROR: Number is too large to store.\n" << std::endl;
            break;
        
        case ErrorType::ILLEGAL_NUMBER_DECLERATION:
            std::cout << "\nLine " << lineNumber << ": ERROR: Incorrect decleration of type \"NUMBER\".\n" << std::endl;
            break;

        case ErrorType::ILLEGAL_STRING_DECLERATION:
            std::cout << "\nLine " << lineNumber << ": ERROR: Incorrect declaration of type \"STRING\".\n" << std::endl;
            break;

        case ErrorType::ILLEGAL_NUMBER_INTIALIZATION:
            std::cout << "\nLine " << lineNumber << ": ERROR: Cannot assign type \"STRING\" to type \"NUMBER\".\n" << std::endl;
            break;
        
        case ErrorType::ILLEGAL_STRING_INTIALIZATION:
            std::cout << "\nLine " << lineNumber << ": ERROR: Cannot assign type \"NUMBER\" to type \"STRING\".\n" << std::endl;
            break;

        case ErrorType::ILLEGAL_PRINT:
            std::cout << "\nLine " << lineNumber << ": ERROR: The print statement is illegal.\n" << std::endl;
            break;

        case ErrorType::ILLEGAL_VARIABLE_NAME:
            std::cout << "\nLine " << lineNumber << ": ERROR: Illegal variable name.\n" << std::endl;
            break;

        case ErrorType::ILLEGAL_REDEFINITON:
            std::cout << "\nLine " << lineNumber << ": ERROR: Redefinition of existing variable is illegal.\n" << std::endl;
            break;
        
        case ErrorType::UNDEFINED_VARIABLE:
            std::cout << "\nLine " << lineNumber << ": ERROR: Undefined variable \"" << undefined << "\".\n" << std::endl;
            break;
        
        case ErrorType::ILLEGAL_ARITHMETIC:
            std::cout << "\nLine " << lineNumber << ": ERROR: Illegal arithmetic expression.\n" << std::endl;
            break;
        
        case ErrorType::ILLEGAL_STRING_ARITHMETIC:
            std::cout << "\nLine " << lineNumber << ": ERROR: Cannot perform arithmetic on type \"STRING\".\n" << std::endl;
            break;
    }
}

vector<string> HUNLANCompiler::operator()(const string& line, const size_t& lineNumber) const
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
            token += line[i];

            if (inQuotes)
            {
                parsedLine.push_back(token);
                token.clear();
            }

            inQuotes = !inQuotes;
            ++quoteCount;
        }
        else if  (line[i] == '"' && quoteCount >= 2)
        {
            token += line[i];
            parsedLine.push_back(token);
            token.clear();
        }
        else if (inQuotes)
        {
            if (line[i] == '\\' && IsEscapeSequence(line[i + 1]))
            {
                token += EscapeCharacter(line[i + 1]);
                ++i;
            }
            else if (line[i] == '\\' && !IsEscapeSequence(line[i + 1]))
                continue;
            else
                token += line[i];
        }
        else if (IsSeperator(line[i]))
        {
            if (!token.empty())
                parsedLine.push_back(token);
            token.clear();
        }
        else if (IsValidOperator(line[i]) || line[i] == '=')
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

vector<string> HUNLANCompiler::ValidateParse(const vector<string>& parsedLine, const size_t& lineNumber) const
{
    if (parsedLine.empty())
        return {"EMPTYLINE"};
    else if (parsedLine.size() < 2)
    {
        ErrorMessage(ErrorType::INVALID_COMMAND, lineNumber);
        return {};
    }
    else if (parsedLine[1][0] == '=' && !NumberExists(parsedLine[0]) && !StringExists(parsedLine[0]))
    {
        ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, parsedLine[0]);
        return {};
    }
    else if (!IsValidKeyword(parsedLine[0]) && !NumberExists(parsedLine[0]) && !StringExists(parsedLine[0]))
    {
        ErrorMessage(ErrorType::INVALID_COMMAND, lineNumber);
        return {};
    }
    else if ((NumberExists(parsedLine[0]) || StringExists(parsedLine[0])) && parsedLine[1][0] != '=')
    {
        ErrorMessage(ErrorType::INVALID_COMMAND, lineNumber);
        return {};
    }
    else if (IsValidKeyword(parsedLine[0]))
    {
        string keyword = parsedLine[0];
        if (keyword == "NUMBER" || keyword == "STRING")
        {
            if (parsedLine.size() != 2)
            {
                ErrorMessage(ErrorType::EXCESS_TOKENS, lineNumber);
                return {};
            }
            string variable = parsedLine[1];
            if (!IsValidVariableName(variable) || IsValidKeyword(variable))
            {
                ErrorMessage(ErrorType::ILLEGAL_VARIABLE_NAME, lineNumber);
                return {};
            }
            else if (NumberExists(variable) || StringExists(variable))
            {
                ErrorMessage(ErrorType::ILLEGAL_REDEFINITON, lineNumber);
                return {};
            }
        }
        else if (keyword == "PRINT")
        {
            if (parsedLine.size() != 2)
            {
                ErrorMessage(ErrorType::ILLEGAL_PRINT, lineNumber);
                return {};
            }
            string print = parsedLine[1];
            if (print[0] != '"' && !IsNumber(print) && !NumberExists(print) && !StringExists(print))
            {
                ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, print);
                return {};
            }
        }
    }
    else if (parsedLine[1][0] == '=')
    {
        if (parsedLine.size() < 3)
        {
            ErrorMessage(ErrorType::INVALID_COMMAND, lineNumber);
            return {};
        }
        string variable = parsedLine[0];
        if (!NumberExists(variable) && !StringExists(variable))
        {
            ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, variable);
            return {};
        }
        string assignment = parsedLine[2];
        if (NumberExists(variable))
        {
            if (parsedLine.size() < 3)
            {
                ErrorMessage(ErrorType::ILLEGAL_NUMBER_DECLERATION, lineNumber);
                return {};
            }
            else if (parsedLine.size() > 3 && !IsValidArithmetic(parsedLine, lineNumber))
                return {};
            else if (assignment[0] == '"' || StringExists(assignment))
            {
                ErrorMessage(ErrorType::ILLEGAL_NUMBER_INTIALIZATION, lineNumber);
                return {};
            }
            else if (!IsNumber(assignment) && !NumberExists(assignment))
            {
                ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, assignment);
                return {};
            }
            else if (StringExists(assignment))
            {
                ErrorMessage(ErrorType::ILLEGAL_NUMBER_INTIALIZATION, lineNumber);
                return {};
            }
            else if (IsNumber(assignment) && LongLongOverflow(assignment))
            {
                ErrorMessage(ErrorType::NUMBER_OVERFLOW, lineNumber);
                return {};
            }
        }
        else if (StringExists(variable)) 
        {
            if (parsedLine.size() != 3)
            {
                ErrorMessage(ErrorType::ILLEGAL_STRING_DECLERATION, lineNumber);
                return {};
            }
            else if (assignment[0] == '"' && assignment[assignment.size() - 1] != '"')
            {
                ErrorMessage(ErrorType::ILLEGAL_STRING_DECLERATION, lineNumber);
                return {};
            }
            else if (NumberExists(assignment) || IsNumber(assignment))
            {
                ErrorMessage(ErrorType::ILLEGAL_STRING_INTIALIZATION, lineNumber);
                return {};
            }
            else if (assignment[0] != '"' && !StringExists(assignment))
            {
                ErrorMessage(ErrorType::UNDEFINED_VARIABLE, lineNumber, assignment);
                return {};
            }
        }
    }

    return parsedLine;
}

bool HUNLANCompiler::Execute(const vector<string>& validLine)
{
    if (validLine.empty())
        return false;
    else if (validLine[0] == "EMPTYLINE")
        return true;
    if (IsValidKeyword(validLine[0]))
    {
        string keyword = validLine[0], variable = validLine[1];
        if (keyword == "NUMBER")
            numbers[variable] = 0;
        else if (keyword == "STRING")
            strings[variable] = "";
        else if (keyword == "PRINT")
        {
            if (variable[0] == '"')
                std::cout << variable.substr(1, variable.size() - 2);
            else if (NumberExists(variable))
                std::cout << NumberValueOf(variable);
            else if (StringExists(variable))
                std::cout << StringValueOf(variable);
            else if (IsNumber(variable))
                std::cout << variable;
        }
    }
    else if (validLine[1][0] == '=')
    {
        string variable = validLine[0], assignment = validLine[2];
        if (NumberExists(variable))
        {
            if (validLine.size() == 3 && IsNumber(assignment))
                numbers[variable] = stoll(assignment);
            else if (validLine.size() == 3 && NumberExists(assignment))
                numbers[variable] = NumberValueOf(assignment);
            else if (validLine.size() > 3)
                numbers[variable] = CalculateArithmetic(validLine);
        }
        else if (StringExists(variable))
        {
            if (assignment[0] == '"')
                strings[variable] = assignment.substr(1, assignment.size() - 2);
            else if (StringExists(assignment))
                strings[variable] = StringValueOf(assignment);
        }
    }

    return true;
}