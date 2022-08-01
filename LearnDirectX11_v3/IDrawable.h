#pragma once
#include "Camera.h"
#include "Transform.h"
#include "RenderTarget.h"
#include "TransformState.h"

class IDrawable
{
public:
	virtual void draw(RenderTarget* renderTarget, TransformState* state) = 0;
	//virtual void draw(Transform* transform) = 0;
};

