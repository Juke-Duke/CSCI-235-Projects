#include "HUNLANCompiler.h"
#include <fstream>
using std::cout, std::endl, std::string, std::vector;

int main(int argc, char** argv)
{
    std::ifstream file(argv[1]);
    HUNLANCompiler compiler;
    string line;
    size_t lineNumber = 1;
    bool running = true;
    while (std::getline(file, line) && running)
    {
        running = compiler.Execute(compiler(line, lineNumber));
        ++lineNumber;
    }

    return 0;
}