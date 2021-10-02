#include <QTcpSocket>
#include <QString>
#include "Client.pb.h"
#include "Server.pb.h"
#include "NotificationTupeMoc.pb.h"
#include "SqlContactModel.h"

#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

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
    void errorMessage(const QString& error);
    void newUser(const QString& user);
public slots:
    void connectToServer();
    void sendMessage(const QString& message);
    void login(const QString& userLogin, const QString& userPass);
    void regestration(const QString& userLogin, const QString& userPass, const QString& confirmPass, const QString& userName);
private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);
private:void SendLoginIn(const std::string& login, const std::string& pass);
private:void RegestrationUser(const std::string& login, const std::string& pass, const std::string& name);
private:
    QTcpSocket* m_socket;
    QByteArray m_dataFromServer;
    std::vector<char> m_requestForServer;
    QString m_ip="127.0.0.1";//"192.168.56.1"
    std::int64_t m_port = 45000;
    ClientSendMessageNotification m_sendMess;
    //NotificationTupeMoc m_tMoc;
    ServerRegistrationNotification m_regNotif;
    //ServerLogInNotification m_signInNotif;
     NewUserConnectNotification user;
     SqlContactModel* contacts=nullptr;
};

#endif // TCPCLIENT_HPP
