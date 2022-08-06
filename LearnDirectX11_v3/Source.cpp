#include "MainWindow.h"
#include "Graphics.h"
#include "Shape.h"
#include "Box.h"
#include "DirectLightSource.h"
#include "Model.h"
#include "Camera.h"
#include "DirectLightSource.h"
#include "PointLight.h"
#include "GameObject.h"
#include "Sphere.h"
#include "TwoBalls.h"
#include <chrono>
#include "Spherenic.h"
#include "ModeledObject.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	RenderWindow* renderWindow = new RenderWindow();
	Camera* mainCamera = new Camera(true);
	mainCamera->position = { 0, 3, -10 };
	renderWindow->setCamera(mainCamera);

	Sphere* sphere = new Sphere(renderWindow);
	Spherenic* spherenic = new Spherenic(renderWindow);

	ModeledObject* modeledObject = new ModeledObject(renderWindow, renderWindow->modelsContent->sphere);
	modeledObject->setPosition({0, 3, 0});

	ModeledObject* plane = new ModeledObject(renderWindow, renderWindow->modelsContent->plane);
	plane->setTexture(renderWindow->graphics->texturesContent->stoneWallAlbedo, 0);
	plane->setTexture(renderWindow->graphics->texturesContent->stoneWallNormalMap, 1);
	plane->setScale({1, 1, 1});

	//PointLight whitePointLight = PointLight(renderWindow->graphics, (char*)"Models//sphere.obj", renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->lightSourcePS);
	//whitePointLight.setPosition(float3{ 0, 1, -3 });
	//whitePointLight.setColor(float4{ 1, 1, 1, 1 });
	//whitePointLight.setFactors(float3{ 1, 0.014f, 0.0007f });

	PointLight2* pointLight = new PointLight2(renderWindow, renderWindow->modelsContent->sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 1, 1, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	int size = renderWindow->graphics->pointLights2.size();


	float k = 0;
	float timer = 0;

	while (renderWindow->isOpen)
	{
		renderWindow->startDeltaTime();
		renderWindow->dispatchEvents();
		renderWindow->update();
		renderWindow->setBackRenderTargetAndDepthStencil();
		renderWindow->updatePointLights();
		renderWindow->clear(float4{ 0, 0, 0, 0 });

		timer += 1 * renderWindow->graphics->deltaTime;

		for (int i = 0; i < 1000; i++)
			renderWindow->Draw(plane);

		renderWindow->Draw(sphere);
		sphere->setPosition({k * 0.1f, 0, 3});
		sphere->setRotation({k * 0.1f, 0, 0});

		renderWindow->Draw(spherenic);
		spherenic->setRotation({k, 0, 0});
		spherenic->setPosition({ cos(k * 0.1f) * 7, 0, sin(k * 0.1f) * 7});

		k += 3.14f * renderWindow->graphics->deltaTime;
		pointLight->setPosition({ cos(k) * 2, 1, sin(k) * 2 });
		renderWindow->Draw(pointLight);
		//whitePointLight.setPosition({cos(0.0f) * 2, 1, sin(0.0f) * 2});
		//whitePointLight.draw(renderWindow->graphics, mainCamera);

		if ((int)timer % 2 == 1)
			modeledObject->setModel(renderWindow->modelsContent->plane);
		else
			modeledObject->setModel(renderWindow->modelsContent->sphere);

		renderWindow->Draw(modeledObject);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}