#ifndef SQLCONTACTMODEL_H
#define SQLCONTACTMODEL_H

#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QObject>
#include <QSqlError>
#include <QDebug>
#include <vector>

class SqlContactModel : public QSqlQueryModel
{
    Q_OBJECT
    Q_PROPERTY(QVector<QString> contacts READ contacts WRITE setContacts NOTIFY contactsChanged)

public:
    explicit SqlContactModel(QObject *parent = nullptr);
    QVector<QString> contacts() const
    {
        return m_contacts;
    }
    void setContacts(const QVector<QString> &contacts)
    {
        if (contacts == m_contacts)
            return;

        m_contacts =contacts;
        emit contactsChanged(m_contacts);
    }
    Q_INVOKABLE bool AddUserToDatabase(const std::string& name);
    Q_INVOKABLE bool LoadUsersToDatabase(const std::vector<std::string>& users);
signals:void contactsChanged(const QVector<QString>& contacts);
private:
    QVector<QString> m_contacts{"Dima","Anton","Sasha"};
};

#endif // SQLCONTACTMODEL_H
