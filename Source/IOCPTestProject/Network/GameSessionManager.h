// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../IOCPTestProject.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/prewindowsapi.h"

#include <ServerCore/CorePch.h>

#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

#include "ServerPacketHandler.h"
#include "ServerSession.h"
#include <ServerCore/Service.h>
#include <ServerCore/Types.h>

class IOCPTESTPROJECT_API AGameSessionManager
{
public:	
	// Sets default values for this actor's properties
	AGameSessionManager();
	~AGameSessionManager();

	static TSharedPtr<AGameSessionManager> GetInst()
	{
		if (_inst == nullptr)
		{
			_inst = MakeShared<AGameSessionManager>();
		}
		return _inst;
	}

	void DestroyInst()
	{
		if (_inst != nullptr)
		{
			CloseSocket();
		}
		_inst = nullptr;
	}

	FrokEngine::ClientServiceRef GetService() { return _service; }

public:	
	bool StartService();
	void CloseSocket();
	void Dispatch();

	

private : 
	static TSharedPtr<AGameSessionManager>			_inst;
	FrokEngine::ClientServiceRef				_service;
};
