#ifndef CSVREAD_H
#define CSVREAD_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <QString>
using namespace std;


class CsvRead
{
public:
    CsvRead();
    void readcsv(const string& workDir, const string& filename, vector<vector<string>>& arr);
    void writeTable(vector<vector<QString>> data, const string& path);
};

#endif // CSVREAD_H
