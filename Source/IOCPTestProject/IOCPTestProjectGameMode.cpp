// Copyright Epic Games, Inc. All Rights Reserved.

#include "IOCPTestProjectGameMode.h"
#include "IOCPTestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Network/GameSessionManager.h"
#include "Network/ServerPacketHandler.h"

AIOCPTestProjectGameMode::AIOCPTestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AIOCPTestProjectGameMode::BeginPlay()
{
	AGameSessionManager::GetInst()->StartService();

	// 플레이어 캐릭터가 생성되면서, 오브젝트 매니저에 이 플레이어를 등록한다.
	Protocol::C_LOGIN loginPacket;
	auto sendBuffer = FrokEngine::ServerPacketHandler::MakeSendBuffer(loginPacket);
	AGameSessionManager::GetInst()->GetService()->Broadcast(sendBuffer);
	AGameSessionManager::GetInst()->Dispatch();
	// AGameSessionManager::GetInst()->Dispatch();
}

void AIOCPTestProjectGameMode::EndPlay(EEndPlayReason::Type eEndPlayReasonType)
{
	AGameSessionManager::GetInst()->CloseSocket();
}
