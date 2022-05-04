#ifndef STUDENT_H
#define STUDENT_H

#include "databaseHandler.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


class Student{
    private:
        int _age;
        string _name;
    public:
        Student(int age, string name);
        int getAge() const;
        string getName() const;
        void setAge(int age);
        void setName(string name);
        int getCosts(string month, const std::string& city, const std::string& homeAddress,
            const std::string& institute, const std::string& cinema,
            const std::string& coffee, DatabaseHandler database);
        int getWorkdayCost(const string& city, const string& homeAddress, const string& institute,
                           DatabaseHandler database);
        int getWeekendCost(const string& city, const string& cinema, const string& coffee,
                           DatabaseHandler database);
};

#endif
