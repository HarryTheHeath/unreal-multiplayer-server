// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractIF.h"
#include "ColourCubeBase.generated.h"

UENUM(BlueprintType)
enum class EColours : uint8{
	Red,
	Green,
	Blue
};

UCLASS()
class UNREALGP_API AColourCubeBase : public AActor, public IInteractIF{
public:
private:
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AColourCubeBase();

	UFUNCTION(BlueprintCallable)
	void ChangeColour();

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<EColours, UMaterialInterface*> MaterialsMap;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* CubeComponent;

private:
	UPROPERTY(ReplicatedUsing=Rep_CurrentColour)
	EColours CurrentColour;

	UFUNCTION()
	void Rep_CurrentColour();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Interact_Implementation(ACharacter* Interactor) override;

};
