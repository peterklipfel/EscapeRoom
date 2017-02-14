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
    if(!pressurePlate){
        UE_LOG(LogTemp, Error, TEXT("Pressure Plate not set"));
        return;
    }
}

float UOpenDoor::getTotalMassOnPressurePlate(){
    float totalMass = 0.f;
    TArray<AActor*> overlappingActors;
    if(!pressurePlate){ return totalMass; }
    pressurePlate->GetOverlappingActors(OUT overlappingActors);
    
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
        onOpen.Broadcast();
    } else {
        onClose.Broadcast();
    }
}

