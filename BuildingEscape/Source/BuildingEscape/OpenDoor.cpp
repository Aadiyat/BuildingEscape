// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

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
	
	// Find player controller
	// Can store pointer to a Pawn in ActorThatOpens which is a pointer to an actor
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the trigger volume every frame
	// If the actor that opens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
	// Close door when actor that opens leaves the trigger volume
	else
	{
		CloseDoor();
	}
		
}


void UOpenDoor::OpenDoor()
{
	// Find owning actor
	AActor *door = GetOwner();
	FRotator doorRotation = door->GetActorRotation();
	doorRotation.Yaw = OpenAngle;	// Open door by preset angle
	door->SetActorRotation(doorRotation);

	return;
}

void UOpenDoor::CloseDoor()
{
	AActor *door = GetOwner();
	FRotator doorRotation = door->GetActorRotation();
	doorRotation.Yaw = 0;	// Reset door to initial angle
	door->SetActorRotation(doorRotation);

	return;
}
