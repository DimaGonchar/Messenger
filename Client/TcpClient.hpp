#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "Client.pb.h"
#include "Server.pb.h"

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

struct UserInformation
{
     QString login;
     QString pass;
};


class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject* parent = nullptr);
    ~TcpClient();
signals:
    void newMessage(const QByteArray& str);
    void logIn();
    void signUp();

public slots:
    void connectToServer();
    void sendMessage(const QString& message);
    void login(const QString& userLogin, const QString& userPass);
    void registration(const QString& login, const QString& pass);
private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);
private:void SendLoginIn(const std::string& login, const std::string& pass);
private:void RegistrationUser(const std::string& login, const std::string& pass);
private:
    QTcpSocket* m_socket;
    QByteArray m_dataFromServer;
    std::vector<char> m_requestForServer;
    QString m_ip="192.168.56.1";
    std::int64_t m_port = 45000;
    UserInformation m_uInform;
    ProtoClient m_client;
};

#endif // TCPCLIENT_HPP
