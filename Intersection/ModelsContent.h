#pragma once
#include "Model.h"

class ModelsContent
{
public:
	Model* sphere;
	Model* plane;
	Model* tree;

	ModelsContent(RenderWindow* renderWindow);
	~ModelsContent();
};

