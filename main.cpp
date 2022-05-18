#include "mainwindow.h"
#include <QApplication>


int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    CsvRead reader;
    DatabaseHandler db;
    MainWindow w(db, reader);
    w.show();

    return a.exec();
}
