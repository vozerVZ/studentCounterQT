#include "csvread.h"
#include <QFile>
#include <QTextStream>
#include <iostream>

CsvRead::CsvRead(){
}

void CsvRead::setWorkDir(string workDir){
    _workDir = workDir;
}

string CsvRead::getWorkDir() const{
    return _workDir;
}

vector<vector<string>> CsvRead::getCaffeeTable(){
    return caffeAndCinemaTableRead;
}
vector<vector<string>> CsvRead::getCostsTable(){
    return costsTableRead;
}
vector<vector<string>> CsvRead::getInstituteTable(){
    return instituteTableRead;
}
vector<vector<string>> CsvRead::getTransportTable(){
    return transportTableRead;
}
vector<vector<string>> CsvRead::getWorkdaysTable(){
    return workdaysTableRead;
}

void CsvRead::readcsv(const string& filename, vector<vector<string>>& arr){
    ifstream fs(_workDir + filename);
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

void CsvRead::writeTable(vector<vector<QString>> data, const string& path){
    QString filename = QString::fromStdString(path);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j){
                stream << data[i][j] << ",";
            }
            stream << "\n";
        }
    }

    //this->parent();
}

void CsvRead::reloadTables(){
    caffeAndCinemaTableRead.clear();
    costsTableRead.clear();
    instituteTableRead.clear();
    transportTableRead.clear();
    workdaysTableRead.clear();

    readcsv("Caffe-and-cinema.csv", caffeAndCinemaTableRead);
    readcsv("Costs.csv", costsTableRead);
    readcsv("Institute.csv", instituteTableRead);
    readcsv("Transport.csv", transportTableRead);
    readcsv("Workdays.csv", workdaysTableRead);
}
