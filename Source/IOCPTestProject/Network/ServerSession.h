// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <ServerCore/CorePch.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include <ServerCore/ThreadManager.h>
#include <ServerCore/Service.h>
#include <ServerCore/BufferReader.h>
#include "ServerPacketHandler.h"

/**
 * 
 */

namespace FrokEngine
{
	class PacketSession;

	class IOCPTESTPROJECT_API ServerSession : public PacketSession
	{
	public:
		~ServerSession();

		virtual void OnConnected() override;
		virtual void OnRecvPacket(BYTE* buffer, int32 len) override;
		virtual void OnSend(int32 len) override;
		virtual void OnDisconnected() override;
	};
}
