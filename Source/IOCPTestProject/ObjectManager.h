// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "IOCPTestProject.h"

// ������Ʈ���� �����ϱ� ���� �Ŵ��� Ŭ����
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
	// TODO : ���߿� ��Ȯ�� �÷��̾ ���ϴ� ĳ���͸� �޾ƿ��� ������ 
	// protocol ������ �ʿ� ����
	void Add(Protocol::ObjectInfo objectInfo, bool myPlayer = false);

private : 
	// ���� � ĳ���� ��� �ִ°�.
	class AIOCPTestProjectCharacter* _myPlayer;
	TMap<int, AIOCPTestProjectCharacter*> _object;
};

extern TSharedPtr<AObjectManager> GObjectManager;
