// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "cuda_lib_test.h"
#include "cuda_runtime.h"

#include "TestCudaTAct.generated.h"

UCLASS()
class DLLCUDACALL_API ATestCudaTAct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestCudaTAct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UFUNCTION(BlueprintCallable, Category = "CUDATest")
	bool SimpleCUDATest() {
		const int arraySize = 5;
		const int a[arraySize] = { 1,2,3,4,5 };
		const int b[arraySize] = { 10,20,30,40,50 };
		int c[arraySize] = {};

		std::string error_message;

		cudaError_t cuda_status = addWithCuda(c, a, b, arraySize, &error_message);
		if (cuda_status != cudaSuccess) {
			UE_LOG(LogTemp, Warning, TEXT("addWithCuda failed!\n"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(error_message.c_str()));
			return false;
		}
		UE_LOG(LogTemp, Warning, TEXT("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}"), c[0], c[1], c[2], c[3], c[4]);

		const int4 a_int4 = make_int4(1, 2, 3, 4);
		const int4 b_int4 = make_int4(10, 20, 30, 40);
		int4 c_int4;

		cuda_status = addWithCuda2(&c_int4, &a_int4, &b_int4, &error_message);
		if (cuda_status != cudaSuccess) {
			UE_LOG(LogTemp, Warning, TEXT("addWithCuda2 failed!\n"));
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FString(error_message.c_str()));
			return false;
		}
		UE_LOG(LogTemp, Warning, TEXT("{1,2,3,4} + {10,20,30,40} = {%d,%d,%d,%d}"), c_int4.x, c_int4.y, c_int4.z, c_int4.w);

		return true;
	}

};
