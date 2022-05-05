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
    void WriteTable(vector<vector<QString>> data, std::string path);
};

#endif // CSVREAD_H
