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
    void readcsv(const string& filename, vector<vector<string>>& arr);
    void writeTable(vector<vector<QString>> data, const string& path);
    void setWorkDir(string workDir);
    void reloadTables();
    string getWorkDir() const;

    vector<vector<string>> getCaffeeTable();
    vector<vector<string>> getCostsTable();
    vector<vector<string>> getInstituteTable();
    vector<vector<string>> getTransportTable();
    vector<vector<string>> getWorkdaysTable();
private:
    string _workDir;
    vector<vector<string>> caffeAndCinemaTableRead;
    vector<vector<string>> costsTableRead;
    vector<vector<string>> instituteTableRead;
    vector<vector<string>> transportTableRead;
    vector<vector<string>> workdaysTableRead;
};

#endif // CSVREAD_H
