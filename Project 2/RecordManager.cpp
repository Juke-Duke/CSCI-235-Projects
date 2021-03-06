#include "RecordManager.h"

RecordManager::RecordManager() { AssembleStudents(); }

bool RecordManager::Process(vector<string> parsedCommand)
{
    if (parsedCommand.empty())
        return true;
        
    if (parsedCommand[0] == "ADD")
        ADD(std::stoi(parsedCommand[1]), parsedCommand[2], std::stoi(parsedCommand[3]));
    else if (parsedCommand[0] == "FIND")
    {
        if (parsedCommand[1] == "id")
        {
            unsigned int ID = std::stoi(parsedCommand[3]);
            FIND(ID, parsedCommand[2][0]);
        }
        else if (parsedCommand[1] == "name")
            FIND(parsedCommand[3], parsedCommand[2][0]);
        else if (parsedCommand[1] == "age")
        {
            unsigned short age = std::stoi(parsedCommand[3]);
            FIND(age, parsedCommand[2][0]);
        }
    }
    else if (parsedCommand[0] == "REMOVE")
    {
        if (parsedCommand[1] == "id")
        {
            unsigned int ID = std::stoi(parsedCommand[3]);
            REMOVE(ID, parsedCommand[2][0]);
        }
        else if (parsedCommand[1] == "name")
            REMOVE(parsedCommand[3], parsedCommand[2][0]);
        else if (parsedCommand[1] == "age")
        {
            unsigned short age = std::stoi(parsedCommand[3]);
            REMOVE(age, parsedCommand[2][0]);
        }
    }
    else if (parsedCommand[0] == "STOP")
    {
        STOP();
        return false;
    }

    return true;
}

void RecordManager::AssembleStudents()
{
    std::ifstream file;
    file.open("StudentRecords.txt");

    if (file.is_open())
    {
        int dataLine = 0;
        unsigned int ID;
        string name, line;
        unsigned short age;

        while (std::getline(file, line))
        {
            if (dataLine == 0)
            {
                ID = std::stoi(line);
                ++dataLine;
            }
            else if (dataLine == 1)
            {
                name = line;
                ++dataLine;
            }
            else if (dataLine == 2)
            {
                age = std::stoi(line);
                dataLine = 0;
                students.push_back(StudentRecord(ID, name, age));
            }
        }

        file.close();
    }
}

void RecordManager::ADD(const unsigned int& ID, const string& name, const unsigned short& age)
    { students.push_back(StudentRecord(ID, name, age)); }

void RecordManager::FIND(const unsigned int& ID, const char& relation)
{
    std::cout << std::endl;

    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.ID == ID)
            student.Display();
        else if (relation == '>' && student.ID > ID)
            student.Display();
        else if (relation == '<' && student.ID < ID)
            student.Display();
    }

    std::cout << std::endl;
}

void RecordManager::FIND(const string& name, const char& relation)
{
    std::cout << std::endl;

    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.name == name)
            student.Display();
        else if (relation == '>' && student.name > name)
            student.Display();
        else if (relation == '<' && student.name < name)
            student.Display();
    }

    std::cout << std::endl;
}

void RecordManager::FIND(const unsigned short& age, const char& relation)
{
    std::cout << std::endl;
    
    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.age == age)
            student.Display();
        else if (relation == '>' && student.age > age)
            student.Display();
        else if (relation == '<' && student.age < age)
            student.Display();
    }

    std::cout << std::endl;
}

void RecordManager::REMOVE(const unsigned int& ID, const char& relation)
{
    vector<StudentRecord> clean;

    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.ID != ID)
            clean.push_back(student);
        else if (relation == '>' && student.ID <= ID)
            clean.push_back(student);
        else if (relation == '<' && student.ID >= ID)
            clean.push_back(student);
    }

    students = clean;
}

void RecordManager::REMOVE(const string& name, const char& relation)
{
    vector<StudentRecord> clean;

    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.name != name)
            clean.push_back(student);
        else if (relation == '>' && student.name <= name)
            clean.push_back(student);
        else if (relation == '<' && student.name >= name)
            clean.push_back(student);
    }

    students = clean;
}

void RecordManager::REMOVE(const unsigned short& age, const char& relation)
{
    vector<StudentRecord> clean;

    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.age != age)
            clean.push_back(student);
        else if (relation == '>' && student.age <= age)
            clean.push_back(student);
        else if (relation == '<' && student.age >= age)
            clean.push_back(student);
    }

    students = clean;
}

void RecordManager::STOP()
{
    std::ofstream file;
    file.open("StudentRecords.txt");

    if (file.is_open())
    {
        for (StudentRecord& student : students)
            file << student.ID << '\n' << student.name << '\n' << student.age << '\n';
        
        file.close();
    }
}