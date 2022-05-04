#ifndef CSVREAD_H
#define CSVREAD_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;


class CsvRead
{
public:
    CsvRead();
    void readcsv(const string& workDir, const string& filename, vector<vector<string>>& arr);
};

#endif // CSVREAD_H
