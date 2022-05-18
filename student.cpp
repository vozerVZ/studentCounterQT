#include "student.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;


Student::Student(int age, string name){
    _age = age;
    _name = name;
}

int Student::getAge() const{
    return _age;
}

string Student::getName() const{
    return _name;
}

void Student::setAge(int age){
    _age = age;
}

void Student::setName(string name){
    _name = name;
}

int Student::getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute, DatabaseHandler database, CsvRead r) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<int>(2 * database.getTransportCost(city, homeAddress, institute, r) +
        database.getInstituteDinnerCost(city, institute, r) + 0.66 * database.getHomeFoodCost(city, r) + 0.5);
}


int Student::getWeekendCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee, DatabaseHandler database, CsvRead r) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<int>(0.66 * database.getHomeFoodCost(city, r) +
        database.getCinemaCost(city, cinema, r) + database.getCoffeeCost(city, coffee, r) + 0.5);
}

int Student::getCosts(string month, const std::string& city, const std::string& homeAddress,
    const std::string& institute, const std::string& cinema,
    const std::string& coffee, DatabaseHandler database, CsvRead r) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const int daysCount = database.getDaysCount(month, r);
    const int workDays = database.getWorkdays(month, r);
    const int weekends = daysCount - workDays;

    return workDays * getWorkdayCost(city, homeAddress, institute, database, r) +
           weekends * getWeekendCost(city, cinema, coffee, database, r) +
           database.getOtherMontlyCosts(city, getAge(), r);
}
