#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "databaseHandler.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(DatabaseHandler& db, QWidget* parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonCalculate_clicked();

    void on_horizontalSliderAge_valueChanged(int value);

    void on_pushButtonWorkDir_clicked();

    void on_buttonEdit_clicked();

private:
    DatabaseHandler _db;
    Ui::MainWindow* ui;
    void loadTips();
};
#endif // MAINWINDOW_H
