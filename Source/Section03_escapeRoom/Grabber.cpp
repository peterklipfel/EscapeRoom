// Fill out your copyright notice in the Description page of Project Settings.

#include "Section03_escapeRoom.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("I'm a Grabber!"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
    FVector playerLocation;
    FRotator playerViewRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT playerLocation,
        OUT playerViewRotation
    );
    
    // UE_LOG(LogTemp, Warning, TEXT("Location: %s, Viewing: %s"),
    //     *PlayerLocation.ToString(),
    //     *PlayerViewRotation.ToString()
    // );
    
    // Add our Grabber debug vector
    FVector reachEnd = playerLocation + (playerViewRotation.Vector() * Reach);
    DrawDebugLine(GetWorld(),
                  playerLocation,
                  reachEnd,
                  FColor(255, 0, 0),
                  false,
                  0.f,
                  0.f,
                  10.f
                );
    
    // Trace out to where the grabbing vector ends
    FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

    FHitResult hit;

    GetWorld()->LineTraceSingleByObjectType(
        OUT hit,
        playerLocation,
        reachEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        traceParameters
    );
    AActor* hitActor = hit.GetActor();
    if(hitActor){
        FString name = hitActor->GetName();
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *name);
    };
    

}

