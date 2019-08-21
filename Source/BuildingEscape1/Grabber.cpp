// Copy RIghts Ali Hafeez 2019

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
    //UE_LOG(LogTemp, Warning, TEXT("Grabber working."));

    /// Look for attached physics handle in the pawn actor like we did in OpenDoor
    /// It will get the owner of the actor that this grabber (component) is attached to
    FindPhysicsHandleComponent();

    /// It will get the owner of the actor that this grabber (component) is attached to
    FindInputComponent();
}

void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Grab key pressed"));

    /// Line Trace to see if we collide with any physics body
    auto HitResult = GetFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto HitActor = HitResult.GetActor();

    if (HitActor) {
        if (!PhysicsHandle) {
            UE_LOG(LogTemp, Warning, TEXT("Physics handle not found"));
            return; 
        }
        PhysicsHandle->GrabComponentAtLocationWithRotation(
            ComponentToGrab,
            NAME_None,
            HitActor->GetActorLocation(),
            HitActor->GetActorRotation()
        );
    }
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Grab key Released"));
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Warning, TEXT("Physics handle not found"));
        return;
    }
    PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr) {
        UE_LOG(LogTemp, Error, TEXT("%s is missing physics component."), *(GetOwner()->GetName()));
    }
}

void UGrabber::FindInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent) {
        // on pressing a key that is mapped to "Grab" then look for a 'method' on 'this' (grabber)
        // reference to UGrabber class and method name is Grab
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
    else {
        UE_LOG(LogTemp, Error, TEXT("%s is missing input component."), *(GetOwner()->GetName()));
    }
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
    FVector LineTraceEnd = GetReachLineEnd();
    /// if the physics handle is attached to a physics body
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Warning, TEXT("Physics handle not found"));
        return;
    }
    if (PhysicsHandle->GrabbedComponent) {
        /// move the object we are holding
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }

}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
    /// geting player viewpoint
    FVector PlayerViewPointLocation = GetReachLineStart();
    FVector LineTrace = GetReachLineEnd();

    DrawDebugLine(
        GetWorld(),
        PlayerViewPointLocation,
        LineTrace,
        FColor(0, 0, 250),
        false,
        0.f,
        0,
        1.0f
    );

    /// ray cast out to reach a distance

    FHitResult Hit;
    FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
    GetWorld()->LineTraceSingleByObjectType(
        OUT Hit,
        PlayerViewPointLocation,
        LineTrace,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParams
    );

    //AActor* HitActor = Hit.GetActor();
    //if (HitActor) {
    //    UE_LOG(LogTemp, Warning, TEXT("Line trace hitting %s"), *(HitActor->GetName()));
    //}
    return Hit;
}

FVector UGrabber::GetReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation, OUT PlayerViewPointRotation
    );
    /*UE_LOG(LogTemp, Display, TEXT("Location: %s, Position: %s"),
        *PlayerViewPointLocation.ToString(),
        *PlayerViewPointRotation.ToString()
    );*/
    return PlayerViewPointLocation;
}

FVector UGrabber::GetReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation, OUT PlayerViewPointRotation
    );
    FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;
    return LineTraceEnd;
}
