// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "Math/UnrealMathUtility.h"
#include "../GameplayAbilitiesTutCharacter.h"
#include "GameplayEffectTypes.h"
#include "GameplayTagContainer.h"

void UMyAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
    UAbilitySystemComponent* Source = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();

    FProperty* HealthAttribute = FindFieldChecked<FProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, Health));

    if (Data.EvaluatedData.Attribute.GetUProperty() == HealthAttribute)
    {
        // Get the Target actor
        
        AActor* DamagedActor = nullptr;
        AController* DamagedController = nullptr;
        if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
        {
            DamagedActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
            DamagedController = Data.Target.AbilityActorInfo->PlayerController.Get();
        }

        // Get the Source actor
        AActor* AttackingActor = nullptr;
        AController* AttackingController = nullptr;
        AController* AttackingPlayerController = nullptr;
        if (Source && Source->AbilityActorInfo.IsValid() && Source->AbilityActorInfo->AvatarActor.IsValid())
        {
            AttackingActor = Source->AbilityActorInfo->AvatarActor.Get();
            AttackingController = Source->AbilityActorInfo->PlayerController.Get();
            AttackingPlayerController = Source->AbilityActorInfo->PlayerController.Get();
            if (AttackingController == nullptr && AttackingActor != nullptr)
            {
                if (APawn* Pawn = Cast<APawn>(AttackingActor))
                {
                    AttackingController = Pawn->GetController();
                }
            }
        }
        
        // Clamp health
        Health = FMath::Clamp(Health.GetCurrentValue(), 0.0f, MaxHealth.GetCurrentValue());
        if (Health.GetCurrentValue() <= 0)
        {
            // Handle death with GASCharacter. Note this is just one example of how this could be done.
            if (AGameplayAbilitiesTutCharacter* Character = Cast<AGameplayAbilitiesTutCharacter>(DamagedActor))
            {
                // Construct a gameplay cue event for this death
                FGameplayCueParameters Params(Data.EffectSpec.GetContext());
                Params.RawMagnitude = Data.EvaluatedData.Magnitude;
                Params.NormalizedMagnitude = FMath::Abs(Data.EvaluatedData.Magnitude / MaxHealth.GetCurrentValue());
                /*Params.AggregatedSourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();
                Params.AggregatedTargetTags = *Data.EffectSpec.CapturedTargetTags.GetAggregatedTags();

                //Character->Die(DamagedController, DamagedActor, Data.EffectSpec, Params.RawMagnitude, Params.Normal);*/
            }
        }
        
    }
}