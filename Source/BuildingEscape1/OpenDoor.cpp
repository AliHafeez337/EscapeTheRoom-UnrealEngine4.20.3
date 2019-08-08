// Copy RIghts Ali Hafeez 2019

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
    Owner = GetOwner();
    PawnActor = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::DoorOpening()
{
    FRotator NewRotation = FRotator(0.f, -70.f, 0.f);
    Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::DoorClosing()
{
    FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
    Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    if (PressurePlate && PressurePlate->IsOverlappingActor(PawnActor))
    {
        DoorOpening();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }

    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
        DoorClosing();
    }
}

