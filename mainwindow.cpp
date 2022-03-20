#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler.h"
#include <vector>
#include <iostream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadTips();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadTips()
{
    vector<vector<std::string>> cities;
    readcsv("Caffe-and-cinema.csv", cities);
    std::cout << "mas size " << cities.size() << std::endl;
    for(std::size_t i = 0; i < cities.size(); i++){
        std::cout << cities[i][1] << std::endl;
        ui->comboBoxCity->addItem(QString::fromStdString(cities[i][0]));
        ui->comboBoxDistrict->addItem(QString::fromStdString(cities[i][1]));
        ui->comboBoxCafe->addItem(QString::fromStdString(cities[i][2]));
        ui->comboBoxCinema->addItem(QString::fromStdString(cities[i][4]));
    }
}

void MainWindow::on_pushButtonCalculate_clicked()
{

}


