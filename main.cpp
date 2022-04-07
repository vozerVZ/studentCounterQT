#include "mainwindow.h"
#include <QApplication>


int main(int argc, char* argv[]){
    QApplication a(argc, argv);
    DatabaseHandler db;
    MainWindow w(db);
    w.show();

    return a.exec();
}
