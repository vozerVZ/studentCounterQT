#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databaseHandler.h"
#include <QMainWindow>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseHandler _db, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCalculate_clicked();


    void on_horizontalSliderAge_valueChanged(int value);

    void on_pushButtonWorkDir_clicked();

    void on_horizontalSliderMonth_valueChanged(int value);

private:
    DatabaseHandler db;
    Ui::MainWindow *ui;
    void loadTips();
};
#endif // MAINWINDOW_H
