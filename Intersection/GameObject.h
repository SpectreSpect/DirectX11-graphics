#pragma once
#include "Model.h"
#include "IDrawable.h"
class GameObject
{
public:
	Graphics* graphics;
	Model* model;
	float3 position = {};
	float3 rotation = {};
	float3 scale = {1, 1, 1};

	GameObject(Graphics* graphics);
	void setModel(Model* model);
	virtual void update();
	virtual void draw();
};

