#pragma once
#include "MainWindow.h"
#include "Graphics.h"
#include "IDrawable.h"
#include "RenderTarget.h"
#include <chrono>
#include "ModelsContent.h"

class RenderWindow
{
public:
	MainWindow* window;
	Graphics* graphics;
	Camera* boundCamera;
	ModelsContent* modelsContent;
	bool isOpen = true;

	RenderWindow();
	~RenderWindow();
	void Draw(IDrawable* object, bool depthStencilOn = true);
	void display();
	void update();
	void dispatchEvents();
	void clear(float4 color);
	void updatePointLights();
	void setCamera(Camera* camera);
	void startDeltaTime();
	void endDeltaTime();
	void setBackRenderTargetAndDepthStencil();
private:
	MSG msg;
	std::chrono::steady_clock::time_point start;
};