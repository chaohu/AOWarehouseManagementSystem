#include "mainwindow.h"
#include <QApplication>
#include "logindialog.h"
//#include <QStringList>
//#include <QSqlDatabase>
//#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog ldlg;
    if(ldlg.exec() == QDialog::Accepted) {
//        QStringList drivers = QSqlDatabase::drivers();
//        foreach (QString driver, drivers) {
//            qDebug()<<driver;
//        }
//        QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
//        qDebug()<<db.isValid();
        MainWindow w;
        w.show();
        return a.exec();
    }
    else return 0;
}
