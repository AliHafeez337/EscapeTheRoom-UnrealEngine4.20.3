// Copy RIghts Ali Hafeez 2019

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"

#define OUT

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
    /*PawnActor = GetWorld()->GetFirstPlayerController()->GetPawn();*/
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

    /// Door opens and closes if pawn is in the pressure plate, not based on the mass
    /*if (PressurePlate && PressurePlate->IsOverlappingActor(PawnActor))*/
    
    if (TotalMassOnPressurePlate() > RequiredMassToOpenDoor)
    {
        DoorOpening();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }

    if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
    {
        DoorClosing();
    }
}

float UOpenDoor::TotalMassOnPressurePlate()
{
    float TotalMass = 0.0f;
    TArray<AActor*> OverlappingActors;

    /// find all the overlapping actors having masses
    PressurePlate->GetOverlappingActors(OUT OverlappingActors);

    for (const auto* Actor : OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        /*UE_LOG(LogTemp, Warning, TEXT("%fkg and %s on the pressure plate."), TotalMass, *Actor->GetName());*/
    }

    return TotalMass;
}

