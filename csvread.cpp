#include "csvread.h"
#include <QFile>
#include <QTextStream>

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

void CsvRead::WriteTable(vector<vector<QString>> data, std::string path){
    QString filename = QString::fromStdString(path);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream( &file );
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j){
                stream << data[i][j] << ",";
            }
            stream << "\n";
        }
    }

    //this->parent();
}
