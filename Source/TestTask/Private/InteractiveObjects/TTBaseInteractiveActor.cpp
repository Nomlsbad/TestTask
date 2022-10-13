// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveObjects/TTBaseInteractiveActor.h"


ATTBaseInteractiveActor::ATTBaseInteractiveActor()
{
 	PrimaryActorTick.bCanEverTick = true;
}

void ATTBaseInteractiveActor::StartInteraction_Implementation(AActor* InstigatedBy)
{
	OnStartInteraction.Broadcast(InstigatedBy);
}

void ATTBaseInteractiveActor::StopInteraction_Implementation()
{
	OnStopInteraction.Broadcast();
}

void ATTBaseInteractiveActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (CollisionComponentNames.Num() == 0)
	{
		UE_LOG(LogTTInteractiveObjects, Warning, TEXT("%s : hasn't any CollisonComponents"), *this->GetName());
	}
	for(const auto ComponentName : CollisionComponentNames)
	{
		CollisionComponentReference.ComponentProperty = ComponentName;
		const auto CollisionComponent = Cast<UPrimitiveComponent>(CollisionComponentReference.GetComponent(this));
		CollisionComponents.Add(CollisionComponent);
	}
}

void ATTBaseInteractiveActor::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bStoreOverlappingActors)
	{
		OverlappingActors.Add(OtherActor);
	}
	++CountOfOverlappingActors;
}

void ATTBaseInteractiveActor::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bStoreOverlappingActors)
	{
		OverlappingActors.Remove(OtherActor);
	}
	--CountOfOverlappingActors;
}