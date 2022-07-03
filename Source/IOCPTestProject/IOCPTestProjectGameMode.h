// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "IOCPTestProject.h"
#include "GameFramework/GameModeBase.h"
#include "IOCPTestProjectGameMode.generated.h"

UCLASS(minimalapi)
class AIOCPTestProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AIOCPTestProjectGameMode();

	virtual void BeginPlay() override;
};



