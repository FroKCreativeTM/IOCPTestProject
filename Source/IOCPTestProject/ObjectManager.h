// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IOCPTestProject.h"

// 오브젝트들을 관리하기 위한 매니저 클래스
class IOCPTESTPROJECT_API AObjectManager
{	
public:	
	AObjectManager(class AIOCPTestProjectCharacter* player);
	~AObjectManager();

public : 
	static Protocol::GameObjectType GetObjectTypeById(int id)
	{
		int type = (id >> 24) & 0x7F;
		return (Protocol::GameObjectType)type;
	}

public : 
	// TODO : 나중엔 정확한 플레이어가 원하는 캐릭터를 받아오는 식으로 
	// protocol 수정할 필요 있음
	void Add(Protocol::ObjectInfo objectInfo, bool myPlayer = false);

private : 
	// 내가 어떤 캐릭을 들고 있는가.
	class AIOCPTestProjectCharacter* _myPlayer;
	TMap<int, AIOCPTestProjectCharacter*> _object;
};

extern TSharedPtr<AObjectManager> GObjectManager;
