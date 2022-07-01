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
	// ���� ��Ŷ���� ����� Ŭ������ �ʱ�ȭ�Ѵ�.
	FrokEngine::ServerPacketHandler::Init();

	// Ŭ���̾�Ʈ���� ������ ������ �����Ѵ�.
	_service = FrokEngine::MakeShared<FrokEngine::ClientService>(
		FrokEngine::NetAddress(L"127.0.0.1", 7777),
		FrokEngine::MakeShared<FrokEngine::IocpCore>(),
		FrokEngine::MakeShared<FrokEngine::ServerSession>, // TODO : SessionManager ��
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
	// service�� ����Ǿ� ���� �ʴٸ� �����͸� ���� �� ����.
	if (_service != nullptr)
	{
		_service->GetIocpCore()->Dispatch();
	}
}

