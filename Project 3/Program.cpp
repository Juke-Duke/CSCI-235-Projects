#include "HUNLANCompiler.h"
using std::cout, std::endl, std::string, std::vector;

int main()
{
    HUNLANCompiler compiler;
    string line;
    size_t lineNumber = 0;
    while (getline(std::cin, line))
    {
        vector<string> parsedLine = compiler(line, lineNumber);
        
        cout << endl;
        for (string token : parsedLine)
            cout << token << endl;
        cout << endl;

        ++lineNumber;
    }

    return 0;
}