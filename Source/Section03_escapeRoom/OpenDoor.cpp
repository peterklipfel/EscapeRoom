// Fill out your copyright notice in the Description page of Project Settings.

#include "Section03_escapeRoom.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
    
    Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
}

void UOpenDoor::CloseDoor()
{
    Owner->SetActorRotation(FRotator(0.0f, 270.0f, 0.0f));
}

float UOpenDoor::getTotalMassOnPressurePlate(){
    float totalMass = 0.f;
    TArray<AActor*> overlappingActors;
    PressurePlate->GetOverlappingActors(OUT overlappingActors);
    
    for (const AActor* actor : overlappingActors){
        totalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }
    return totalMass;
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    float currentTime = GetWorld()->GetTimeSeconds();
    if(getTotalMassOnPressurePlate() > triggerWeight){
        OpenDoor();
        LastDoorOpenTime = currentTime;
    }
    if( currentTime - LastDoorOpenTime > DoorCloseDelay ){
        
        CloseDoor();
    }
}

