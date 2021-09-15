#include "UserInformation.h"

UserInformation::UserInformation()
{
}

UserInformation::UserInformation(const std::uint64_t id,const std::string& login, const std::string& pass, const std::string& name)
    : m_login(login), m_pass(pass), m_name(name),m_id(id){}

UserInformation::UserInformation(const std::string& login, const std::string& pass, const std::string& name)
	: m_login(login), m_pass(pass), m_name(name) {}

UserInformation::UserInformation(const std::string& login, const std::string& pass)
	:  m_login(login), m_pass(pass) {}

const std::string& UserInformation::GetLogin() const
{
	return m_login;
}

void UserInformation::SetId(const uint64_t id)
{
	m_id = id;
}

void UserInformation::SetName(const std::string& name)
{
	m_name = name;
}

void UserInformation::SetPass(const std::string& pass)
{
	m_pass = pass;
}

 void UserInformation::SetLogin(const std::string& login)
{
	m_login = login;
}

const std::string& UserInformation::GetPass() const
{
	return m_pass;
}
const std::string& UserInformation::GetName()const
{
	return m_name;
}
 uint64_t UserInformation::GetId() const
{
	return m_id;
}

UserInformation* UserInformation::operator->()
{
	return this;
}
