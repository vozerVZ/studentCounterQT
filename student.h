#ifndef STUDENT_H
#define STUDENT_H

#include "databaseHandler.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class Student{
    private:
        int age;
        string name;
    public:
        Student(int _age, string _name);
        int getAge() const;
        string getName() const;
        void setAge(int _age);
        void setName(string _name);
        int getCosts(int month, const std::string& city, const std::string& homeAddress,
            const std::string& institute, const std::string& cinema,
            const std::string& coffee, DatabaseHandler database);
};

#endif
