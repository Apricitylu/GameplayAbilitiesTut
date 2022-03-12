// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_MyTask.h"

UAbilityTask_MyTask* UAbilityTask_MyTask::CreateMyTask(TScriptInterface<IGameplayTaskOwnerInterface> OwningAbility, FName TaskInstanceName, float Examplevariable)
{

    UAbilityTask_MyTask* Instance = NewTask<UAbilityTask_MyTask>(OwningAbility, TaskInstanceName);

    return Instance;
}

void UAbilityTask_MyTask::Activate()
{
    OnCalled.Broadcast(500.f, 42);
}
