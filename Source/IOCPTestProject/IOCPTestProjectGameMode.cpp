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
	AGameSessionManager::GetInst()->Dispatch();
}
