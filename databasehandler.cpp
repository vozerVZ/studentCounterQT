#include "databasehandler.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


DatabaseHandler::DatabaseHandler(){
}

int DatabaseHandler::getWorkdays(string month, CsvRead& r) const{
    // Получаем из базы данных число рабочих дней данном в месяце
    for (size_t i = 1; i < r.getWorkdaysTable().size(); i++){
        if(r.getWorkdaysTable()[i][3] == month){
            return stoi(r.getWorkdaysTable()[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getDaysCount(string month, CsvRead& r) const{
    // Получаем из базы данных число дней данном в месяце
    for (size_t i = 1; i < r.getWorkdaysTable().size(); i++){
        if(r.getWorkdaysTable()[i][3] == month){
            return stoi(r.getWorkdaysTable()[i][1]);
        }
    }
    return -1;
}

int DatabaseHandler::getTransportCost(const string& city, const string& homeAddress,const string& institute, CsvRead& r) const{
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    for (size_t i = 1; i < r.getTransportTable().size(); i++){
        if (r.getTransportTable()[i][0] == city && r.getTransportTable()[i][1] == homeAddress &&
                r.getTransportTable()[i][2] == institute){
            return stoi(r.getTransportTable()[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getInstituteDinnerCost(const string& city, const string& institute, CsvRead& r) const{
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    for (size_t i = 1; i < r.getInstituteTable().size(); i++){
        if (r.getInstituteTable()[i][0] == city && r.getInstituteTable()[i][1] == institute){
            return stoi(r.getInstituteTable()[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getCoffeeCost(const string& city, const string& coffee, CsvRead& r) const{
    // Получаем из базы данных средний чек в данном баре
    for (size_t i = 1; i < r.getCaffeeTable().size(); i++){
        if (r.getCaffeeTable()[i][0] == city && r.getCaffeeTable()[i][2] == coffee){
            return stoi(r.getCaffeeTable()[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getCinemaCost(const string& city, const string& cinema, CsvRead& r) const{
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    for (size_t i = 1; i < r.getCaffeeTable().size(); i++){
        if (r.getCaffeeTable()[i][0] == city && r.getCaffeeTable()[i][4] == cinema){
            return stoi(r.getCaffeeTable()[i][5]);
        }
    }
    return -1;
}

int DatabaseHandler::getHomeFoodCost(const string& city, CsvRead& r) const{
    // Получаем из базы данных средние по региону затраты на еду
    for (size_t i = 1; i < r.getCostsTable().size(); i++){
        if (r.getCostsTable()[i][0] == city){
            return stoi(r.getCostsTable()[i][2]);
        }
    }
    return -1;
}


int DatabaseHandler::getOtherMontlyCosts(const std::string& city, int age, CsvRead& r) const{
    /* Получаем из базы данных средние по региону затраты в данном месяце
     для людей данного возраста
    (по остальным статьям кроме еды, транспорта и развлечений) */
    if(age == 0){
        return 0;
    }
    for (size_t i = 1; i < r.getCostsTable().size(); i++){
        if (r.getCostsTable()[i][0] == city && stoi(r.getCostsTable()[i][1]) == age){
            return stoi(r.getCostsTable()[i][3]);
        }
    }
    return -1;
}
