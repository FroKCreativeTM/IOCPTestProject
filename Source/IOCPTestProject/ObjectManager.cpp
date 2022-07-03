// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectManager.h"
#include "IOCPTestProjectCharacter.h"

// ������Ʈ���� �������ִ� Ŭ�����̴�.
TSharedPtr<AObjectManager> GObjectManager = nullptr;

// �� ������Ʈ �Ŵ����� ��� ���� ĳ���ʹ� �����ΰ�
AObjectManager::AObjectManager(AIOCPTestProjectCharacter* player) : 
	_myPlayer(player)
{

}

AObjectManager::~AObjectManager()
{
}

void AObjectManager::AddPlayer(Protocol::ObjectInfo objectInfo, bool myPlayer)
{
	UWorld* const world =_myPlayer->GetWorld();

	// ���� ������Ʈ Ÿ���� �����´�.
	Protocol::GameObjectType objectType = GetObjectTypeById(objectInfo.objectid());
	// �÷��̾� Ÿ���� ���
	if (objectType == Protocol::GameObjectType::GAME_OBJECT_TYPE_PLAYER)
	{
		if (myPlayer)
		{
			_myPlayer->Rename(TEXT("%s", objectInfo.name().c_str()));
			_myPlayer->SetPlayerId(objectInfo.objectid());
			_object.Add(objectInfo.objectid(), _myPlayer);
		}
		else
		{
			// ���ο� �÷��̾ �ʵ忡 ����
			// ���� ������ �ִ� x : 550 y :950 ������ ����(z�� 50)
			FVector SpawnLocation;
			SpawnLocation.X = 550.f;
			SpawnLocation.Y = 950.f;
			SpawnLocation.Z = 55.f;

			FRotator SpawnRotation;
			SpawnRotation.Yaw = 0.f;
			SpawnRotation.Pitch = 0.f;
			SpawnRotation.Roll = 0.f;

			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = _myPlayer;
			SpawnParams.Instigator = _myPlayer->GetInstigator();
			SpawnParams.Name = FName(*FString(objectInfo.name().c_str()));

			// �ϳ��� ĳ���͸� ������Ų��.
			AIOCPTestProjectCharacter* SpawnCharacter
				= world->SpawnActor<AIOCPTestProjectCharacter>(_myPlayer->WhoToSpawn, SpawnLocation, 
					SpawnRotation, SpawnParams);
			SpawnCharacter->SpawnDefaultController();
			SpawnCharacter->SetPlayerId(objectInfo.objectid());
			SpawnCharacter->SetPlayerHealth(100.f);

			// �÷��̾� ������ �ִ´�.
			_object.Add(objectInfo.objectid(), SpawnCharacter);

			UE_LOG(LogClass, Log, TEXT("other player spawned."));
		}
	}
}

