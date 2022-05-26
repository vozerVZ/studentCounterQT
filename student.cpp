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
                    const std::string& institute, DatabaseHandler database, CsvRead rTransport,
                    CsvRead rInstitute, CsvRead rCosts) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<int>(2 * database.getTransportCost(city, homeAddress, institute, rTransport) +
        database.getInstituteDinnerCost(city, institute, rInstitute) + 0.66 * database.getHomeFoodCost(city, rCosts) + 0.5);
}


int Student::getWeekendCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee, DatabaseHandler database, CsvRead rCosts,
                    CsvRead rCaffe) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<int>(0.66 * database.getHomeFoodCost(city, rCosts) +
        database.getCinemaCost(city, cinema, rCaffe) + database.getCoffeeCost(city, coffee, rCaffe) + 0.5);
}

int Student::getCosts(string month, const std::string& city, const std::string& homeAddress,
    const std::string& institute, const std::string& cinema,
    const std::string& coffee, DatabaseHandler database, CsvRead rCaffe,
    CsvRead rCosts, CsvRead rInstitute, CsvRead rTransport, CsvRead rWorkdays) {
    /* Расходы:
     - по рабочим дням
     - по выходным дням
     - прочие расходы */

    const int daysCount = database.getDaysCount(month, rWorkdays);
    const int workDays = database.getWorkdays(month, rWorkdays);
    const int weekends = daysCount - workDays;

    return workDays * getWorkdayCost(city, homeAddress, institute, database, rTransport, rInstitute, rCosts) +
           weekends * getWeekendCost(city, cinema, coffee, database, rCosts, rCaffe) +
           database.getOtherMontlyCosts(city, getAge(), rCosts);
}
