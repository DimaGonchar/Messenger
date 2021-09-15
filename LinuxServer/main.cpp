#include <QCoreApplication>
#include "Server.h"
#include <QtSql/QSqlDatabase>
#include <QDir>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QtSql/QSqlQuery>

static void connectToDatabase()
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName("/home/dima/Documents/Messenger/usersDatabase.sqlite3");
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
    }
    QSqlQuery query;
    query.prepare("SELECT *FROM Users WHERE login like:login");
    query.bindValue(":login",QString("dima"));
    if(query.exec())
    {
        qInfo()<<"true";
        if(query.first())
        {
            qDebug() << "login: " << query.value(1).toString();
        }
    }
    else
    {
        qDebug()<<"false "<<query.lastError();
    }
//    while(query.next()) {
//    QString id=query.value(0).toString();
//    QString login=query.value(1).toString();
//    QString pass=query.value(2).toString();
//    QString name=query.value(3).toString();
//    qInfo()<<id;
//    qInfo()<<login;
//    qInfo()<<pass;
//    qInfo()<<name;
//        QString  login=query.value(0).toString();
//        if(login=="sasha")
//        {
//            qInfo()<<"true";
//        }
//        else {
//            qInfo()<<login;
//        }
//    }
//    QString l="sasha";
//    query.prepare("INSERT INTO Users(login) VALUES(?);");
//    query.addBindValue(l);
//    if(query.exec())
//    {
//        qDebug()<<"true";
//    }
//    else
//    {
//         qDebug() << "addPerson error:"
//                  << query.lastError();
//    }
//    database.commit();
    database.close();
}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    connectToDatabase();
    //Server server;
    return a.exec();
}
