#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasehandler.h"
#include "csvedit.h"
#include "student.h"
#include <vector>
#include <iostream>
#include <QComboBox>
#include <QCompleter>

#include <QMessageBox>


using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

MainWindow::MainWindow(DatabaseHandler& db, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    _db = db;
    ui->setupUi(this);

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::loadTips(){
    vector<vector<std::string>> cities;
    _db.readcsv("Caffe-and-cinema.csv", cities);
    ui->comboBoxCity->clear();
    ui->comboBoxDistrict->clear();
    ui->comboBoxCafe->clear();
    ui->comboBoxCinema->clear();
    ui->comboBoxInstitute->clear();
    QStringList wordList;
    for(std::size_t i = 1; i < cities.size(); i++){
        if(ui->comboBoxCity->findText(QString::fromStdString(cities[i][0])) == -1){
            ui->comboBoxCity->addItem(QString::fromStdString(cities[i][0]));
        }
        if(ui->comboBoxDistrict->findText(QString::fromStdString(cities[i][1])) == -1){
            ui->comboBoxDistrict->addItem(QString::fromStdString(cities[i][1]));
        }
        if(ui->comboBoxCafe->findText(QString::fromStdString(cities[i][2])) == -1){
            ui->comboBoxCafe->addItem(QString::fromStdString(cities[i][2]));
        }
        if(ui->comboBoxCinema->findText(QString::fromStdString(cities[i][4])) == -1){
            ui->comboBoxCinema->addItem(QString::fromStdString(cities[i][4]));
        }
    }
    vector<vector<std::string>> institute;
    _db.readcsv("Institute.csv", institute);
    for(std::size_t i = 1; i < institute.size(); i++){
        if(ui->comboBoxInstitute->findText(QString::fromStdString(institute[i][1])) == -1){
            ui->comboBoxInstitute->addItem(QString::fromStdString(institute[i][1]));
        }
    }
    vector<vector<std::string>> month;
    _db.readcsv("Workdays.csv", month);
    for(std::size_t i = 1; i < month.size(); i++){
        wordList << QString::fromStdString(month[i][3]);
    }
    QCompleter *test = new QCompleter(wordList);

    ui->lineMonth->setCompleter(test);
    checkReadyButton();
}

void MainWindow::on_pushButtonCalculate_clicked(){
    int age = ui->spinBoxAge->value();
    std::string name = ui->lineName->text().toStdString();
    Student student(age, name);
    std::string month = ui->lineMonth->text().toStdString();
    std::string city = ui->comboBoxCity->currentText().toStdString();
    std::string homeAddress = ui->comboBoxDistrict->currentText().toStdString();
    std::string cinema = ui->comboBoxCinema->currentText().toStdString();
    std::string institute = ui->comboBoxInstitute->currentText().toStdString();
    std::string coffee = ui->comboBoxCafe->currentText().toStdString();
    int costs = student.getCosts(month, city, homeAddress, institute, cinema, coffee, _db);
    QMessageBox msgBox;
    msgBox.setWindowTitle("Результат");
    msgBox.setText("Привет, " + QString::fromStdString(student.getName()) + "! Ты тратишь "+QString::number(costs) + " рублей в месяц.");
    msgBox.exec();
}

void MainWindow::checkReadyButton(){
    if(!ui->lineName->text().isEmpty() && !ui->lineMonth->text().isEmpty()){
        ui->pushButtonCalculate->setEnabled(true);
    }
}

void MainWindow::on_pushButtonWorkDir_clicked(){
    QString workDir = QFileDialog::getExistingDirectory();
    std::string path = workDir.toStdString().append("/");
    for (const auto & file : directory_iterator(path)){
        std::string efilename = file.path().filename().string();
        if(efilename.find(".csv")!= std::string::npos){
            ui->comboBoxFile->addItem(QString::fromStdString(efilename));
        }
    }
    _db.setWorkDir(path);
    loadTips();
    ui->label_dir->setText(workDir);
    ui->label_dir->adjustSize();
}

void MainWindow::on_buttonEdit_clicked(){
    std::string efilename = ui->comboBoxFile->currentText().toStdString();
    CsvEdit csvedit(efilename, _db, this);
    csvedit.setModal(true);
    csvedit.exec();
    loadTips();
}

void MainWindow::on_radioButton_clicked(){
}

void MainWindow::on_radioButtonAge_toggled(bool checked){
    if(checked){
        ui->spinBoxAge->setEnabled(true);
    }
    else{
        ui->spinBoxAge->setEnabled(false);
    }
    checkReadyButton();
}

void MainWindow::on_lineName_textEdited(const QString &arg1){
}

void MainWindow::on_lineMonth_textEdited(const QString &arg1){
    checkReadyButton();
}
