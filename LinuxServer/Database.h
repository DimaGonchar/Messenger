#ifndef DATABASE_H
#define DATABASE_H

#pragma once
#include <QtSql/QSqlDatabase>
#include <QDir>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QVector>
#include <QVariant>
#include "UserInformation.h"

class Database
{
public:
    Database(const QString& databaseName):
        m_databaseName(databaseName)
    {
        Connect();
    }
 private: void Connect()
    {
        m_database = QSqlDatabase::database();
        if (!m_database.isValid()) {
            m_database = QSqlDatabase::addDatabase("QSQLITE");
            if (!m_database.isValid())
                qFatal("Cannot add database: %s", qPrintable(m_database.lastError().text()));
        }
        // When using the SQLite driver, open() will create the SQLite database if it doesn't exist.
        m_database.setDatabaseName(m_databaseName);
        if (!m_database.open()) {
            qFatal("Cannot open database: %s", qPrintable(m_database.lastError().text()));
        }
    }
public:
    bool SaveUserToDatabase(const UserInformation& user)
    {
      if(ChackIfUserExists(user)==false) {
        m_query.prepare("INSERT INTO Users(login,password,name) VALUES(?,?,?);");
        m_query.addBindValue(QString::fromLocal8Bit(user.GetLogin().c_str()));
        m_query.addBindValue(QString::fromLocal8Bit(user.GetPass().c_str()));
        m_query.addBindValue(QString::fromLocal8Bit(user.GetName().c_str()));
        if(m_query.exec())
        {
            qDebug()<<"true";
            m_database.commit();
            return true;
        }
        else
        {
             qDebug() << "addPerson error:"
                      << m_query.lastError();
        }
      }
      else
      {
          return false;
      }
    }
private:bool ChackIfUserExists(const UserInformation& user)
    {
        bool searchResult=false;
        m_query.exec("SELECT login FROM Users WHERE login=?");
        m_query.addBindValue(QString::fromLocal8Bit(user.GetLogin().c_str()));
        while(m_query.next())
        {
           if(user.GetLogin()==m_query.value(0).toString().toStdString())
           {
               return true;
           }
        }
        return searchResult;
    }
public: Database* operator->()
    {
        return this;
    }
private:
   QSqlDatabase m_database;
   const QString m_databaseName;
   QSqlQuery m_query;
};

#endif // DATABASE_H
