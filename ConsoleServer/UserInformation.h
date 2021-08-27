#pragma once
#include <string>

class UserInformation 
{
public:
	UserInformation();
	explicit UserInformation(const std::string& login, const std::string& pass, const std::uint64_t id);
	explicit UserInformation( const std::string& login, const std::string& pass);
	const void SetLogin(const std::string& login);
	const void SetPass(const std::string& pass);
	const void SetName(const std::string& name);
	const void SetId(const std::uint64_t id);
	const std::string& GetLogin()const;
	const std::string& GetPass()const;
	const std::string& GetName();
	const std::uint64_t GetId()const;
	UserInformation* operator->();
private:
	std::string m_login;
	std::string m_pass;
	std::string m_name;
	std::uint32_t m_id = 0;
};

