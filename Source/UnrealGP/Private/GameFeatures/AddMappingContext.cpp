
#include "GameFeatures/AddMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "Components/GameFrameworkComponentManager.h"

void UAddMappingContext::OnGameFeatureActivating()
{
	Super::OnGameFeatureActivating();
	GameInstanceHandle = FWorldDelegates::OnStartGameInstance.AddUObject(this,&UAddMappingContext::HandleGameInstanceStart);
}

void UAddMappingContext::HandleGameInstanceStart(UGameInstance* GameInstance)
{
	UGameFrameworkComponentManager* ComponentManager = UGameInstance::GetSubsystem<UGameFrameworkComponentManager>(GameInstance);

	for (int i = 0; i < MappingEntries.Num(); ++i)
	{
		FGameFeatureMappingEntry MappingEntry = MappingEntries[i];
		const auto ExtensionHandle = UGameFrameworkComponentManager::FExtensionHandlerDelegate::CreateUObject(this, &UAddMappingContext::HandleExtensionDelegate, i);
		ExtensionHandlers.Add(ComponentManager->AddExtensionHandler(MappingEntry.CharacterClass,ExtensionHandle));
	}
}

void UAddMappingContext::HandleExtensionDelegate(AActor* ActorClass, FName Name, int EntryIndex)
{
	const ACharacter* PlayerCharacter = Cast<ACharacter>(ActorClass);
	const APlayerController* PlayerController = Cast<APlayerController>(PlayerCharacter->Controller);
	const auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		PlayerController->GetLocalPlayer());

	InputSubsystem->AddMappingContext(MappingEntries[EntryIndex].MappingContext, 0);
}