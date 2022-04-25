#include "HUNLANCompiler.h"
#include <fstream>

int main(int argc, char** argv)
{
    std::ifstream file(argv[1]);
    HUNLANCompiler compiler;
    string line;
    size_t lineNumber = 1;
    bool running = true;

    while (running && std::getline(file, line))
    {
        running = compiler.Execute(compiler(line, lineNumber));
        ++lineNumber;
    }

    return 0;
}