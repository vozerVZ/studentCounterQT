#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

void readcsv(const string& filename, vector<vector<string>>& arr);

class DatabaseHandler
{
    public:
        int getWorkdays(int month);
        int getDaysCount(int month);
        int getOtherMontlyCosts(const string& city,int age);
        int getWorkdayCost(const string& city, const string& homeAddress, const string& institute);
        int getWeekandCost(const string& city, const string& cinema, const string& coffee);
    private:
        int getHomeFoodCost(const string& city);
        int getCinemaCost(const string& city, const string& cinema);
        int getCoffeeCost(const string& city, const string& coffee);
        int getInstituteDinnerCost(const string& city, const string& institute);
        int getTransportCost(const string& city, const string& homeAddress,const string& institute);
};

#endif
