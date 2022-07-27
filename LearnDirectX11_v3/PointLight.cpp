#include "PointLight.h"

PointLight::PointLight(Graphics* graphics, char* modelPath, bool bind) : Model(graphics, modelPath)
{
	if (bind)
		this->bind(graphics);
	this->graphics = graphics;
}

PointLight::PointLight(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader, bool bind) : Model(graphics, modelPath, vertexShader, pixelShader)
{
	if (bind)
		this->bind(graphics);
	this->graphics = graphics;
}

void PointLight::bind(Graphics* graphics)
{
	graphics->pointLights.push_back(this);
	graphics->updatePointLights();
}

void PointLight::setPosition(float3 position)
{
	this->position = position;
	graphics->updatePointLights();
}

void PointLight::setColor(float4 color)
{
	this->color = color;
	graphics->updatePointLights();
}

void PointLight::setFactors(float3 factors)
{

	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	graphics->updatePointLights();
}

void PointLight::setParams(float3 position, float4 color, float3 factors)
{
	this->position = position;
	this->color = color;
	kc = factors.x;
	kl = factors.y;
	kq = factors.z;
	graphics->updatePointLights();
}

void PointLight::turn(bool on)
{
	turnedOn = on;
	graphics->updatePointLights();
}

void PointLight::draw(Graphics* graphics, Camera* camera)
{
	//graphics->deviceCon->PSGetShaderResources(9, 1, &graphics->pointLightsSRV);
	Model::draw(graphics, camera);
}