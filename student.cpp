#include "student.h"
using namespace std;
#include <string>
#include <iostream>
#include <fstream>

Student::Student(int _age, string _name){
    age = _age;
    name = _name;
}

int Student::getAge() const{
    return age;
}

string Student::getName() const{
    return name;
}

void Student::setAge(int _age){
    age = _age;
}

void Student::setName(string _name){
    name = _name;
}

int Student::getCosts(int month, const std::string& city, const std::string& homeAddress,
    const std::string& institute, const std::string& cinema,
    const std::string& coffee, DatabaseHandler database) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const int daysCount = database.getDaysCount(month);
    const int workDays = database.getWorkdays(month);
    const int weekends = daysCount - workDays;

    return workDays * database.getWorkdayCost(city, homeAddress, institute) +
           weekends * database.getWeekandCost(city, cinema, coffee) +
           database.getOtherMontlyCosts(city, getAge());
}
