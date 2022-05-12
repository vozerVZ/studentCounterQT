#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


class DatabaseHandler{
    public:
        void setWorkDir(string workDir);
        void reloadTables();
        string getWorkDir() const;
        int getWorkdays(string month);
        int getDaysCount(string month);
        int getOtherMontlyCosts(const string& city, int age);
        int getHomeFoodCost(const string& city);
        int getCinemaCost(const string& city, const string& cinema);
        int getCoffeeCost(const string& city, const string& coffee);
        int getInstituteDinnerCost(const string& city, const string& institute);
        int getTransportCost(const string& city, const string& homeAddress, const string& institute);
        vector<vector<string>> caffeAndCinemaTable;
        vector<vector<string>> costsTable;
        vector<vector<string>> instituteTable;
        vector<vector<string>> transportTable;
        vector<vector<string>> workdaysTable;
    private:
        string _workDir;

};

#endif
