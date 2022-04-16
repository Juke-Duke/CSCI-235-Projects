#include "HUNLANCompiler.h"
#include <fstream>
using std::cout, std::endl, std::string, std::vector;

int main()
{
    std::ifstream file("input.txt");
    HUNLANCompiler compiler;
    string line;
    size_t lineNumber = 1;
    while (std::getline(file, line))
    {
        vector<string> parsedLine = compiler(line, lineNumber);
        compiler.Execute(parsedLine);
        ++lineNumber;
    }

    return 0;
}