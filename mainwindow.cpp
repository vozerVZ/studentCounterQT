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
    : QMainWindow(parent),
    _db(db),
    _ui(new Ui::MainWindow){
    _db = db;
    _readerCaffe = new CsvRead("Caffe-and-cinema.csv");
    _readerCosts = new CsvRead("Costs.csv");
    _readerInstitute = new CsvRead("Institute.csv");
    _readerTransport = new CsvRead("Transport.csv");
    _readerWorkdays = new CsvRead("Workdays.csv");
    _ui->setupUi(this);
    this->setWindowTitle("Твоя цена");
}

MainWindow::~MainWindow(){
    delete _ui;
    delete _readerCaffe;
    delete _readerCosts;
    delete _readerInstitute;
    delete _readerTransport;
    delete _readerWorkdays;
}

void MainWindow::loadTips(){
    _ui->comboBoxCity->clear();
    _ui->comboBoxDistrict->clear();
    _ui->comboBoxCafe->clear();
    _ui->comboBoxCinema->clear();
    _ui->comboBoxInstitute->clear();
    QStringList wordList;
    for(std::size_t i = 1; i < _readerCaffe->getTable().size(); i++){
        if(_ui->comboBoxCity->findText(QString::fromStdString(_readerCaffe->getTable()[i][0])) == -1){
            _ui->comboBoxCity->addItem(QString::fromStdString(_readerCaffe->getTable()[i][0]));
        }
        if(_ui->comboBoxDistrict->findText(QString::fromStdString(_readerCaffe->getTable()[i][1])) == -1){
            _ui->comboBoxDistrict->addItem(QString::fromStdString(_readerCaffe->getTable()[i][1]));
        }
        if(_ui->comboBoxCafe->findText(QString::fromStdString(_readerCaffe->getTable()[i][2])) == -1){
            _ui->comboBoxCafe->addItem(QString::fromStdString(_readerCaffe->getTable()[i][2]));
        }
        if(_ui->comboBoxCinema->findText(QString::fromStdString(_readerCaffe->getTable()[i][4])) == -1){
            _ui->comboBoxCinema->addItem(QString::fromStdString(_readerCaffe->getTable()[i][4]));
        }
    }

    for(std::size_t i = 1; i < _readerInstitute->getTable().size(); i++){
        if(_ui->comboBoxInstitute->findText(QString::fromStdString(_readerInstitute->getTable()[i][1])) == -1){
            _ui->comboBoxInstitute->addItem(QString::fromStdString(_readerInstitute->getTable()[i][1]));
        }
    }

    for(std::size_t i = 1; i < _readerWorkdays->getTable().size(); i++){
        wordList << QString::fromStdString(_readerWorkdays->getTable()[i][3]);
    }
    QCompleter *test = new QCompleter(wordList);
    test->setCaseSensitivity(Qt::CaseSensitivity());
    _ui->lineMonth->setCompleter(test);
    checkReadyButton();
}

void MainWindow::on_pushButtonCalculate_clicked(){
    int age = 0;
    if(_ui->radioButtonAge->isChecked()){
        age = _ui->spinBoxAge->value();
    }
    std::string name = _ui->lineName->text().toStdString();
    Student student(age, name);
    std::string month = _ui->lineMonth->text().toStdString();
    std::string city = _ui->comboBoxCity->currentText().toStdString();
    std::string homeAddress = _ui->comboBoxDistrict->currentText().toStdString();
    std::string cinema = _ui->comboBoxCinema->currentText().toStdString();
    std::string institute = _ui->comboBoxInstitute->currentText().toStdString();
    std::string coffee = _ui->comboBoxCafe->currentText().toStdString();
    int costs;
    QMessageBox msgBox;
    try {
        costs = student.getCosts(month, city, homeAddress, institute, cinema, coffee, _db,
            *_readerCaffe, *_readerCosts, *_readerInstitute, *_readerTransport, *_readerWorkdays);
        if(costs > 0){
            msgBox.setText("Привет, " + QString::fromStdString(student.getName()) + "! Ты тратишь "+ QString::number(costs) + " рублей в месяц.");
        }
        else{
            msgBox.setText("Ошибка: данные введены неверно");
            msgBox.setStyleSheet("color: red;");
        }
    }  catch (const std::exception& e) {
        msgBox.setText("Ошибка в функции: " + QString(e.what()));
        msgBox.setStyleSheet("color: red;");
    }

    msgBox.setWindowTitle("Результат");

    msgBox.exec();
}

