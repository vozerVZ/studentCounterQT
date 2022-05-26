#include "csvedit.h"
#include "csvread.h"
#include "ui_csvedit.h"
#include <vector>

using std::vector;
using std::size_t;


CsvEdit::CsvEdit(const std::string& filename, DatabaseHandler& db, CsvRead& reader, QWidget* parent) :
    QDialog(parent),
    _db(db),
    _reader(reader),
    _ui(new Ui::CsvEdit){
    _filename = filename,
    _db = db,
    _reader = reader,
    _ui->setupUi(this);
    loadTable();
    this->setParent(parent);
}

CsvEdit::~CsvEdit(){
    delete _ui;
}

void CsvEdit::loadTable(){
    _ui->labelTable->setText(QString::fromStdString(_filename));
    vector<vector<std::string>> vecTable = _reader.getTable();

    _ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    _ui->tableWidget->verticalHeader()->hide();
    _ui->tableWidget->setColumnCount(vecTable[0].size());
    _ui->tableWidget->setRowCount(vecTable.size() - 1);
    for(std::size_t i = 0; i < vecTable[0].size(); i -= -1){
        _ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(vecTable[0][i])));

    }
    for(std::size_t i = 1; i < vecTable.size(); i++){
        for(std::size_t j = 0; j < vecTable[i].size(); j++){
            _ui->tableWidget->setItem(i - 1, j, new QTableWidgetItem(QString::fromStdString(vecTable[i][j])));
        }
    }

}

void CsvEdit::on_buttonBoxTable_accepted(){
    vector<vector<QString>> vecTable;
    int rows_count = _ui->tableWidget->rowCount();
    int column_count = _ui->tableWidget->columnCount();
    vector<QString> row;
    for(int column_ = 0; column_ < column_count; column_++){
        row.push_back(_ui->tableWidget->horizontalHeaderItem(column_)->text());
    }
    vecTable.push_back(row);
    for(int row_ = 0; row_ < rows_count; row_++){
        vector<QString> row;
        for(int column_ = 0; column_ < column_count; column_++){
            row.push_back(_ui->tableWidget->item(row_, column_)->text());
        }
        vecTable.push_back(row);
        row.clear();
    }
    _reader.writeTable(vecTable);
}

