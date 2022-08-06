#include "PointLight2.h"
#include "RenderWindow.h"
#include "ModeledObject.h"

PointLight2::PointLight2(RenderWindow* renderWindow, Model* model, bool bind)
{
	this->model = new ModeledObject(renderWindow, model, renderWindow->graphics->shadersContent->defaultVS, renderWindow->graphics->shadersContent->lightSourcePS);
	this->model->setTexture(renderWindow->graphics->texturesContent->stoneWallAlbedo, 0);
	this->model->setTexture(renderWindow->graphics->texturesContent->stoneWallNormalMap, 1);

	if (bind)
		this->bind(renderWindow);
	this->renderWindow = renderWindow;
}

PointLight2::~PointLight2()
{
	delete model;
}

void PointLight2::bind(RenderWindow* renderWindow)
{
	renderWindow->graphics->pointLights2.push_back(this);
	renderWindow->graphics->updatePointLights();
}

void PointLight2::setPosition(float3 position)
{
	Transformable::setPosition(position);
	renderWindow->graphics->updatePointLights();
}

void PointLight2::setColor(float4 color)
{
	this->color = color;
	renderWindow->graphics->updatePointLights();
}

void PointLight2::setFactors(float3 factors)
{
	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	renderWindow->graphics->updatePointLights();
}

void PointLight2::setParams(float3 position, float4 color, float3 factors)
{
	Transformable::setPosition(position);
	this->color = color;
	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	renderWindow->graphics->updatePointLights();
}

void PointLight2::turn(bool on)
{
	turnedOn = on;
	renderWindow->graphics->updatePointLights();
}

void PointLight2::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}