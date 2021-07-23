
#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();
	~Server();
public slots:
	void start();
	void incomingConnection(int socketDescriptor);
	void sockReady();
	void sockDisc();
private:
	QTcpSocket* socket = nullptr;
	QByteArray data;
};
#endif