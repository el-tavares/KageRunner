// Copyright Vox Dei. All Rights Reserved.

#include "Items/Projectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SceneComponent.h"
#include "Field/FieldSystemComponent.h"
#include "Field/FieldSystemNodes.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName(TEXT("BoxComponent")));
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Destructible, ECR_Overlap);
	BoxCollider->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);	// Binding OnComponentBeginOverlap delegate
	BoxCollider->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);	// Binding OnComponentHit delegate
	RootComponent = BoxCollider;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName(TEXT("StaticMeshComponent")));
	ProjectileMesh->SetupAttachment(GetRootComponent());
	ProjectileMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileMesh->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileMesh->SetGenerateOverlapEvents(false);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName(TEXT("MovementComponent")));
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 2000.f;
	ProjectileMovement->ProjectileGravityScale = 0.1f;

	FieldSystem = CreateDefaultSubobject<UFieldSystemComponent>(FName(TEXT("FieldSystemComponent")));
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Overlap")));

	if (FieldSystem)	// Generate impact for physical objects
	{
		URadialFalloff* RadialFalloff = NewObject<URadialFalloff>();
		RadialFalloff->SetRadialFalloff(ImpactMagnitude, 0.f, 1.f, 0.f, ImpactRadius, SweepResult.ImpactPoint, EFieldFalloffType::Field_FallOff_None);

		FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr, RadialFalloff);
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString(TEXT("Hit")));

	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
}
