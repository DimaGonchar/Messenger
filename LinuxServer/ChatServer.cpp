#include "ChatServer.h"
#include "Client.h"
#include <QTimer>
#include <algorithm>
#include "NotificationType.hpp"

ChatServer::ChatServer(QObject *parent)
	: QTcpServer(parent)
	,m_idealThreadCount(qMax(QThread::idealThreadCount(), 1))
{
	m_availableThreads.reserve(m_idealThreadCount);
	m_threadsLoad.reserve(m_idealThreadCount);
    qRegisterMetaType<ClientRegistrationNotification>("ClientRegistrationNotification");
    qRegisterMetaType<ClientSignInNotification>("ClientSignInNotification");
	qRegisterMetaType<ClientSendMessageNotification>("ClientSendMessageNotification");
	qRegisterMetaType<UserInformation>("UserInformation");
    m_database=new Database("/home/dima/Documents/Messenger/usersDatabase.sqlite3");
}

void ChatServer::incomingConnection(std::int64_t  socketDescriptor)
{
    Client* newClient = new Client;
    if (!newClient->setSocketDescriptor(socketDescriptor))
    {
        newClient->deleteLater();
        return;
    }
    int threadIdx = m_availableThreads.size();
    if (threadIdx < m_idealThreadCount)
    { //we can add a new thread
        m_availableThreads.append(new QThread(this));
        m_threadsLoad.append(1);
        m_availableThreads.last()->start();
    }
    else
    {
        //find the thread with the least amount of clients and use it
        threadIdx = std::distance(m_threadsLoad.cbegin(), std::min_element(m_threadsLoad.cbegin(), m_threadsLoad.cend()));
        ++m_threadsLoad[threadIdx];
    }

    newClient->moveToThread(m_availableThreads.at(threadIdx));
    connect(m_availableThreads.at(threadIdx), &QThread::finished, newClient, &QObject::deleteLater);
    connect(newClient, &Client::registrationNotificationReceived, this, std::bind(&ChatServer::registrationNotificationReceived, this, newClient, std::placeholders::_1));
    connect(newClient, &Client::signInNotificationReceived, this, std::bind(&ChatServer::signInNotificationReceived, this, newClient, std::placeholders::_1));
    //connect(newClient, &Client::sendMessageNotificationReceived, this, std::bind(&ChatServer::sendMessageNotificationReceived, this, newClient, std::placeholders::_1));
    m_clients.append(newClient);
    qInfo() << socketDescriptor;
	emit logMessage(QString("new connect"));
}

void ChatServer::RegistrationNotification(Client* destination, ServerRegistrationNotification& message, int interval)
{
	Q_ASSERT(destination);
	QTimer::singleShot(interval, destination, std::bind(&Client::sendRegistrationNotification, destination, message));
}
 void ChatServer::LoginInNotification(Client* destination, ServerLogInNotification& message, int interval)
 {
	Q_ASSERT(destination);
	QTimer::singleShot(interval, destination, std::bind(&Client::sendLoginInNotification, destination, message));
 }

 void ChatServer::broadcastUserConnectionNotification(const NewUserConnectNotification& notification, Client* exclude)
 {
	 for (Client* receiver : m_clients)
	 {
		 Q_ASSERT(receiver);
		 if (receiver!= exclude)
		 {
			 QTimer::singleShot(0, receiver, std::bind(&Client::sendNewUserConnectNotification, receiver, notification));
		 }
		 continue;
	 }
 }

bool ChatServer::Regestration(Client* client, const UserInformation& userInfo)
{
	std::cout << "Registration(method)\n";

	ServerRegistrationNotification response;
	response.set_typenotification(NotificationType::Registration);
//	if(m_database->SaveUserToDatabase(userInfo))
//    {
//        response.set_response(ServerRegistrationNotification_Response_REGISTRATION_IS_SUCCESFUL);
//		std::cout << "REGISTRATION_IS_SUCCESFUL\n";
//		RegistrationNotification(client, response, 0);
//    }
	if (IfUserExists(userInfo)==false)
	{
		m_registeredUsers.emplace_back(userInfo);
		response.set_response(ServerRegistrationNotification_Response_REGISTRATION_IS_SUCCESFUL);
		std::cout << "REGISTRATION_IS_SUCCESFUL\n";
		RegistrationNotification(client, response, 0);
		return true;
	}
	else
	{
		response.set_response(ServerRegistrationNotification_Response_USER_EXISTS);
		std::cout << "USER_EXISTS\n";
		RegistrationNotification(client, response, 0);
		return false;
	}
	
}

void ChatServer::SignIn(Client* client,const UserInformation& userInfo)
 {
	 ServerLogInNotification res;
	 res.set_typenotification(NotificationType::SignIn);
	 if (IfUserExists(userInfo)==true)
	 {
		 if (GetUser(userInfo).GetPass() == userInfo.GetPass())
		 {
			 res.set_respose(ServerLogInNotification_Response_AUTHORIZATION_IS_SUCCESFUL);
			 std::cout << "AUTHORIZATION_IS_SUCCESFUL\n";
			 LoginInNotification(client, res, 0);
		 }
		 else
		 {
			 std::cout << "AUTHORIZATION_FAILD\n";
			 res.set_respose(ServerLogInNotification_Response_AUTHORIZATION_FAILD);
			 LoginInNotification(client, res, 0);
		 }
	 }
	 else
	 {
		 std::cout << "USER_NOT_FOUND\n";
		 res.set_respose(ServerLogInNotification_Response_USER_NOT_FOUND);
		 LoginInNotification(client, res, 0);
	 }
 }

bool ChatServer::IfUserExists(const UserInformation& userInfo)
{

	for (auto currentUser = m_registeredUsers.begin(); currentUser != m_registeredUsers.end(); ++currentUser)
	{
		if (currentUser->GetLogin() == userInfo.GetLogin())
		{
			return true;
		}
	}
	return false;
}

 UserInformation& ChatServer::GetUser( const UserInformation& user)
{
	 for (auto it = m_registeredUsers.begin(); it != m_registeredUsers.end(); ++it)
	 {
		 if (it->GetLogin() == user.GetLogin())
		 {
			 return *it;
		 }
	 }
}

void ChatServer::registrationNotificationReceived(Client* sender, const ClientRegistrationNotification& data)
{
	std::cout << "Registration\n";
	if (Regestration(sender, UserInformation(data.login(), data.pass())))
	{
		NewUserConnectNotification newConnection;
		newConnection.set_typenotification(NotificationType::NewUserConnect);
		newConnection.set_username(data.username());
		broadcastUserConnectionNotification(newConnection, sender);
	}
}

void ChatServer::signInNotificationReceived(Client* sender, const ClientSignInNotification& data)
{
	std::cout << "Sign in\n";
	SignIn(sender, UserInformation(data.login(), data.pass()));
}
//void ChatServer::sendMessageNotificationReceived(Client* sender, const ClientSendMessageNotification& data)
//{

//}
ChatServer::~ChatServer()
{
	std::cout << "~ChatServer\n";
    delete m_database;
	for (QThread* singleThread : m_availableThreads) {
		singleThread->quit();
		singleThread->wait();
	}
}
