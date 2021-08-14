#include "Server.h"
#include <qdebug.h>
#include <QFileInfo>

Server::Server()
{
	start();
}

Server::~Server()
{
}

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
void Server::UserRegestration(const User& user)
{
	arrayForResponse.resize(response.ByteSize());
	if (IfUserExists(user) == false)
	{
		m_users.emplace_back(user);
		m_userLogins.emplace_back(user.GetLogin());
		++m_userId;
		response.set_responce(ProtoServer_Response_REGISTRATION_IS_SUCCESFUL);
		response.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
		socket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
		//std::cout << "succesful" << std::endl;
	}
	else
	{
		response.set_responce(ProtoServer_Response_USER_EXISTS);
		response.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
		socket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
		//std::cout << "user exists" << std::endl;
	}
}

void Server::LoginUser(const User& user)
{
	//char* array=nullptr;
	arrayForResponse.resize(response.ByteSize());

	if (IfUserExists(user) == true)
	{
		User currentUser = SearchUser(user.GetLogin());
		/*if (currentUser.GetLogin() != user.GetLogin())
		{
			response.set_responce(ProtoServer_Response_NO_CORRECT_LOGIN);
			response.SerializeToArray(static_cast<void*>(&array[0]),array.size());
			socket->write(static_cast<QByteArray>(&array[0]),array.size());
		}*/
		if (currentUser.GetPass() != user.GetPass())
		{
			response.set_responce(ProtoServer_Response_NO_CORRECT_PASS);
			response.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
			socket->write(static_cast<QByteArray>(&arrayForResponse[0]));
		}
		else
		{
			response.set_responce(ProtoServer_Response_AUTHORIZATION_IS_SUCCESFUL);
			response.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
			socket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
		}
	}
	else
	{
		response.set_responce(ProtoServer_Response_USER_NOT_FOUND);
		response.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
		socket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
	}
}

User& Server::SearchUser(const std::string& login)
{
	for (auto currentUser = m_users.begin(); currentUser != m_users.end(); ++currentUser)
	{
		if (currentUser->GetLogin() == login)
		{
			return *currentUser;
		}
	}
}
bool Server::IfUserExists(const User& user)
{
	bool res = false;
	for (auto currentUser = m_users.begin(); currentUser != m_users.end(); ++currentUser)
	{
		if (currentUser->GetLogin() == user.GetLogin())
		{
			res = true;
		}
	}
	return res;
}

void Server::RequestHendler(const ProtoClient& dataFromClient)
{
	switch (dataFromClient.request())
	{
	case ProtoClient_Request_REGISTER_USER:
		UserRegestration(User(dataFromClient.login(), dataFromClient.pass()));
		Print();
		break;
	case ProtoClient_Request_AUTHORIZE_USER:
		LoginUser(User(dataFromClient.login(), dataFromClient.pass()));
		break;
	case ProtoClient_Request_SEND_MESSAGE:
		break;
	default:
		break;
	}
}

void Server::Print()
{
	std::cout << m_users.size() << std::endl;
}
void Server::sockReady()
{
	dataFromClient.append(socket->readAll());
	ProtoClient client;
	if (client.ParseFromArray(dataFromClient, dataFromClient.size()))
	{
		RequestHendler(client);
	}
	dataFromClient.clear();
};

void Server::incomingConnection(std::int64_t socketDescriptor)
{
	socket = new QTcpSocket(this);
	socket->setSocketDescriptor(socketDescriptor);
	m_socketDescriptor = socketDescriptor;
	connect(socket, SIGNAL(readyRead()), this, SLOT(sockReady()));
	connect(socket, SIGNAL(disconnected()), this, SLOT(sockDisc()));
	qInfo() << socketDescriptor << " Connected...";
	socket->write("Welcome to chat");
}

void Server::sockDisc()
{
	qDebug() << m_socketDescriptor << "Disconnected...";
	socket->deleteLater();
}
uint64_t Server::m_userId = 0;
