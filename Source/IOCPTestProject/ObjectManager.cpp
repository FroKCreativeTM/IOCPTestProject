// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "IOCPTestProjectCharacter.h"

// 오브젝트들을 관리해주는 클래스이다.
TSharedPtr<AObjectManager> GObjectManager = nullptr;

// 이 오브젝트 매니저를 들고 있을 캐릭터는 누구인가
AObjectManager::AObjectManager(AIOCPTestProjectCharacter* player) : 
	_myPlayer(player)
{

}

AObjectManager::~AObjectManager()
{
}

void AObjectManager::Add(Protocol::ObjectInfo objectInfo, bool myPlayer)
{
	UWorld* const world =_myPlayer->GetWorld();

	// 먼저 오브젝트 타입을 가져온다.
	// Protocol::GameObjectType objectType = GetObjectTypeById(objectInfo.objectid());

	if (myPlayer)
	{
		ABLOG_S(Warning);
		_myPlayer->Rename(*FString(objectInfo.name().c_str()));
		_myPlayer->SetPlayerId(objectInfo.objectid());
		_object.Add(objectInfo.objectid(), _myPlayer);

		_myPlayer->BindObjectManager();
	}
	else
	{
		ABLOG_S(Warning);
		// 새로운 플레이어를 필드에 스폰
		// 새로 스폰한 애는 x : 550 y :950 정도에 스폰(z는 50)
		FVector SpawnLocation;
		SpawnLocation.X = 600.f;
		SpawnLocation.Y = 1000.f;
		SpawnLocation.Z = 55.f;

		FRotator SpawnRotation;
		SpawnRotation.Yaw = 0.f;
		SpawnRotation.Pitch = 0.f;
		SpawnRotation.Roll = 0.f;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = _myPlayer;
		SpawnParams.Instigator = _myPlayer->GetInstigator();
		SpawnParams.Name = FName(*FString(objectInfo.name().c_str()));

		// 하나의 캐릭터를 스폰시킨다.
		AIOCPTestProjectCharacter* SpawnCharacter
			= world->SpawnActor<AIOCPTestProjectCharacter>(_myPlayer->WhoToSpawn, SpawnLocation,
				SpawnRotation, SpawnParams);
		SpawnCharacter->SpawnDefaultController();
		SpawnCharacter->SetPlayerId(objectInfo.objectid());
		SpawnCharacter->SetPlayerHealth(100.f);

		// 플레이어 정보를 넣는다.
		_object.Add(objectInfo.objectid(), SpawnCharacter);

		UE_LOG(LogClass, Log, TEXT("other player spawned."));
	}

	//// 플레이어 타입인 경우
	//if (objectType == Protocol::GameObjectType::GAME_OBJECT_TYPE_PLAYER)
	//{
	//	
	//}
}