void MainWindow::checkReadyButton(){
    if(!_ui->lineName->text().isEmpty() && !_ui->lineMonth->text().isEmpty() && _readerCaffe->getWorkDir().size() != 0){
        _ui->pushButtonCalculate->setEnabled(true);
    }
}

void MainWindow::on_pushButtonWorkDir_clicked(){
    QString workDir = QFileDialog::getExistingDirectory();
    std::string path = workDir.toStdString().append("/");
    for (const auto & file : directory_iterator(path)){
        std::string efilename = file.path().filename().string();
        if(efilename.find(".csv") != std::string::npos){
            _ui->comboBoxFile->addItem(QString::fromStdString(efilename));
        }
    }
    try{
        _readerCaffe->setWorkDir(path);
        _readerCaffe->readcsv();
        _readerCosts->setWorkDir(path);
        _readerCosts->readcsv();
        _readerInstitute->setWorkDir(path);
        _readerInstitute->readcsv();
        _readerTransport->setWorkDir(path);
        _readerTransport->readcsv();
        _readerWorkdays->setWorkDir(path);
        _readerWorkdays->readcsv();
        loadTips();
        _ui->buttonEdit->setEnabled(true);
        _ui->label_dir->setText(workDir);
        _ui->label_dir->adjustSize();
    }
    catch(const char* e){
        _readerCaffe->setWorkDir("");
        _readerCosts->setWorkDir("");
        _readerInstitute->setWorkDir("");
        _readerTransport->setWorkDir("");
        _readerWorkdays->setWorkDir("");
        QMessageBox msgBox;
        msgBox.setText(QString(e));
        msgBox.setStyleSheet("color: red;");
        msgBox.setWindowTitle("Ошибка");
        msgBox.exec();
    }
}

void MainWindow::on_buttonEdit_clicked(){
    std::string efilename = _ui->comboBoxFile->currentText().toStdString();
    if(efilename == "Caffe-and-cinema.csv"){
        CsvEdit csvedit(efilename, _db, *_readerCaffe, this);
        csvedit.setModal(true);
        csvedit.exec();
        _readerCaffe->readcsv();
    }
    else if(efilename == "Costs.csv"){
        CsvEdit csvedit(efilename, _db, *_readerCosts, this);
        csvedit.setModal(true);
        csvedit.exec();
        _readerCosts->readcsv();
    }
    else if(efilename == "Institute.csv"){
        CsvEdit csvedit(efilename, _db, *_readerInstitute, this);
        csvedit.setModal(true);
        csvedit.exec();
        _readerInstitute->readcsv();
    }
    else if(efilename == "Transport.csv"){
        CsvEdit csvedit(efilename, _db, *_readerTransport, this);
        csvedit.setModal(true);
        csvedit.exec();
        _readerTransport->readcsv();
    }
    else if(efilename == "Workdays.csv"){
        CsvEdit csvedit(efilename, _db, *_readerWorkdays, this);
        csvedit.setModal(true);
        csvedit.exec();
        _readerWorkdays->readcsv();
    }
    loadTips();
}

void MainWindow::on_radioButton_clicked(){
}

void MainWindow::on_radioButtonAge_toggled(bool checked){
    if(checked){
        _ui->spinBoxAge->setEnabled(true);
    }
    else{
        _ui->spinBoxAge->setEnabled(false);
    }
    checkReadyButton();
}

void MainWindow::on_lineName_textEdited(const QString &arg1){
    checkReadyButton();
}

void MainWindow::on_lineMonth_textEdited(const QString &arg1){
    checkReadyButton();
}
