#include "csvedit.h"
#include "ui_csvedit.h"
#include <vector>

using std::vector;

CsvEdit::CsvEdit(std::string& filename, DatabaseHandler& db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CsvEdit)
{

    _filename = filename;
    _db = db;
    ui->setupUi(this);
    LoadTable();
}

CsvEdit::~CsvEdit()
{
    delete ui;
}

void CsvEdit::LoadTable(){
    ui->labelTable->setText(QString::fromStdString(_filename));
    vector<vector<std::string>> vecTable;
    _db.readcsv(_filename, vecTable);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setColumnCount(vecTable[0].size());
    ui->tableWidget->setRowCount(vecTable.size() - 1);
    for(std::size_t i = 0; i < vecTable[0].size(); i++){
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(QString::fromStdString(vecTable[0][i])));

    }
    for(std::size_t i = 1; i < vecTable.size(); i++){
        for(std::size_t j = 0; j < vecTable[i].size(); j++){
            ui->tableWidget->setItem(i - 1, j, new QTableWidgetItem(QString::fromStdString(vecTable[i][j])));
        }
    }

}

void CsvEdit::on_buttonBoxTable_accepted()
{
    vector<vector<std::string>> vecTable;
    int rows_count = ui->tableWidget->rowCount();
    int column_count = ui->tableWidget->colorCount();
    for(int row_ = 0; row_ < rows_count; row_++){
        std::
        vector<std::string> row;
        for(int column_ = 0; column_ < column_count; column_++){
            row.push_back(ui->tableWidget->item(row_, column_)->text().toStdString());
        }
        vecTable.push_back(row);
        row.clear();
    }

}



void CsvEdit::WriteTable(vector<vector<std::string>> &data){
    std::ofstream myfile;
    std::cout << "начал сосать зуй" << "\n";
    myfile.open("test.csv");
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j){
            std::cout << data[i][j] << ",";
        }
        std::cout << "\n";
    }
}

