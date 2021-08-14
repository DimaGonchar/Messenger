#include "TcpClient.hpp"
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
        m_client.set_login(login);
        m_client.set_pass(pass);
        m_client.set_request(ProtoClient_Request_AUTHORIZE_USER);
        m_requestForServer.resize(m_client.ByteSizeLong());
        m_client.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
        m_socket->write(static_cast<QByteArray>(&m_requestForServer[0]),m_requestForServer.size());
}
void TcpClient::registration(const QString& login, const QString& pass)
{
    if(login.isEmpty())
    {
        emit newMessage("empty login!");
    }
    if(pass.isEmpty())
    {
        emit newMessage("empty password!");
    }
    else if(!login.isEmpty()&&!pass.isEmpty())
    {
      RegistrationUser(login.toStdString(),pass.toStdString());
    }
}
void TcpClient::RegistrationUser(const std::string& login, const std::string& pass)
{
    m_client.set_login(login);
    m_client.set_pass(pass);
    m_client.set_request(ProtoClient_Request_REGISTER_USER);
     m_requestForServer.resize(m_client.ByteSizeLong());
    m_client.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
    m_socket->write(static_cast<QByteArray>(&m_requestForServer[0]),m_requestForServer.size());
}
void TcpClient::sendMessage(const QString& message)
{
    m_client.set_usermessage(message.toStdString());
    m_client.set_request(ProtoClient_Request_SEND_MESSAGE);
    m_client.SerializeToArray(static_cast<void*>(&m_requestForServer[0]), m_requestForServer.size());
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
    ProtoServer server;
    if(server.ParseFromArray(m_dataFromServer, m_dataFromServer.size()))
    {
        if(server.responce()==ProtoServer_Response_USER_EXISTS)
        {
            emit newMessage("user exists!");
        }
        if(server.responce()==ProtoServer::Response::ProtoServer_Response_REGISTRATION_IS_SUCCESFUL)
        {
           qInfo()<<"succesful";
           emit newMessage("registered!");
        }
        if(server.responce()==ProtoServer_Response_AUTHORIZATION_IS_SUCCESFUL)
        {
            qInfo()<<"succesful";
            emit logIn();
        }
        if(server.responce()==ProtoServer_Response_NO_CORRECT_LOGIN)
        {
            qInfo()<<"no correct login";
            emit newMessage("no correct login");
         }
        if(server.responce()==ProtoServer_Response_NO_CORRECT_PASS)
        {
            qInfo()<<"no correct password";
            emit newMessage("no correct password");
        }

        if(server.responce()==ProtoServer_Response_USER_NOT_FOUND)
        {
            qInfo()<<"user not founded";
            emit newMessage("user not founded");
        }
    }
   m_dataFromServer.clear();
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
