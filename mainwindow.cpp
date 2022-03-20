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
    readcsv("C:\\Caffe-and-cinema.csv", cities);
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

}



void MainWindow::on_pushButtonTransport_clicked()
{
    QString file1Name = QFileDialog::getOpenFileName(this);

    ui->label_transport->setText(file1Name);
    ui->label_transport->adjustSize();
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    ui->label_age->setText(QString::number(value));
}

