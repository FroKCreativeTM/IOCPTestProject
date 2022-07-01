// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSessionManager.h"

TSharedPtr<AGameSessionManager>	AGameSessionManager::_inst = nullptr;

// Sets default values
AGameSessionManager::AGameSessionManager()
{
}

AGameSessionManager::~AGameSessionManager()
{
	CloseSocket();
}

bool AGameSessionManager::StartService()
{
	// 서버 패킷들을 담당할 클래스를 초기화한다.
	FrokEngine::ServerPacketHandler::Init();

	// 클라이언트에서 서버로 연결을 진행한다.
	_service = FrokEngine::MakeShared<FrokEngine::ClientService>(
		FrokEngine::NetAddress(L"127.0.0.1", 7777),
		FrokEngine::MakeShared<FrokEngine::IocpCore>(),
		FrokEngine::MakeShared<FrokEngine::ServerSession>, // TODO : SessionManager 등
		1);

	return _service->Start();
}

void AGameSessionManager::CloseSocket()
{
	if (_service != nullptr)
	{
		_service.reset();
		_service = nullptr;
	}
}

void AGameSessionManager::Dispatch()
{
	// service가 연결되어 있지 않다면 데이터를 보낼 수 없다.
	if (_service != nullptr)
	{
		_service->GetIocpCore()->Dispatch();
	}
}

