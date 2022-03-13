// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "MyAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYABILITIESTUT_API UMyAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
    virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;

    UPROPERTY(Category = "Wizard Attributes | Health", EditAnywhere, BlueprintReadWrite)
    FGameplayAttributeData Health;

    UPROPERTY(Category = "Wizard Attributes | Health", EditAnywhere, BlueprintReadWrite)
    FGameplayAttributeData MaxHealth;

    //FGameplayAttributeData is the intended struct to be used for attributes by the system. However,
    //attributes can also be declared as simple floats. I am unsure if the attribute initialization method
    //further down functions with the struct, however the float method seems to be the more dated one.
};
