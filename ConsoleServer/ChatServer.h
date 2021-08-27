#pragma once
#include <QTcpServer>
#include <QTcpSocket>
#include <QThread>
#include <QVector>
#include "UserInformation.h"
#include "Server.pb.h"
#include "Client.pb.h"

Q_DECLARE_METATYPE(ClientRegistrationNotification)
Q_DECLARE_METATYPE(ClientSignInNotification)
Q_DECLARE_METATYPE(ClientSendMessageNotification)
Q_DECLARE_METATYPE(UserInformation)


class Client;

class ChatServer : public QTcpServer
{
	Q_OBJECT
	Q_DISABLE_COPY(ChatServer)
signals:
	void logMessage(const QString& mess);
public:
	void incomingConnection(std::int64_t  socketDescriptor) override;
	void sendRegistrationNotification(Client* destination, ServerRegistrationNotification& message, int interval);
	void sendLoginInNotification(Client* destination, ServerLogInNotification& message, int interval);
	void Regestration(Client* send, const UserInformation& user);
	bool IfUserExists(const UserInformation& user);
	UserInformation& SearchUser(const std::string& login);
private slots:
	void registrationNotificationReceived(Client* sender, const ClientRegistrationNotification& data);
	void signInNotificationReceived(Client* sender, const ClientSignInNotification& data);
	void sendMessageNotificationReceived(Client* sender, const ClientSendMessageNotification& data);
public:
	explicit ChatServer(QObject *parent);
	~ChatServer();
private:
	QByteArray m_fromClient;
	const std::int64_t m_idealThreadCount;
	QVector<QThread*> m_availableThreads;
	QVector<std::int64_t> m_threadsLoad;
	QVector<Client*> m_clients;
	std::vector<UserInformation> m_users;
};
