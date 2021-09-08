#include "Client.h"
#include "NotificationType.hpp"
#include "NotificationTupeMoc.pb.h"


Client::Client(QObject *parent)
	: QObject(parent)
	, m_serverSocket(new QTcpSocket(this))
{
	connect(m_serverSocket,  &QTcpSocket::readyRead,     this,  &Client::receiveNotification);
	connect(m_serverSocket,  &QTcpSocket::disconnected,  this,  &Client::disconnectFromClient);
}

void Client::sendRegistrationNotification(const ServerRegistrationNotification& res)
{
	std::cout << "sended regestration notification \n";
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
}

void Client::sendLoginInNotification(const ServerLogInNotification& res)
{
	std::cout << " sended sign in notification\n";
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
}

void Client::sendNewUserConnectNotification(const NewUserConnectNotification& res)
{
	std::cout << "new connection success\n";
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
}

 void Client::SetName(const std::string& name)
{
	m_loker.lockForWrite();
	m_name = name;
	m_loker.unlock();
}

 void Client::SetSessionId(const std::uint64_t sessionId)
 {
	m_loker.lockForWrite();
	m_sessionId = sessionId;
	m_loker.unlock();
 }

 void Client::SetUserId(const std::uint64_t userId)
 {
	 m_loker.lockForWrite();
	 m_userId = userId;
	 m_loker.unlock();
 }

void Client::receiveNotification()
{
	qInfo()<<dataFromClient.append(m_serverSocket->readAll());
	NotificationTupeMoc tMoc;
	tMoc.ParseFromArray(dataFromClient, dataFromClient.size());
	const auto resType = static_cast<NotificationType>(tMoc.typenotification());

	if (resType == NotificationType::Registration)
	{
		ClientRegistrationNotification registData;
		registData.ParseFromArray(dataFromClient, dataFromClient.size());
		emit registrationNotificationReceived(registData);
	}
	if (resType == NotificationType::SignIn)
	{
		ClientSignInNotification signInData;
		signInData.ParseFromArray(dataFromClient, dataFromClient.size());
		emit signInNotificationReceived(signInData);
	}
	if (resType == NotificationType::Message)
	{
		ClientSendMessageNotification messData;
		messData.ParseFromArray(dataFromClient, dataFromClient.size());
		emit sendMessageNotificationReceived(messData);
	}
	dataFromClient.clear();
}

bool Client::setSocketDescriptor(std::uint64_t socketDescriptor)
{
	return m_serverSocket->setSocketDescriptor(socketDescriptor);
}

const std::uint64_t Client::GetSocketDescriptor() const
{
	return m_serverSocket->socketDescriptor();
}

void Client::disconnectFromClient()
{
	std::cout << "disconnectFromClient\n";
	m_serverSocket->disconnectFromHost();
}

const std::uint64_t Client::GetSessionId()
{
	return m_sessionId;
}

void Client::SetSignInInformation(const UserInformation& data)
{
	m_loker.lockForWrite();

	m_user.SetLogin(data.GetLogin());
	m_user.SetPass(data.GetPass());

	m_loker.unlock();
}

const UserInformation& Client::GetSignInInformation() const
 {
	return m_user;
 }

const std::string& Client::GetName() const
{
	return m_name;
}

 Client* Client::operator->()
 {
	 return this;
 }

Client::~Client()
{
	std::cout << "~Client\n";
	delete m_serverSocket;
}
