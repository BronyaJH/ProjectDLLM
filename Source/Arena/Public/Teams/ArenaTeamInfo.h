// Copyright Ludens Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "System/GameplayTagStack.h"
#include "ArenaTeamInfo.generated.h"

class UArenaTeamCreationComponent;
class UArenaTeamSubsystem;

// UENUM(BlueprintType)
// enum class ETeam : uint8
// {	
// 	ET_Neutral UMETA(DisplayName = "Neutral"),
// 	ET_Attack UMETA(DisplayName = "Attack"),
// 	ET_Defense UMETA(DisplayName = "Defense"),
// 	
// 	ET_Max UMETA(DisplayName = "Max")
// };

/**
 * 
 */
UCLASS()
class ARENA_API AArenaTeamInfo : public AInfo
{
	GENERATED_BODY()

public:
	AArenaTeamInfo(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	friend UArenaTeamSubsystem;

	int32 GetTeamId() const { return TeamId; }

	//~AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//~End of AActor interface

protected:
	void RegisterWithTeamSubsystem(UArenaTeamSubsystem* Subsystem);
	void TryRegisterWithTeamSubsystem();

private:
	void SetTeamId(const int32 NewTeamId);

	UFUNCTION()
	void OnRep_Team();

	UFUNCTION()
	void OnRep_TeamTags();

public:
	friend UArenaTeamCreationComponent;
	
	UPROPERTY(ReplicatedUsing = OnRep_TeamTags)
	FGameplayTagStackContainer TeamTags;

private:
	UPROPERTY(ReplicatedUsing = OnRep_Team)
	int32 TeamId;
};
