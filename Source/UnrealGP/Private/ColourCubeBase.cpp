// Fill out your copyright notice in the Description page of Project Settings.


#include "ColourCubeBase.h"

#include "Net/UnrealNetwork.h"


// Sets default values
AColourCubeBase::AColourCubeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CubeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
}

void AColourCubeBase::Rep_CurrentColour()
{
	CubeComponent->SetMaterial(0, MaterialsMap[CurrentColour]);
}

void AColourCubeBase::ChangeColour()
{
	switch (CurrentColour)
	{
	case EColours::Red:
		CurrentColour = EColours::Green;
		break;
	case EColours::Green:
		CurrentColour = EColours::Blue;
		break;
	case EColours::Blue:
		CurrentColour = EColours::Red;
		break;
	}
	Rep_CurrentColour();
}

void AColourCubeBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AColourCubeBase, CurrentColour);
}

void AColourCubeBase::Interact_Implementation(ACharacter* Interactor)
{
	ChangeColour();
}
