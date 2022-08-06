#pragma once
#include "Graphics.h"
#include "mymath.h"
#include <DirectXMath.h>
#include "MainWindow.h"
class Camera
{
public:
	float3 position;
	float3 rotation;
	float3 velocity = {};
	float accelirationSpeed = 0.1f;
	float maxSpeedTime = 0.05f;
	float minSpeedTime = 0.1f;
	float moveSpeed = 30.0f;
	double rotationSpeed = 3.5f;
	bool responded;
	DirectX::XMMATRIX viewMatrix;
	DirectX::XMMATRIX projectionMatrix;
	Camera(float3 camPos, float3 camRotation, bool responded);
	Camera(bool responded = true);
	void update(Graphics* graphics);
	void responseInput(Graphics* graphics, MainWindow* mainWindow);
};

