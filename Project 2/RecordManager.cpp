#include "RecordManager.h"

void RecordManager::AssembleStudents()
{
    std::ifstream file;
    file.open("StudentRecords.txt", std::ios::out);

    if (file.is_open())
    {
        unsigned int ID;
        string name;
        unsigned short age;

        while (file >> ID >> name >> age)
        {
            students.push_back(StudentRecord(ID, name, age));
        }

        file.close();
    }
}