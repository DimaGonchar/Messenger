#ifndef DATABASE_H
#define DATABASE_H

#pragma once
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QVariant>
#include "UserInformation.h"
#include "Server.pb.h"

class Database
{
public:
    Database();
    bool SaveUserToDatabase(const UserInformation& user);
    ServerLogInNotification::Response VerificationOfLoginDetails(const UserInformation& user);
    std::vector<std::string> GetUsers();
    Database* operator->();
private:bool ChackIfUserExists(const UserInformation& user);
};
#endif // DATABASE_H
