#pragma once
#include "Model.h"

class ModelsContent
{
public:
	Model* sphere;
	Model* plane;

	ModelsContent(RenderWindow* renderWindow);
	~ModelsContent();
};

