#include "ChatServer.h"
#include <Client.h>
#include <QTimer>
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
        // find the thread with the least amount of clients and use it
        threadIdx = std::distance(m_threadsLoad.cbegin(), std::min_element(m_threadsLoad.cbegin(), m_threadsLoad.cend()));
        ++m_threadsLoad[threadIdx];
    }

    newClient->moveToThread(m_availableThreads.at(threadIdx));
    connect(m_availableThreads.at(threadIdx), &QThread::finished, newClient, &QObject::deleteLater);
	connect(newClient, &Client::registrationNotificationReceived, this, std::bind(&ChatServer::registrationNotificationReceived, this, newClient, std::placeholders::_1));
	connect(newClient, &Client::signInNotificationReceived, this, std::bind(&ChatServer::signInNotificationReceived, this, newClient, std::placeholders::_1));
	connect(newClient, &Client::sendMessageNotificationReceived, this, std::bind(&ChatServer::sendMessageNotificationReceived, this, newClient, std::placeholders::_1));
    m_clients.append(newClient);
    qInfo() << socketDescriptor;
	emit logMessage(QString("new connect"));
}

void ChatServer::sendRegistrationNotification(Client* destination, ServerRegistrationNotification& message, int interval)
{
	Q_ASSERT(destination);
	QTimer::singleShot(interval, destination, std::bind(&Client::sendRegistrationNotification, destination, message));
}
 void ChatServer::sendLoginInNotification(Client* destination, ServerLogInNotification& message, int interval)
{
	Q_ASSERT(destination);
	QTimer::singleShot(interval, destination, std::bind(&Client::sendLoginInNotification, destination, message));
}

UserInformation& ChatServer::SearchUser(const std::string& login)
{
	for (auto currentUser = m_users.begin(); currentUser != m_users.end(); ++currentUser)
	{
		if (currentUser->GetLogin() == login)
		{
			return *currentUser;
		}
	}
}

void  ChatServer::Regestration(Client* send, const UserInformation& user)
{
	std::cout << "Registration(method)\n";

	ServerRegistrationNotification response;
	response.set_typenotification(static_cast<google::protobuf::uint32>(NotificationType::Registration));
	
	if (IfUserExists(user) == false)
	{
		m_users.emplace_back(user);
		response.set_response(ServerRegistrationNotification_Response_REGISTRATION_IS_SUCCESFUL);
		sendRegistrationNotification(send, response, 0);
	}
	else
	{
		response.set_response(ServerRegistrationNotification_Response_USER_EXISTS);
		sendRegistrationNotification(send, response,0);
	}
	
}
bool ChatServer::IfUserExists(const UserInformation& user)
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

void ChatServer::registrationNotificationReceived(Client* sender, const ClientRegistrationNotification& data)
{
	std::cout << "Registration\n";
	//NotificationType ntType=RegistrationNotification;
	Regestration(sender, UserInformation(data.login(), data.pass()));
}

void ChatServer::signInNotificationReceived(Client* sender, const ClientSignInNotification& data)
{
	std::cout << "Sign in\n";
	ServerLogInNotification notif;
	notif.set_typenotification(static_cast<google::protobuf::uint32>(NotificationType::SignIn));
	notif.set_respose(ServerLogInNotification_Response_AUTHORIZATION_IS_SUCCESFUL);
	sendLoginInNotification(sender, notif,0);
}
void ChatServer::sendMessageNotificationReceived(Client* sender, const ClientSendMessageNotification& data)
{

}
ChatServer::~ChatServer()
{
	for (QThread* singleThread : m_availableThreads) {
		singleThread->quit();
		singleThread->wait();
	}
}






//void ChatServer::sendResponse(Client* destination, ServerDataSerialize& message, int interval)
//{
//	Q_ASSERT(destination);
//	QTimer::singleShot(interval, destination, std::bind(&Client::sendResponse,destination,message));
//}

//void ChatServer::protoFileRecieved(Client* sender, const ClientDataSerialize& clientFile)
//{
//	std::cout << sender->GetSocketDescriptor()<<std::endl;
//    
//	if (clientFile.request() == ClientDataSerialize_Request_REGISTER_USER)
//	{
//		ClientDataSerialize::Registration regist;
//		std::cout << "Registration\n";
//		if (Regestration(sender, UserInformation(regist.login(), regist.pass())))
//		{
//			NewUserConnectionNotification();
//		}
//	}
//
//	if (clientFile.request() == ClientDataSerialize_Request_SEND_MESSAGE)
//	{
//		std::cout << "Message\n";
//		ClientDataSerialize::MessageInformation massage;
//		ServerDataSerialize response;
//		response.set_response(ServerDataSerialize_Response_NewMessage);
//		sendResponse(sender, response,0);
//	}
//}



//void ChatServer::protoFileRecieved(Client* sender, const ClientDataSerialize& clientFile)
//{
//	std::cout << sender->GetSocketDescriptor()<<std::endl;
//    
//	if (clientFile.request() == ClientDataSerialize_Request_REGISTER_USER)
//	{
//		ClientDataSerialize::Registration regist;
//		std::cout << "Registration\n";
//		if (Regestration(sender, UserInformation(regist.login(), regist.pass())))
//		{
//			NewUserConnectionNotification();
//		}
//	}
//
//	if (clientFile.request() == ClientDataSerialize_Request_SEND_MESSAGE)
//	{
//		std::cout << "Message\n";
//		ClientDataSerialize::MessageInformation massage;
//		ServerDataSerialize response;
//		response.set_response(ServerDataSerialize_Response_NewMessage);
//		sendResponse(sender, response,0);
//	}
//}