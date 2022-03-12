// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTask.h"
#include "AbilityTask_MyTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMyTwoParamDelegate, float, FirstParamName, int32, SecondParamName);

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITIESTUT_API UAbilityTask_MyTask : public UGameplayTask
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FMyTwoParamDelegate OnCalled;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ExecuteMyTask", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_MyTask* CreateMyTask(TScriptInterface<IGameplayTaskOwnerInterface> OwningAbility, FName TaskInstanceName, float Examplevariable);

	virtual void Activate() override;
};
