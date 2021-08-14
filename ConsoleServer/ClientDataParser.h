#pragma once
#include "Client.pb.h"

class ClientDataParser
{
public:
	ClientDataParser(const ProtoClient&data)
	  : m_client(data)
	{
	}
private:
	enum ClientRequest
	{
		UNKNOWN_ERROR   = ProtoClient::Request::ProtoClient_Request_UNKNOWN_ERROR,
		REGISTER_USER   = ProtoClient::Request::ProtoClient_Request_REGISTER_USER,
		AUTHORIZE_USER  = ProtoClient::Request::ProtoClient_Request_AUTHORIZE_USER,
		LOG_OUT_ACCOUNT = ProtoClient::Request::ProtoClient_Request_LOG_OUT_ACCOUNT,
		SEND_MESSAGE    = ProtoClient::Request::ProtoClient_Request_SEND_MESSAGE 
	};
	ProtoClient m_client;
	ClientRequest request;
};

