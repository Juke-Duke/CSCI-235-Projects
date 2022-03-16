#include <iostream>
#include<fstream>
#include "CommandParser.h"

int main()
{
    CommandParser parser;
    vector<string> parsed;
    parsed = parser("");
    for (string& s : parsed)
        std::cout << s << std::endl;

}