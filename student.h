#ifndef STUDENT_H
#define STUDENT_H

#include "databaseHandler.h"
#include "csvread.h"
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
            const std::string& coffee, DatabaseHandler database, CsvRead rCaffe,
            CsvRead rCosts, CsvRead rInstitute, CsvRead rTransport, CsvRead rWorkdays);
        int getWorkdayCost(const string& city, const string& homeAddress, const string& institute,
                           DatabaseHandler database, CsvRead rTransport,
                           CsvRead rInstitute, CsvRead rCosts);
        int getWeekendCost(const string& city, const string& cinema, const string& coffee,
                           DatabaseHandler database, CsvRead rCosts,
                           CsvRead rCaffe);
};

#endif
