// Vox Dei. All rights reserved.

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

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::BeginOverlap);	// Binding BeginOverlap delegate
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	if (FieldSystem)	// Generate impact for physical objects
	{
		URadialFalloff* RadialFalloff = NewObject<URadialFalloff>();
		RadialFalloff->SetRadialFalloff(ImpactMagnitude, 0.f, 1.f, 0.f, ImpactRadius, SweepResult.ImpactPoint, EFieldFalloffType::Field_FallOff_None);

		FieldSystem->ApplyPhysicsField(true, EFieldPhysicsType::Field_ExternalClusterStrain, nullptr, RadialFalloff);
	}

	ProjectileMesh->SetSimulatePhysics(true);
	ProjectileMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
}
