#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <QObject>
#include <QTcpSocket>
#include <QString>

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

signals:
    void newMessage(const QByteArray& ba);

public slots:
    void connectToServer();
    void sendMessage(const QString& message);
    void login(const QString& login, const QString& pass);
private slots:
    void onConnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);
private:
    QTcpSocket m_socket;
    QByteArray m_message;
    QString m_ip="127.0.0.1";
    int m_port = 45000;
    UserInformation m_uInform;
};

#endif // TCPCLIENT_HPP
