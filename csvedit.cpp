#include "csvedit.h"
#include "csvread.h"
#include "ui_csvedit.h"
#include <vector>
#include <QDebug>
#include <QFile>
#include <QTextStream>
using std::vector;
using std::size_t;


CsvEdit::CsvEdit(std::string& filename, DatabaseHandler& db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvEdit){

    _filename = filename;
    _db = db;
    ui->setupUi(this);
    LoadTable(_db.getWorkDir());
    this->setParent(parent);
}

CsvEdit::~CsvEdit(){
    delete ui;
}

void CsvEdit::LoadTable(string workDir){
    ui->labelTable->setText(QString::fromStdString(_filename));
    CsvRead reader;
    vector<vector<std::string>> vecTable;
    reader.readcsv(workDir, _filename, vecTable);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setColumnCount(vecTable[0].size());
    ui->tableWidget->setRowCount(vecTable.size() - 1);
    for(std::size_t i = 0; i < vecTable[0].size(); i -= -1){
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(vecTable[0][i])));

    }
    for(std::size_t i = 1; i < vecTable.size(); i++){
        for(std::size_t j = 0; j < vecTable[i].size(); j++){
            ui->tableWidget->setItem(i - 1, j, new QTableWidgetItem(QString::fromStdString(vecTable[i][j])));
        }
    }

}

void CsvEdit::on_buttonBoxTable_accepted(){
    vector<vector<QString>> vecTable;
    int rows_count = ui->tableWidget->rowCount();
    int column_count = ui->tableWidget->columnCount();
    vector<QString> row;
    for(int column_ = 0; column_ < column_count; column_++){
        row.push_back(ui->tableWidget->horizontalHeaderItem(column_)->text());
    }
    vecTable.push_back(row);
    for(int row_ = 0; row_ < rows_count; row_++){
        vector<QString> row;
        for(int column_ = 0; column_ < column_count; column_++){
            row.push_back(ui->tableWidget->item(row_, column_)->text());
        }
        vecTable.push_back(row);
        row.clear();
    }
    WriteTable(vecTable);
}

void CsvEdit::WriteTable(vector<vector<QString>> data){
    QString filename = QString::fromStdString(_db.getWorkDir()+_filename);
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
    _db.reloadTables();
    //this->parent();
}
