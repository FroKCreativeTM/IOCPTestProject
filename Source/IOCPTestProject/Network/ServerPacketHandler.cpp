// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerPacketHandler.h"

namespace FrokEngine
{
	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// ���� ������ �۾���

	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		// TODO : Log
		return false;
	}

	bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt)
	{
		if (pkt.players().size() == 0)
		{
			// ĳ���� ����â
		}

		if (pkt.success())
		{
		}
		else
		{
		}

		// ���� UI ��ư ������ ���� ����
		// Protocol::C_ENTER_GAME enterGamePkt;
		// enterGamePkt.set_playerindex(0); // ù��° ĳ���ͷ� ����
		// auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
		// session->Send(sendBuffer);

		return true;
	}

	// ȸ������ ��û �� ���� ���θ� �޾Ƴ���..
	bool Handle_S_SIGNUP(PacketSessionRef& session, Protocol::S_SIGNUP& pkt)
	{
		// ���� ��
		if (pkt.success() == 1) 
		{
		}
		else {
		}

		return true;
	}

	bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt)
	{
		// TODO
		return true;
	}

	bool Handle_S_CURRENT_PLAYER_INFO(PacketSessionRef& session, Protocol::S_CURRENT_PLAYER_INFO& pkt)
	{
		return true;
	}

	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
	{
		return true;
	}
}