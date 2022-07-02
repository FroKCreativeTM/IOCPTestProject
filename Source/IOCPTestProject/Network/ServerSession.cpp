// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerSession.h"

namespace FrokEngine
{
	ServerSession::~ServerSession()
	{
		cout << "~ServerSession" << endl;
	}

	void ServerSession::OnConnected() 
	{
		Protocol::C_LOGIN pkt;
		pkt.set_id("test");
		pkt.set_password("testpassword");
		auto sendBuffer = FrokEngine::ServerPacketHandler::MakeSendBuffer(pkt);
		Send(sendBuffer);
	}

	void ServerSession::OnRecvPacket(BYTE* buffer, int32 len)
	{
		FrokEngine::PacketSessionRef session = GetPacketSessionRef();
		FrokEngine::PacketHeader* header = reinterpret_cast<FrokEngine::PacketHeader*>(buffer);

		// TODO : packetId 대역 체크
		FrokEngine::ServerPacketHandler::HandlePacket(session, buffer, len);
	}

	void ServerSession::OnSend(int32 len)
	{
	}

	void ServerSession::OnDisconnected()
	{
	}
}