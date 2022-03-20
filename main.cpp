#include "mainwindow.h"

#include <QApplication>

#include <iostream>
#include <string>
#include <filesystem>
#include <unistd.h>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::current_path;

int main(int argc, char *argv[])
{
    cout << "Current working directory: " << current_path() << endl;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
