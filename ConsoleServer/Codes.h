#pragma once

enum class ClientRequest
{
	unknownError=-1,
	createUserAccount,
	logIntoAccount,
	logOutAccaunt,
	sendMessage
};

enum class ServerResponse
{
	unknownError = -1,
	userExists,
	userNotFound,
	noCorrectlogin,
	noCorrectPass,
	registrationIsSuccessful,
};