#include <iostream>
#include <string>
#include <vector>
using std::string, std::vector;

template<typename T>
struct Variable
{
    string name;
    T value;

    Variable(const string& name, const T& value) : name(name), value(value) {}
};

template<typename T>
class HUNLANCompiler 
{
private:
    const string commands[3] = {"NUMBER", "STRING", "PRINT"};
    vector<Variable<T>> variables;

public:
    bool IsSeperator(const char& token) const { return token == ' ' || token == '\t'; }

    bool IsValidOperator(const char& operation) const { return operation == '=' || operation == '+' || operation == '-' || operation = '*'; }
    
    bool IsValidCommand(const string& token) const
    {
        for (string command : commands)
            if (token == command)
                return true;
        
        return false;
    }

    bool IsNumber(const string& num) const
    {
        for (char digit : num)
            if (!isdigit(digit))
                return false;
        
        return true;
    }

    vector<string> operator()(const string& line) const
    {
        vector<string> parsedLine;
        string token;
        bool inQuotes = false;
        int quoteCount = 0;

        for (int i = 0; i < line.size(); ++i)
        {
            if (line[i] == '#')
                break;
            else if (line[i] == '"' && quoteCount < 2)
            {
                inQuotes = !inQuotes;
                ++quoteCount;
            }
            else if  (line[i] == '"' && quoteCount >= 2)
            {
                token += line[i];
                parsedLine.push_back(token);
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
    }
};