// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../IOCPTestProject.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <ServerCore/CorePch.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "Protobuf/Protocol.pb.h"

namespace FrokEngine
{
	using PacketHandlerFunc = std::function<bool(PacketSessionRef&, BYTE*, int32)>;
	extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

	enum : uint16
	{
		PKT_C_LOGIN = 0,
		PKT_S_LOGIN = 1,
		PKT_C_SIGNUP = 2,
		PKT_S_SIGNUP = 3,
		PKT_C_ENTER_GAME = 4,
		PKT_S_ENTER_GAME = 5,
		PKT_C_CHAT = 6,
		PKT_S_CHAT = 7,
		PKT_C_SPAWN = 8,
		PKT_S_SPAWN = 9,
		PKT_C_MOVE = 10,
		PKT_S_MOVE = 11,
	};

	// Custom Handlers
	bool Handle_INVALID(PacketSessionRef& session, BYTE* buffer, int32 len);
	bool Handle_S_LOGIN(PacketSessionRef& session, Protocol::S_LOGIN& pkt);
	bool Handle_S_SIGNUP(PacketSessionRef& session, Protocol::S_SIGNUP& pkt);
	bool Handle_S_ENTER_GAME(PacketSessionRef& session, Protocol::S_ENTER_GAME& pkt);
	bool Handle_S_CHAT(PacketSessionRef& session, Protocol::S_CHAT& pkt);
	bool Handle_S_SPAWN(PacketSessionRef& session, Protocol::S_SPAWN& pkt);
	bool Handle_S_MOVE(PacketSessionRef& session, Protocol::S_MOVE& pkt);

	class ServerPacketHandler
	{
	public:
		static void Init()
		{
			for (int32 i = 0; i < UINT16_MAX; i++)
				GPacketHandler[i] = Handle_INVALID;
			GPacketHandler[PKT_S_LOGIN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_LOGIN >(Handle_S_LOGIN, session, buffer, len); };
			GPacketHandler[PKT_S_SIGNUP] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_SIGNUP >(Handle_S_SIGNUP, session, buffer, len); };
			GPacketHandler[PKT_S_ENTER_GAME] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_ENTER_GAME >(Handle_S_ENTER_GAME, session, buffer, len); };
			GPacketHandler[PKT_S_CHAT] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_CHAT >(Handle_S_CHAT, session, buffer, len); };
			GPacketHandler[PKT_S_SPAWN] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_SPAWN >(Handle_S_SPAWN, session, buffer, len); };
			GPacketHandler[PKT_S_MOVE] = [](PacketSessionRef& session, BYTE* buffer, int32 len) { return HandlePacket < Protocol::S_MOVE >(Handle_S_MOVE, session, buffer, len); };
		}

		static bool HandlePacket(PacketSessionRef& session, BYTE* buffer, int32 len)
		{
			PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
			return GPacketHandler[header->id](session, buffer, len);
		}
		static SendBufferRef MakeSendBuffer(Protocol::C_LOGIN& pkt) { return MakeSendBuffer(pkt, PKT_C_LOGIN); }
		static SendBufferRef MakeSendBuffer(Protocol::C_SIGNUP& pkt) { return MakeSendBuffer(pkt, PKT_C_SIGNUP); }
		static SendBufferRef MakeSendBuffer(Protocol::C_ENTER_GAME& pkt) { return MakeSendBuffer(pkt, PKT_C_ENTER_GAME); }
		static SendBufferRef MakeSendBuffer(Protocol::C_CHAT& pkt) { return MakeSendBuffer(pkt, PKT_C_CHAT); }
		static SendBufferRef MakeSendBuffer(Protocol::C_SPAWN& pkt) { return MakeSendBuffer(pkt, PKT_C_SPAWN); }
		static SendBufferRef MakeSendBuffer(Protocol::C_MOVE& pkt) { return MakeSendBuffer(pkt, PKT_C_MOVE); }

	private:
		template<typename PacketType, typename ProcessFunc>
		static bool HandlePacket(ProcessFunc func, PacketSessionRef& session, BYTE* buffer, int32 len)
		{
			PacketType pkt;
			if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
				return false;

			return func(session, pkt);
		}

		template<typename T>
		static SendBufferRef MakeSendBuffer(T& pkt, uint16 pktId)
		{
			const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong());
			const uint16 packetSize = dataSize + sizeof(PacketHeader);

			SendBufferRef sendBuffer = GSendBufferManager->Open(packetSize);
			PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
			header->size = packetSize;
			header->id = pktId;
			ASSERT_CRASH(pkt.SerializeToArray(&header[1], dataSize));
			sendBuffer->Close(packetSize);

			return sendBuffer;
		}
	};
}