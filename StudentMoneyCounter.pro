QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csvedit.cpp \
    databasehandler.cpp \
    main.cpp \
    mainwindow.cpp \
    student.cpp

HEADERS += \
    csvedit.h \
    databasehandler.h \
    mainwindow.h \
    student.h

FORMS += \
    csvedit.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Caffe-and-cinema.csv \
    Costs.csv \
    Institute.csv \
    Transport.csv \
    Workdays.csv
