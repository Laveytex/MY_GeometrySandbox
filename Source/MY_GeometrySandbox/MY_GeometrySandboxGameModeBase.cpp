// Copyright Epic Games, Inc. All Rights Reserved.


#include "MY_GeometrySandboxGameModeBase.h"
#include "SandboxPawn.h"
#include "SandboxPlayerController.h"

AMY_GeometrySandboxGameModeBase::AMY_GeometrySandboxGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
	PlayerControllerClass = ASandboxPlayerController::StaticClass();
}