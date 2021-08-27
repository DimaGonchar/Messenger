#pragma once

#include <QObject>
#include <QTcpSocket>
#include "Client.pb.h"
#include "Server.pb.h"
#include "UserInformation.h"
#include <vector>
#include <string>
#include <QReadWriteLock>

class Client : public QObject
{
	Q_OBJECT
public:
	explicit Client(QObject *parent=nullptr);
    bool setSocketDescriptor(std::uint64_t socketDescriptor);
	const std::uint64_t GetSocketDescriptor()const;
	virtual const QTcpSocket* GetSocket()const;
	void sendRegistrationNotification(const ServerRegistrationNotification& res);
	void sendLoginInNotification(const ServerLogInNotification& res);
	void sendNewUserConnectNotification(const NewUserConnectNotification& res);
	void SetSessionId(const std::uint64_t sessionId);
	void SetUserId(const std::uint64_t userId);
	const std::uint64_t GetSessionId();
	void SetUserInformation(const std::string& login, const std::string& pass);
	const UserInformation& GetUserInformation()const;
	Client* operator->();
	~Client();
signals:
	void registrationNotificationReceived(const ClientRegistrationNotification& data);
	void signInNotificationReceived(const ClientSignInNotification& data);
	void sendMessageNotificationReceived(const ClientSendMessageNotification& data);
public slots:
	void disconnectFromClient();
private slots:
	void receiveNotification();
private:
	QByteArray dataFromClient;
	UserInformation m_user;
	QTcpSocket* m_serverSocket;
	std::uint64_t m_sessionId;
	std::uint64_t m_userId;
	ClientRegistrationNotification registData;
	ClientSignInNotification signInData;
	ClientSendMessageNotification messData;
	std::vector<char> arrayForResponse;
	mutable QReadWriteLock m_loker;
};
