// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerPacketHandler.h"

#include "../IOCPTestProject.h"
#include "../IOCPTestProjectCharacter.h"

#include "../ObjectManager.h"

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
		// TODO : 이미 들어온 사람들에 대한 리스트를 받아온다.
		GObjectManager->AddPlayer(pkt.player(), true);

		return true;
	}

	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
	{
		// (서버 상에서 특정 long long type으로 등록된) 어떤 아이디를 가진 유저가
		// 채팅한 것을 가져와서 이를 채팅창에 반영한다.

		// 플레이어 매니저에서 pkt에 보내진 id를 가진 액터를 찾는다.
		FrokEngine::uint64 player_id = pkt.playerid();

		// 그 id를 가진 액터의 이름과 채팅을 같이 채팅창에 표시한다.
		string chat = pkt.msg();

		return true;
	}

	bool Handle_S_SPAWN(PacketSessionRef& session, Protocol::S_SPAWN& pkt)
	{
		return false;
	}

	bool Handle_S_MOVE(PacketSessionRef& session, Protocol::S_MOVE& pkt)
	{
		// 어떤 아이디를 가진 유저가 어디로 움직이는지를 받아오는 것이다.
		// 즉 어떤 클라이언트가 움직이면서 broadcast하는 그 객체를 정보에 맞게 보내는 식이다.

		// 플레이어 매니저에서 pkt에 보내진 id를 가진 액터를 찾는다.
		FrokEngine::uint64 player_id = pkt.playerid();

		// 이 액터의 position, rotation, velocity를 세팅한다.
		Protocol::PosInfo posInfo = pkt.posinfo();

		

		return true;
	}
}