#include "Database.h"


Database::Database()
{

}

bool Database::SaveUserToDatabase(const UserInformation &user)
{
    QSqlQuery m_query;
    if(ChackIfUserExists(user)==false) {
        m_query.prepare("INSERT INTO Users(login,password,name) VALUES(?,?,?);");
        m_query.addBindValue(QString::fromLocal8Bit(user.GetLogin().c_str()));
        m_query.addBindValue(QString::fromLocal8Bit(user.GetPass().c_str()));
        m_query.addBindValue(QString::fromLocal8Bit(user.GetName().c_str()));
        if(m_query.exec())
        {
            qDebug()<<"true";
            return true;
        }
        else
        {
            qDebug() << "SaveUserToDatabase error:"
                     << m_query.lastError();
        }
    }
    else
    {
        return false;
    }
}

ServerLogInNotification::Response Database::VerificationOfLoginDetails(const UserInformation &user)
{
    QSqlQuery query;
    if(ChackIfUserExists(user)==true)
    {
        query.prepare("SELECT login,password FROM Users WHERE (login=?,password=?);");
        query.addBindValue(QString::fromLocal8Bit(user.GetLogin().c_str()));
        query.addBindValue(QString::fromLocal8Bit(user.GetPass().c_str()));
        query.exec();
        while(query.next()){
            if(user.GetLogin()==query.value(0).toString().toStdString()&& user.GetPass()==query.value(1).toString().toStdString())
            {
                qDebug()<<"ServerLogInNotification_Response_AUTHORIZATION_IS_SUCCESFUL\n";
                return ServerLogInNotification_Response_AUTHORIZATION_IS_SUCCESFUL;
            }
            else
            {
                qDebug()<<"ServerLogInNotification_Response_AUTHORIZATION_FAILD\n";
                return ServerLogInNotification_Response_AUTHORIZATION_FAILD;
            }
        }
    }
    else
    {
        qDebug()<<"ServerLogInNotification_Response_USER_NOT_FOUND\n";
        return ServerLogInNotification_Response_USER_NOT_FOUND;
    }
}

std::vector<std::string> Database::GetUsers()
{
    std::vector<std::string> users;
    QSqlQuery query;
    query.prepare("SELECT name FROM Users;");
    query.exec();
    while(query.next())
    {
       qDebug()<<query.value(0).toString();
       users.push_back(query.value(0).toString().toStdString());
    }
    return users;
}

Database *Database::operator->()
{
    return this;
}

bool Database::ChackIfUserExists(const UserInformation &user)
{
    QSqlQuery m_query;
    //bool searchResult=false;
    m_query.prepare("SELECT login FROM Users WHERE login=?");
    m_query.addBindValue(QString::fromLocal8Bit(user.GetLogin().c_str()));
    m_query.exec();
    if(m_query.first())
    {
        qDebug()<<"User exists";
        return true;
    }
    else
    {
        qDebug()<<"User don`t exists"<<" "<<m_query.lastError();
        return false;
    }
}

