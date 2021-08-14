#pragma once
#include <string>

class User 
{
public:
	User();
	explicit User(const std::string& login, const std::string& pass, const std::uint64_t id);
	explicit User( const std::string& login, const std::string& pass);
	const void SetLogin(const std::string& login);
	const void SetPass(const std::string& pass);
	const void SetName(const std::string& name);
	const void SetId(const std::uint64_t id);
	const std::string& GetLogin()const;
	const std::string& GetPass()const;
	const std::string& GetName();
	const std::uint64_t GetId()const;
	User* operator->();
private:
	std::string m_login;
	std::string m_pass;
	std::string m_name;
	std::uint32_t m_id = 0;
};

//bool operator==(const User& currentLogin, const User& second)
//{
//	return currentLogin.GetLogin() == second.GetLogin();
//}
//
//bool operator==(const std::string& login, const User& user)
//{
//	return login == user.GetLogin();
//}