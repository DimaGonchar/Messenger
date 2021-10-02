
#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "ChatServer.h"

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();
	~Server();
public slots:
    void incomingConnection(qintptr socketDescriptor);
	void logMessage(const QString& mess);
private:void startServer();
private:
	ChatServer* m_chatServer;
};
#endif
