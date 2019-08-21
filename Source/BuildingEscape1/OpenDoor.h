// Copy RIghts Ali Hafeez 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE1_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    //void DoorOpening();
    //void DoorClosing();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnOpenRequest;
    UPROPERTY(BlueprintAssignable)
        FDoorEvent OnCloseRequest;

private:
    UPROPERTY(EditAnywhere)
        ATriggerVolume* PressurePlate = nullptr;
    UPROPERTY(VisibleAnywhere)
        float DoorCloseDelay = 1.3f;
    UPROPERTY(EditAnywhere)
        float RequiredMassToOpenDoor = 47.5;

    float LastDoorOpenTime;
    float TotalMassOnPressurePlate();

    //AActor* PawnActor; /// this actor will open or close the door
    AActor* Owner = nullptr;
	
};
