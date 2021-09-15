#include "Server.h"
#include <qdebug.h>
#include <memory>

Server::Server()
	: m_chatServer(new ChatServer(this))
{
	startServer();
	connect(m_chatServer, &ChatServer::logMessage, this, &Server::logMessage);
}

Server::~Server()
{

}

void Server::logMessage(const QString& mess)
{
	qInfo()<<mess;
}

void Server::incomingConnection (qintptr  socketDescriptor)
{
	m_chatServer->incomingConnection(socketDescriptor);
}

void Server::startServer()
{
	if (this->listen(QHostAddress::Any, 45000))
	{
		qDebug() << "Listening...";
	}
	else
	{
		qDebug() << "No listening...";
	}
}

