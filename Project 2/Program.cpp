#include "CommandParser.h"
#include "RecordManager.h"

int main()
{
    CommandParser parser;
    RecordManager manager;

    string input;
    bool running = true;
    
    while(running)
    {
        std::cout << ":\\\\  ";
        std::getline(std::cin, input);
        running = manager.Process(parser(input));
    }

    return 0;
}