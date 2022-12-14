// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractiveActors/TTIntersectingInteractiveActor.h"


bool ATTIntersectingInteractiveActor::IsReadyToStartInteraction()
{
	return CountOfOverlappingActors == 1;
}

bool ATTIntersectingInteractiveActor::IsReadyToStopInteraction()
{
	return CountOfOverlappingActors == 0;
}

void ATTIntersectingInteractiveActor::OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (!IsReadyToStartInteraction()) return;
	
	StartInteraction(OtherActor);
}

void ATTIntersectingInteractiveActor::OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnOverlapEnd_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if (!IsReadyToStopInteraction()) return;
	
	StopInteraction();
}

void ATTIntersectingInteractiveActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	for (const auto CollisionComponent : CollisionComponents)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ATTIntersectingInteractiveActor::OnOverlapBegin);
		CollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ATTIntersectingInteractiveActor::OnOverlapEnd);
	}
}