#include "User.h"

User::User()
{
}

User::User(const std::string& login, const std::string& pass, const uint64_t id)
	: m_login(login), m_pass(pass), m_id(id) {}

User::User(const std::string& login, const std::string& pass)
	:  m_login(login), m_pass(pass) {}

const std::string& User::GetLogin() const
{
	return m_login;
}

const void User::SetId(const uint64_t id)
{
	m_id = id;
}

const void User::SetName(const std::string& name)
{
	m_name = name;
}

const void User::SetPass(const std::string& pass)
{
	m_pass = pass;
}

const void User::SetLogin(const std::string& login)
{
	m_login = login;
}

const std::string& User::GetPass() const
{
	return m_pass;
}
const std::string& User::GetName()
{
	return m_name;
}
const uint64_t User::GetId() const
{
	return m_id;
}

User* User::operator->()
{
	return this;
}
