#include <QCoreApplication>
#include "Server.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>


static void connectToDatabase(const QString& databaseName)
{
    QSqlDatabase database = QSqlDatabase::database();
    if (!database.isValid()) {
        database = QSqlDatabase::addDatabase("QSQLITE");
        if (!database.isValid())
            qFatal("Cannot add database: %s", qPrintable(database.lastError().text()));
    }
    // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
    database.setDatabaseName(databaseName);
    if (!database.open()) {
        qFatal("Cannot open database: %s", qPrintable(database.lastError().text()));
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    connectToDatabase("/home/dima/Documents/Messenger/usersDatabase.sqlite3");
    Server server;
    return a.exec();
}
