#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QIODeviceBase>
#include <iostream>

using namespace std;

#define QSS_FILE "ManjaroMix.qss"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QString dir = a.applicationDirPath();
    QFile file(dir + "/QSS-master/" + QSS_FILE);
    if (file.open(QIODeviceBase::ReadOnly))
    {
        QString txt = QString(file.readAll());
        //cout << txt.toStdString() << endl;
        //a.setStyleSheet(txt);
    }
    return a.exec();
}
