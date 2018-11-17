// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#define OUT	//Blank macro. Marks return by reference

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
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

/// Look for (assumed) attached Physics handle
void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		UE_LOG(LogTemp, Warning, TEXT("Phyics Handle found."));
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Physics Handle Component"), *GetOwner()->GetName());
	}
}

/// Look for (assumed) attached Input Component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Input Component Found."));

		// Bind input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s missing Input Component"), *GetOwner()->GetName());
	}
}

FHitResult UGrabber::GetFirstPhyiscsBodyInReach() const
{
	// If the physics handle is attached
		// Move the object that we're holding

	/// Get the player viewpoint this tick
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation, OUT ViewPointRotation
	);

	// End point of trace line (must be relative to origin, perform vector calculation
	// ViewPointRotation.Vector() Gives a vector of length 1 pointing in the direction the
	// player is pointing.

	FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector()*Reach;

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Raycast out to reach distance (private variable to store reach)
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		ViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// Say what we hit
	AActor *ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *(ActorHit->GetName()));
	}

	return FHitResult();
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Error, TEXT("Grab pressed"));

	// Line trace see if we reach any actors with physics sbody collision chanel set
	GetFirstPhyiscsBodyInReach();
	// If we hit something then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Error, TEXT("Grab released"));
	// Release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		
}

