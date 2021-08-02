#include "TcpClient.hpp"
#include <QDebug>
TcpClient::TcpClient(QObject* parent) : QObject(parent)
{
    connectToServer();
    connect(&m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &TcpClient::onErrorOccurred);
    connect(&m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead);
}

void TcpClient::connectToServer()
{
    m_socket.connectToHost(m_ip,m_port);
}

void TcpClient::login(const QString& login, const QString& pass)
{
    qInfo()<<(m_uInform.login=login);
    qInfo()<<(m_uInform.pass=pass);

}
void TcpClient::sendMessage(const QString& message)
{
    m_socket.write(message.toUtf8());
}

void TcpClient::onConnected()
{
    qInfo() << "Connected to host.";
}

void TcpClient::onReadyRead()
{
    m_message = m_socket.readAll();
    emit newMessage(m_message);
}

void TcpClient::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qWarning() << "Error:" << error;
}
