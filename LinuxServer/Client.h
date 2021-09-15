#pragma once
#include <QObject>
#include <QtNetwork/QTcpSocket>
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
    std::uint64_t GetSocketDescriptor()const;
	void sendRegistrationNotification(const ServerRegistrationNotification& res);
	void sendLoginInNotification(const ServerLogInNotification& res);
	void sendNewUserConnectNotification(const NewUserConnectNotification& res);
	void SetName(const std::string& name);
	void SetSessionId(const std::uint64_t sessionId);
	void SetUserId(const std::uint64_t userId);
    std::uint64_t GetSessionId()const;
	void SetSignInInformation(const UserInformation& data);
	const UserInformation& GetSignInInformation()const;
	const std::string& GetName()const;
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
    std::vector<char> arrayForResponse;
	UserInformation m_user;
	QTcpSocket* m_serverSocket=nullptr;
	std::string m_name;
	std::uint64_t m_sessionId=0;
	std::uint64_t m_userId=0;
	mutable QReadWriteLock m_loker;
};
