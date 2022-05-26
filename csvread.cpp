#include "csvread.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDebug>
CsvRead::CsvRead(const string& filename){
    _filename = filename;
}

void CsvRead::setWorkDir(string workDir){
    _workDir = workDir;
}

string CsvRead::getWorkDir() const{
    return _workDir;
}

vector<vector<string>> CsvRead::getTable() const{
    return _table;
}

void CsvRead::readcsv(){
    ifstream fs(_workDir + _filename);
    if (!fs.is_open()){
        throw "File not opened";
    }
    string BigStr;
    vector<string> selements;
    _table.clear();
    while (getline(fs, BigStr)){
        string ThsStr;
        stringstream lineStream(BigStr);
        while (getline(lineStream, ThsStr, ',')){
            selements.push_back(ThsStr);
        }
        _table.push_back(selements);
        selements.clear();
    }
}

void CsvRead::writeTable(vector<vector<QString>>& vecTable){
    QString filename = QString::fromStdString(_workDir.append(_filename));

    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for (size_t i = 0; i < vecTable.size(); ++i) {
            for (size_t j = 0; j < vecTable[i].size(); ++j){
                stream << vecTable[i][j] << ",";
            }
            stream << "\n";
        }
    }

    //this->parent();
}

