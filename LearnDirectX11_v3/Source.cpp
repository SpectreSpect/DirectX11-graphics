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
#include "SkySphere.h"

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

	PointLight* pointLight = new PointLight(renderWindow, renderWindow->modelsContent->sphere);
	pointLight->setPosition(float3{ 0, 1, -3 });
	pointLight->setColor(float4{ 1, 1, 1, 1 });
	pointLight->setFactors(float3{ 1, 0.014f, 0.0007f });

	SkySphere* skySphere = new SkySphere(renderWindow, renderWindow->graphics->texturesContent->textureSky);

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

		renderWindow->Draw(skySphere, false);

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

		if ((int)timer % 2 == 1)
			modeledObject->setModel(renderWindow->modelsContent->plane);
		else
			modeledObject->setModel(renderWindow->modelsContent->sphere);

		renderWindow->Draw(modeledObject);

		renderWindow->display();
		renderWindow->endDeltaTime();
	}
}