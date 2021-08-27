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
	std::cout << "rgestration success\n";
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
}

void Client::sendLoginInNotification(const ServerLogInNotification& res)
{
	std::cout << "login In success\n";
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
}

void Client::sendNewUserConnectNotification(const NewUserConnectNotification& res)
{
	std::cout << "new connection success\n";
	std::vector<char> arrayForResponse;
	arrayForResponse.resize(res.ByteSizeLong());
	res.SerializeToArray(static_cast<void*>(&arrayForResponse[0]), arrayForResponse.size());
	m_serverSocket->write(static_cast<QByteArray>(&arrayForResponse[0]), arrayForResponse.size());
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
	const auto type = static_cast<NotificationType>(tMoc.typenotification());

	switch (type)
	{
	case NotificationType::Registration:
		registData.ParseFromArray(dataFromClient, dataFromClient.size());
		emit registrationNotificationReceived(registData);

	case NotificationType::SignIn:
	    signInData.ParseFromArray(dataFromClient, dataFromClient.size());
		emit signInNotificationReceived(signInData);

	case NotificationType::Message:
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
const QTcpSocket* Client::GetSocket()const
{
	return m_serverSocket;
}

void Client::disconnectFromClient()
{
	m_serverSocket->disconnectFromHost();
}

const std::uint64_t Client::GetSessionId()
{
	return m_sessionId;
}

void Client::SetUserInformation(const std::string& login, const std::string& pass)
{
	m_loker.lockForWrite();
	m_user.SetLogin(login);
	m_user.SetPass(pass);
	m_loker.unlock();
}

 const UserInformation& Client::GetUserInformation() const
 {
	return m_user;
 }

 Client* Client::operator->()
 {
	 return this;
 }

Client::~Client()
{
	delete m_serverSocket;
}
