#include "CommandParser.h"
#include "RecordManager.h"

int main()
{
    RecordManager manager;
    std::vector<string> command = { "ADD", "100", "Youssef", "20" };
    manager.Process(command);
    command = { "ADD", "1090", "Breh", "21" };
    manager.Process(command);
    command = { "REMOVE", "name", "=", "Youssef" };
    manager.Process(command);
    command = { "STOP" };
    std::vector<StudentRecord> students = manager.GetStudents();
    manager.Process(command);

    for (StudentRecord& student : students)
        student.Display();
}