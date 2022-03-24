#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler.h"
#include "student.h"
#include <vector>
#include <iostream>
#include <QComboBox>
#include <QMessageBox>
MainWindow::MainWindow(DatabaseHandler _db, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    db = _db;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTips()
{
    vector<vector<std::string>> cities;
    db.readcsv("Caffe-and-cinema.csv", cities);
    std::cout << "mas size " << cities.size() << std::endl;
    for(std::size_t i = 1; i < cities.size(); i++){
        std::cout << cities[i][1] << std::endl;
        if(ui->comboBoxCity->findText(QString::fromStdString(cities[i][0])) == -1)
            ui->comboBoxCity->addItem(QString::fromStdString(cities[i][0]));
        if(ui->comboBoxCity->findText(QString::fromStdString(cities[i][1])) == -1)
            ui->comboBoxDistrict->addItem(QString::fromStdString(cities[i][1]));
        if(ui->comboBoxCity->findText(QString::fromStdString(cities[i][2])) == -1)
            ui->comboBoxCafe->addItem(QString::fromStdString(cities[i][2]));
        if(ui->comboBoxCity->findText(QString::fromStdString(cities[i][4])) == -1)
            ui->comboBoxCinema->addItem(QString::fromStdString(cities[i][4]));
    }
}

void MainWindow::on_pushButtonCalculate_clicked()
{
    int age = ui->label_age->text().toInt();
    std::string name = ui->lineName->text().toStdString();
    Student student(age, name);
    int month = ui->label_month->text().toInt();
    std::string city = ui->comboBoxCity->currentText().toStdString();
    std::string homeAddress = ui->comboBoxDistrict->currentText().toStdString();
    std::string cinema = ui->comboBoxCinema->currentText().toStdString();
    std::string institute = "MIREA";
    std::string coffee = ui->comboBoxCafe->currentText().toStdString();
    int costs = student.getCosts(month, city, homeAddress, institute, cinema, coffee, db);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результат");
    msgBox.setText("Привет, "+QString::fromStdString(student.getName())+"! Ты тратишь "+QString::number(costs)+" рублей в месяц.");
    msgBox.exec();
}


void MainWindow::on_horizontalSliderAge_valueChanged(int value)
{
    ui->label_age->setText(QString::number(value));
}


void MainWindow::on_pushButtonWorkDir_clicked()
{
    QString workDir = QFileDialog::getExistingDirectory();
    db.setWorkDir(workDir.toStdString().append("/"));
    loadTips();
    ui->label_dir->setText(workDir);
    ui->label_dir->adjustSize();
}


void MainWindow::on_horizontalSliderMonth_valueChanged(int value)
{
    ui->label_month->setText(QString::number(value));
}

