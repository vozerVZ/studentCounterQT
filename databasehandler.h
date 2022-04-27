#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class DatabaseHandler
{
    public:
        void setWorkDir(string _workDir);
        string getWorkDir();
        void readcsv(const string& filename, vector<vector<string>>& arr);
        int getWorkdays(string month);
        int getDaysCount(string month);
        int getOtherMontlyCosts(const string& city,int age);
        int getWorkdayCost(const string& city, const string& homeAddress, const string& institute);
        int getWeekandCost(const string& city, const string& cinema, const string& coffee);
    private:
        string workDir;

        int getHomeFoodCost(const string& city);
        int getCinemaCost(const string& city, const string& cinema);
        int getCoffeeCost(const string& city, const string& coffee);
        int getInstituteDinnerCost(const string& city, const string& institute);
        int getTransportCost(const string& city, const string& homeAddress,const string& institute);
};

#endif
