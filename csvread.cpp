#include "csvread.h"

CsvRead::CsvRead()
{

}

void CsvRead::readcsv(const string& workDir, const string& filename, vector<vector<string>>& arr){
    ifstream fs(workDir+filename);
    if (!fs.is_open()){
        throw "File not opened";
    }
    string BigStr;
    vector<string> selements;

    while (getline(fs, BigStr)){
        string ThsStr;
        stringstream lineStream(BigStr);
        while (getline(lineStream, ThsStr, ',')){
            selements.push_back(ThsStr);
        }
        arr.push_back(selements);
        selements.clear();
    }
}
