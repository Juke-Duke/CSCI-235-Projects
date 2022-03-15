#include <iostream>
#include<fstream>

int main()
{
    std::fstream file;
    file.open("StudentRecords.txt", std::ios::out);

    if (file.is_open())
    {
        file << "Test";
        file.close();
    }

    return 0;
}