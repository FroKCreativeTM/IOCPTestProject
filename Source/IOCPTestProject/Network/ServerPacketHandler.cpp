// Fill out your copyright notice in the Description page of Project Settings.

#include "ServerPacketHandler.h"

#include "../IOCPTestProject.h"
#include "../IOCPTestProjectCharacter.h"

#include "../ObjectManager.h"

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
		// TODO : �̹� ���� ����鿡 ���� ����Ʈ�� �޾ƿ´�.
		GObjectManager->AddPlayer(pkt.player(), true);

		return true;
	}

	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt)
	{
		// (���� �󿡼� Ư�� long long type���� ��ϵ�) � ���̵� ���� ������
		// ä���� ���� �����ͼ� �̸� ä��â�� �ݿ��Ѵ�.

		// �÷��̾� �Ŵ������� pkt�� ������ id�� ���� ���͸� ã�´�.
		FrokEngine::uint64 player_id = pkt.playerid();

		// �� id�� ���� ������ �̸��� ä���� ���� ä��â�� ǥ���Ѵ�.
		string chat = pkt.msg();

		return true;
	}

	bool Handle_S_SPAWN(PacketSessionRef& session, Protocol::S_SPAWN& pkt)
	{
		return false;
	}

	bool Handle_S_MOVE(PacketSessionRef& session, Protocol::S_MOVE& pkt)
	{
		// � ���̵� ���� ������ ���� �����̴����� �޾ƿ��� ���̴�.
		// �� � Ŭ���̾�Ʈ�� �����̸鼭 broadcast�ϴ� �� ��ü�� ������ �°� ������ ���̴�.

		// �÷��̾� �Ŵ������� pkt�� ������ id�� ���� ���͸� ã�´�.
		FrokEngine::uint64 player_id = pkt.playerid();

		// �� ������ position, rotation, velocity�� �����Ѵ�.
		Protocol::PosInfo posInfo = pkt.posinfo();

		

		return true;
	}
}