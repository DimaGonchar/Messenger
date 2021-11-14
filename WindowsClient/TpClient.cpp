#include "TcpClient.hpp"
#include "NotificationType.hpp"
#include <QDebug>
#include <memory>

TcpClient::TcpClient(QObject* parent) : QObject(parent)
{
     m_socket=new QTcpSocket;
    connectToServer();
    connect(m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}
TcpClient::~TcpClient()
{
    delete m_socket;
}
void TcpClient::connectToServer()
{
    m_socket->connectToHost(m_ip,m_port);
}

void TcpClient::login(const QString& userLogin, const QString& userPass)
{
    if(userLogin.isEmpty())
    {
        emit newMessage("empty login!");
    }
    if(userPass.isEmpty())
    {
        emit newMessage("empty password!");
    }
    else if(!userLogin.isEmpty()&&!userPass.isEmpty())
    {
    SendLoginIn(userLogin.toStdString(),userPass.toStdString());
    }
}

void TcpClient::SendLoginIn(const std::string& login, const std::string& pass)
{
        qInfo()<<"sended sign in";
        ClientSignInNotification signInNotification;
        signInNotification.set_login(login);
        signInNotification.set_pass(pass);
        signInNotification.set_typenotification(NotificationType::SignIn);
        m_requestForServer.resize(signInNotification.ByteSizeLong());
        signInNotification.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
        m_socket->write(static_cast<QByteArray>(&m_requestForServer[0]),m_requestForServer.size());
}
void TcpClient::regestration(const QString& userLogin, const QString& userPass, const QString& userName)
{
    if(userLogin.isEmpty())
    {
        emit newMessage("empty login!");
    }
    if(userPass.isEmpty())
    {
        emit newMessage("empty password!");
    }
    else if(!userLogin.isEmpty()&&!userPass.isEmpty())
    {
      RegestrationUser(userLogin.toStdString(),userPass.toStdString(), userName.toStdString());
    }
}
void TcpClient::RegestrationUser(const std::string& login, const std::string& pass, const std::string& name)
{
    qInfo()<<"sended sign up";
    ClientRegistrationNotification regNotification;
    regNotification.set_typenotification(NotificationType::Registration);
    regNotification.set_login(login);
    regNotification.set_username(name);
    regNotification.set_pass(pass);
    m_requestForServer.resize(regNotification.ByteSizeLong());
    regNotification.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
    m_socket->write(static_cast<QByteArray>(&m_requestForServer[0]),m_requestForServer.size());
}
void TcpClient::sendMessage(const QString& message)
{
    m_sendMess.set_typenotification(NotificationType::Message);
    m_sendMess.set_text(message.toStdString());
    m_requestForServer.resize(m_sendMess.ByteSizeLong());
    m_sendMess.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
    m_socket->write(static_cast<QByteArray>(&m_requestForServer[0]),m_requestForServer.size());
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host.";
}

void TcpClient::onReadyRead()
{
    m_dataFromServer.append(m_socket->readAll());
    qInfo()<<m_dataFromServer;
    NotificationTupeMoc m_tMoc;
    m_tMoc.ParseFromArray(m_dataFromServer, m_dataFromServer.size());
    const auto type= static_cast<NotificationType>(m_tMoc.typenotification());

    if(type==NotificationType::Registration)
    {

        qInfo()<<"regestration";
        m_regNotif.ParseFromArray(m_dataFromServer, m_dataFromServer.size());
        if(m_regNotif.response()==ServerRegistrationNotification_Response_USER_EXISTS)
        {
            qInfo()<<"user exists!";
            emit errorMessage("user already exists!");
            return;
        }
            qInfo()<<"succesful";
            emit signUp();
    }

    if(type==NotificationType::SignIn)
    {
        qInfo()<<"sign in";
        m_signInNotif.ParseFromArray(m_dataFromServer, m_dataFromServer.size());
        if(m_signInNotif.respose()==ServerLogInNotification_Response_USER_NOT_FOUND)
        {
            qInfo()<<"user not founded";
            emit errorMessage("user not founded");
            return;
        }
        if(m_signInNotif.respose()==ServerLogInNotification_Response_AUTHORIZATION_FAILD)
        {
            qInfo()<<"no correct login or password";
            emit errorMessage("no correct login or password");
            return;
        }
            qInfo()<<"succesful";
            emit logIn();
    }
    if(type==NotificationType::NewUserConnect)
    {
        NewUserConnectNotification user;
        user.ParseFromArray(m_dataFromServer, m_dataFromServer.size());
        qInfo()<<"new user";
        emit newUser("user");
    }
   m_dataFromServer.clear();
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
