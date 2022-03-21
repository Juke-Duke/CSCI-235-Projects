#include "RecordManager.h"

RecordManager::RecordManager() { AssembleStudents(); }

vector<StudentRecord> RecordManager::GetStudents() { return students; }

bool RecordManager::Process(vector<string>& parsedCommand)
{
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
            FIND(parsedCommand[3]);
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
            REMOVE(parsedCommand[3]);
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
    file.open("StudentRecords.txt", std::ios::out);

    if (file.is_open())
    {
        unsigned int ID;
        string name;
        unsigned short age;

        while (file >> ID >> name >> age)
            students.push_back(StudentRecord(ID, name, age));

        file.close();
    }
}

void RecordManager::ADD(unsigned int ID, string name, unsigned short age)
    { students.push_back(StudentRecord(ID, name, age)); }

void RecordManager::FIND(unsigned int ID, char relation)
{
    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.ID == ID)
            student.Print();
        else if (relation == '>' && student.ID > ID)
            student.Print();
        else if (relation == '<' && student.ID < ID)
            student.Print();
    }
}

void RecordManager::FIND(string name)
{
    for (StudentRecord& student : students)
        if (student.name == name)
            student.Print();
}

void RecordManager::FIND(unsigned short age, char relation)
{
    for (StudentRecord& student : students)
    {
        if (relation == '=' && student.age == age)
            student.Print();
        else if (relation == '>' && student.age > age)
            student.Print();
        else if (relation == '<' && student.age < age)
            student.Print();
    }
}

void RecordManager::REMOVE(unsigned int ID, char relation)
{
    for (int i = 0; i < students.size(); ++i)
    {
        if (relation == '=' && students[i].ID == ID)
            students.erase(students.begin() + i);
        else if (relation == '>' && students[i].ID > ID)
            students.erase(students.begin() + i);
        else if (relation == '<' && students[i].ID < ID)
            students.erase(students.begin() + i);
    }
}

void RecordManager::REMOVE(string name)
{
    for (int i = 0; i < students.size(); ++i)
        if (students[i].name == name)
            students.erase(students.begin() + i);
}

void RecordManager::REMOVE(unsigned short age, char relation)
{
    for (int i = 0; i < students.size(); ++i)
    {
        if (relation == '=' && students[i].age == age)
            students.erase(students.begin() + i);
        else if (relation == '>' && students[i].age == age)
            students.erase(students.begin() + i);
        else if (relation == '<' && students[i].age == age)
            students.erase(students.begin() + i);
    }
}

void RecordManager::STOP()
{
    std::fstream file;
    file.open("StudentRecords.txt", std::ios::out);

    if (file.is_open())
    {
        for (StudentRecord& student : students)
            file << student.ID << ' ' << student.name << ' ' << student.age << '\n';
        
        file.close();
    }
}