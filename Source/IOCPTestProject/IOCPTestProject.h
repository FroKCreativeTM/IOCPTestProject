// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "EngineMinimal.h"

#include "Network/Protobuf/Protocol.pb.h"
#include "Network/Protobuf/Enum.pb.h"
#include "Network/Protobuf/Struct.pb.h"

DECLARE_LOG_CATEGORY_EXTERN(IOCPTestProject, Log, All);
#define ABLOG_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))
#define ABLOG_S(Verbosity) UE_LOG(IOCPTestProject, Verbosity, TEXT("%s"), *ABLOG_CALLINFO)
#define ABLOG(Verbosity, Format, ...) UE_LOG(IOCPTestProject, Verbosity, TEXT("%s %s"), *ABLOG_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))