#include "Server.h"
#include <qdebug.h>
#include <QHostInfo>

Server::Server(){}
Server::~Server(){}

void Server::start()
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

void Server::incomingConnection(int socketDescriptor)
{
	socket = new QTcpSocket(this);
	socket->setSocketDescriptor(socketDescriptor);
	connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
	qDebug() << socketDescriptor <<" Connected...";
	socket->write("You are connect");
	qDebug() << "Client  connected";

}

void Server::sockReady() {};

void Server::sockDisc()
{
	qDebug() << "Disconnected...";
	socket->deleteLater();
}