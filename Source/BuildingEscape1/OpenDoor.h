// Copy RIghts Ali Hafeez 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


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

    void DoorOpening();
    void DoorClosing();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY(VisibleAnywhere)
        float OpenAngle = 80.f;
    UPROPERTY(EditAnywhere)
        ATriggerVolume* PressurePlate;
    UPROPERTY(EditAnywhere)
        float DoorCloseDelay = 2.3f;

    float LastDoorOpenTime;

    AActor* PawnActor;
    AActor* Owner;
	
};
