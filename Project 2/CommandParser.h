#pragma once
#include <string>
#include <vector>
using std::string, std::vector;

class CommandParser
{
private:
    char separators[2] = {' ', '\t'};

public:
    vector<string> operator()(string& commandInput);
};