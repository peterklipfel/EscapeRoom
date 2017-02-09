// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SECTION03_ESCAPEROOM_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    virtual void OpenDoor();
    virtual void CloseDoor();

    
private:
    UPROPERTY(VisibleAnywhere)
    float OpenAngle = 180.f;

    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate;

    UPROPERTY(EditAnywhere)
    AActor* Owner;
    
    float getTotalMassOnPressurePlate();
    
    float LastDoorOpenTime;
    float DoorCloseDelay = 0.3f;
    float triggerWeight = 50.f;
};
