#ifndef CSVEDIT_H
#define CSVEDIT_H

#include <QDialog>
#include "databasehandler.h"
#include <QTableWidget>


namespace Ui {
class CsvEdit;
}

class CsvEdit : public QDialog{
    Q_OBJECT
public:
    explicit CsvEdit(std::string& filename, DatabaseHandler& db, QWidget *parent = nullptr);
    ~CsvEdit();
private slots:
    void on_buttonBoxTable_accepted();

private:
    Ui::CsvEdit* _ui;
    std::string _filename;
    DatabaseHandler _db;
    void LoadTable(string workDir);
    void WriteTable(vector<vector<QString>> data);
};

#endif // CSVEDIT_H
