// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerPacketHandler.h"

namespace FrokEngine
{
	PacketHandlerFunc GPacketHandler[UINT16_MAX];

	// 직접 컨텐츠 작업자

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
			// 캐릭터 생성창
		}

		if (pkt.success())
		{
		}
		else
		{
		}

		// 입장 UI 버튼 눌러서 게임 입장
		// Protocol::C_ENTER_GAME enterGamePkt;
		// enterGamePkt.set_playerindex(0); // 첫번째 캐릭터로 입장
		// auto sendBuffer = ServerPacketHandler::MakeSendBuffer(enterGamePkt);
		// session->Send(sendBuffer);

		return true;
	}

	// 회원가입 요청 시 성공 여부를 받아낸다..
	bool Handle_S_SIGNUP(PacketSessionRef& session, Protocol::S_SIGNUP& pkt)
	{
		// 성공 시
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