#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include "csvread.h"
using namespace std;


class DatabaseHandler{
    public:
        DatabaseHandler();
        int getWorkdays(string month, CsvRead& r) const;
        int getDaysCount(string month, CsvRead& r) const;
        int getOtherMontlyCosts(const string& city, int age, CsvRead& r) const;
        int getHomeFoodCost(const string& city, CsvRead& r) const;
        int getCinemaCost(const string& city, const string& cinema, CsvRead& r) const;
        int getCoffeeCost(const string& city, const string& coffee, CsvRead& r) const;
        int getInstituteDinnerCost(const string& city, const string& institute, CsvRead& r) const;
        int getTransportCost(const string& city, const string& homeAddress, const string& institute, CsvRead& r) const;
};

#endif
