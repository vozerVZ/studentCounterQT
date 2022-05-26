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
    CsvRead(const string& filename);
    void readcsv();
    void writeTable(vector<vector<QString>>& vecTable);
    void setWorkDir(string workDir);
    string getWorkDir() const;

    vector<vector<string>> getTable() const;
private:
    string _filename;
    string _workDir;
    vector<vector<string>> _table;
};

#endif // CSVREAD_H
