#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databaseHandler.h"
#include "csvread.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <stdio.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(DatabaseHandler& db, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCalculate_clicked();

    void on_pushButtonWorkDir_clicked();

    void on_buttonEdit_clicked();

    void on_radioButton_clicked();

    void on_radioButtonAge_toggled(bool checked);

    void on_lineName_textEdited(const QString &arg1);

    void on_lineMonth_textEdited(const QString &arg1);

private:
    DatabaseHandler _db;
    CsvRead* _readerCaffe;
    CsvRead* _readerCosts;
    CsvRead* _readerInstitute;
    CsvRead* _readerTransport;
    CsvRead* _readerWorkdays;

    Ui::MainWindow* _ui;
    void loadTips();
    void checkReadyButton();
};
#endif // MAINWINDOW_H
