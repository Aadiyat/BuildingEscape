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

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber is ready for grabbing."));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Get the player viewpoint this tick
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT ViewPointLocation, OUT ViewPointRotation
		);

	/*UE_LOG(LogTemp, Warning, TEXT("Locaton: %s | Rotation: %s."),
			*ViewPointLocation.ToString(), *ViewPointRotation.ToString());*/

	// Draw a red trace out in the world to visualise
	// End point of trace line (must be relative to origin, perform vector calculation
	// ViewPointRotation.Vector() Gives a vector of length 1 pointing in the direction the
	// player is pointing.

	FVector LineTraceEnd = ViewPointLocation + ViewPointRotation.Vector()*Reach;
	DrawDebugLine(
		GetWorld(),
		ViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0, 155),
		false,
		0.f,
		0.f,
		10);
	// Raycast out to reach distance (private variable to store reach)
	// Say what we hit

}

