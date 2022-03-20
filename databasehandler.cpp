#include "databasehandler.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>



void readcsv(const string& filename, vector<vector<string>>& arr){
    ifstream fs(filename);
    if (!fs.is_open())
    {
        cout << "File not opened: "<< filename << endl;
        return;
    }
    string BigStr;
    vector<string> selements;

    while (getline(fs, BigStr)){
        string ThsStr;
        stringstream lineStream(BigStr);
        while (getline(lineStream, ThsStr, ','))
        {
            selements.push_back(ThsStr);
        }
        arr.push_back(selements);
        selements.clear();
    }
}

int DatabaseHandler::getWorkdays(int month){
    // Получаем из базы данных число рабочих дней данном в месяце
    vector<vector<string>> sarr;
    readcsv("Workdays.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if(stoi(sarr[i][0]) == month){
            return stoi(sarr[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getDaysCount(int month) {
    // Получаем из базы данных число дней данном в месяце
    vector<vector<string>> sarr;
    readcsv("Workdays.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if(stoi(sarr[i][0]) == month){
            return stoi(sarr[i][1]);
        }
    }
    return -1;
}

int DatabaseHandler::getTransportCost(const string& city, const string& homeAddress,const string& institute){
    // Получаем из базы данных стоимость кратчайшей дороги до инстиутта
    vector<vector<string>> sarr;
    readcsv("Transport.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city && sarr[i][1] == homeAddress && sarr[i][2] == institute){
            return stoi(sarr[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getInstituteDinnerCost(const string& city, const string& institute){
    // Получаем из базы данных среднюю стоимость обеда в столовой данного института
    vector<vector<string>> sarr;
    readcsv("Institute.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city && sarr[i][1] == institute){
            return stoi(sarr[i][2]);
        }
    }
    return -1;
}

int DatabaseHandler::getCoffeeCost(const string& city, const string& coffee){
    // Получаем из базы данных средний чек в данном баре
    vector<vector<string>> sarr;
    readcsv("Caffe-and-cinema.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city && sarr[i][2] == coffee){
            return stoi(sarr[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getCinemaCost(const string& city, const string& cinema){
    // Получаем из базы данных стоимость билета на вечерний сеанс в данном кинотетре
    vector<vector<string>> sarr;
    readcsv("Caffe-and-cinema.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city && sarr[i][4] == cinema){
            return stoi(sarr[i][5]);
        }
    }
    return -1;
}

int DatabaseHandler::getHomeFoodCost(const string& city){
    // Получаем из базы данных средние по региону затраты на еду
    vector<vector<string>> sarr;
    readcsv("Costs.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city){
            return stoi(sarr[i][2]);
        }
    }
    return -1;
}


int DatabaseHandler::getOtherMontlyCosts(const std::string& city, int age){
    /* Получаем из базы данных средние по региону затраты в данном месяце
     для людей данного возраста
    (по остальным статьям кроме еды, транспорта и развлечений) */
    vector<vector<string>> sarr;
    readcsv("Costs.csv", sarr);
    for (size_t i = 1; i < sarr.size(); i++){
        if (sarr[i][0] == city && stoi(sarr[i][1]) == age){
            return stoi(sarr[i][3]);
        }
    }
    return -1;
}

int DatabaseHandler::getWorkdayCost(const std::string& city, const std::string& homeAddress,
                    const std::string& institute) {
   /* По рабочим дням расходы складываются из стоимости:
    - дороги до института и обратно
    - обеда в институтской столовой
    - завтрака и обеда дома */

    return static_cast<int>(2 * getTransportCost(city, homeAddress, institute) +
        getInstituteDinnerCost(city, institute) + 0.66 * getHomeFoodCost(city) + 0.5);
}


int DatabaseHandler::getWeekandCost(const std::string& city, const std::string& cinema,
                    const std::string& coffee) {
    /* По выходным дням расходы складываются из стоимости:
     - похода в кино (пешком)
     - похода  в кафе (пешком)
     - завтрака и обеда дома */

    return static_cast<int>(0.66 * getHomeFoodCost(city) +
        getCinemaCost(city, cinema) + getCoffeeCost(city, coffee) + 0.5);
}
