// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION03_ESCAPEROOM_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    // how far player can "reach" to pick up objects
    float Reach=100.f;
    
    UPhysicsHandleComponent* physicsHandle = nullptr;
    
    UInputComponent* inputComponent = nullptr;
    
    FHitResult AttemptGrabForPhysicsBody();
    
    void GetPhysicsHandleComponent();
    void SetupInputComponent();
    
    FVector playerLocation();
    FRotator playerRotation();
    
    FVector getReachLimit();
    
    void Grab();
    void Release();
};
