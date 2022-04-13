#include <string>
using std::string;

template<typename T>
struct Variable
{
    string name;
    T value;

    Variable(const string& name, const T& value) : name(name), value(value) {}
};