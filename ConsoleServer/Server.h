
#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <vector>
#include "Client.pb.h"
#include "Server.pb.h"
#include "User.h"

class Server : public QTcpServer
{
	Q_OBJECT
public:
	Server();
	~Server();
public slots:
	void start();
	void incomingConnection(std::int64_t socketDescriptor);
	void sockReady();
	void sockDisc();
private:
	void UserRegestration(const User& user);
	void LoginUser(const User& userData);
	//bool PasswordVerification();
	//bool LoginVerification();
	bool IfUserExists(const User& user);
	void Print();
	User& SearchUser(const std::string& login);
	void RequestHendler(const ProtoClient& dataFromClient);
private:
	QTcpSocket* socket = nullptr;
	QByteArray dataFromClient;
	std::int64_t m_socketDescriptor;
	std::vector<User> m_users;
	std::vector<std::string> m_userLogins;
	ProtoServer response;
	std::vector<char> arrayForResponse;
	static std::uint64_t m_userId;

};
#endif