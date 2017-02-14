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
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	
    GetPhysicsHandleComponent();
    SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
    
    if(!physicsHandle){ return; }
    if(physicsHandle->GrabbedComponent){
        physicsHandle->SetTargetLocation(getReachLimit());
    }
}

void UGrabber::GetPhysicsHandleComponent(){
    if(!GetOwner()){ return; }
    FString name = GetOwner()->GetName();
    physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
//    GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if(physicsHandle){
        UE_LOG(LogTemp, Warning, TEXT("Found phyics handle component on Owner: %s"), *name);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Owner: %s does not have physics handle component"), *name);
    }
}

void UGrabber::SetupInputComponent(){
    if(!GetOwner()){ return; }
    FString name = GetOwner()->GetName();
    inputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if(inputComponent){
        UE_LOG(LogTemp, Warning, TEXT("Found input component on Owner: %"), *name);
        
        inputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        
        inputComponent->BindAction("Release", IE_Pressed, this, &UGrabber::Release);
    } else {
        UE_LOG(LogTemp, Error, TEXT("Owner: %s does not have an input component"), *name);
    }
}

void UGrabber::Grab() {
    UE_LOG(LogTemp, Warning, TEXT("Grab Pressed!"));

    if(!physicsHandle){ return; }

    FHitResult hitResult = AttemptGrabForPhysicsBody();
    UPrimitiveComponent* componentToGrab = hitResult.GetComponent();
    if(!componentToGrab){
        UE_LOG(LogTemp, Error, TEXT("hitResult.GetComponent Failed"));
        return;
    }
    AActor* hitActor = hitResult.GetActor();
    
    if(hitActor){
      physicsHandle->GrabComponent(componentToGrab, NAME_None, componentToGrab->GetOwner()->GetActorLocation(), true);
    } else {
        UE_LOG(LogTemp, Error, TEXT("hitActor Failed"));
        return;
    }
}

void UGrabber::Release() {
    UE_LOG(LogTemp, Warning, TEXT("Grab Released!"));

    if(!physicsHandle){
        UE_LOG(LogTemp, Error, TEXT("No physics handle"));
        return;
    }

    physicsHandle->ReleaseComponent();
}

FVector UGrabber::playerLocation() {
    FVector playerLoc;
    FRotator playerRot;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT playerLoc,
        OUT playerRot
    );
    return playerLoc;
}

FRotator UGrabber::playerRotation() {
    FVector playerLoc;
    FRotator playerRot;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT playerLoc,
        OUT playerRot
    );
    return playerRot;
}

// Trace out to where the grabbing vector ends
FVector UGrabber::getReachLimit() {
    FVector reachEnd = playerLocation() + (playerRotation().Vector() * Reach);
    return reachEnd;
}

FHitResult UGrabber::AttemptGrabForPhysicsBody() {
    FVector reachEnd = getReachLimit();
    FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());
    
    FHitResult hit;
    
    GetWorld()->LineTraceSingleByObjectType(
        OUT hit,
        playerLocation(),
        reachEnd,
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        traceParameters
    );
    AActor* hitActor = hit.GetActor();
    if(hitActor){
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(hitActor->GetName()));
    };
    
    return hit;
}
