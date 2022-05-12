#include "databasehandler.h"
#include "csvread.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

void DatabaseHandler::setWorkDir(string workDir){
    _workDir = workDir;
}

void DatabaseHandler::reloadTables(){
    caffeAndCinemaTable.clear();
    costsTable.clear();
    instituteTable.clear();
    transportTable.clear();
    workdaysTable.clear();

    CsvRead reader;
    reader.readcsv(_workDir, "Caffe-and-cinema.csv", caffeAndCinemaTable);
    reader.readcsv(_workDir, "Costs.csv", costsTable);
    reader.readcsv(_workDir, "Institute.csv", instituteTable);
    reader.readcsv(_workDir, "Transport.csv", transportTable);
    reader.readcsv(_workDir, "Workdays.csv", workdaysTable);
}

string DatabaseHandler::getWorkDir() const{
    return _workDir;
}

int DatabaseHandler::getWorkdays(string month){
    // Получаем из базы данных число рабочих дней данном в месяце
    for (size_t i = 1; i < workdaysTable.size(); i++){
        if(workdaysTable[i][3] == month){
            return stoi(workdaysTable[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getDaysCount(string month) {
    // Получаем из базы данных число дней данном в месяце
    for (size_t i = 1; i < workdaysTable.size(); i++){
        if(workdaysTable[i][3] == month){
            return stoi(workdaysTable[i][1]);
        }
    }
    return -1;
}

int DatabaseHandler::getTransportCost(const string& city, const string& homeAddress,const string& institute){
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    for (size_t i = 1; i < transportTable.size(); i++){
        if (transportTable[i][0] == city && transportTable[i][1] == homeAddress && transportTable[i][2] == institute){
            return stoi(transportTable[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getInstituteDinnerCost(const string& city, const string& institute){
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    for (size_t i = 1; i < instituteTable.size(); i++){
        if (instituteTable[i][0] == city && instituteTable[i][1] == institute){
            return stoi(instituteTable[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getCoffeeCost(const string& city, const string& coffee){
    // Получаем из базы данных средний чек в данном баре
    for (size_t i = 1; i < caffeAndCinemaTable.size(); i++){
        if (caffeAndCinemaTable[i][0] == city && caffeAndCinemaTable[i][2] == coffee){
            return stoi(caffeAndCinemaTable[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getCinemaCost(const string& city, const string& cinema){
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    for (size_t i = 1; i < caffeAndCinemaTable.size(); i++){
        if (caffeAndCinemaTable[i][0] == city && caffeAndCinemaTable[i][4] == cinema){
            return stoi(caffeAndCinemaTable[i][5]);
        }
    }
    return -1;
}

int DatabaseHandler::getHomeFoodCost(const string& city){
    // Получаем из базы данных средние по региону затраты на еду
    for (size_t i = 1; i < costsTable.size(); i++){
        if (costsTable[i][0] == city){
            return stoi(costsTable[i][2]);
        }
    }
    return -1;
}


int DatabaseHandler::getOtherMontlyCosts(const std::string& city, int age){
    /* Получаем из базы данных средние по региону затраты в данном месяце
     для людей данного возраста
    (по остальным статьям кроме еды, транспорта и развлечений) */
    if(age == 0){
        return 0;
    }
    for (size_t i = 1; i < costsTable.size(); i++){
        if (costsTable[i][0] == city && stoi(costsTable[i][1]) == age){
            return stoi(costsTable[i][3]);
        }
    }
    return -1;
}
