#pragma once
#include "Camera.h"
#include "Transform.h"
#include "RenderTarget.h"
#include "RenderState.h"

class IDrawable
{
public:
	virtual void draw(RenderTarget* renderTarget, RenderState* state) = 0;
	//virtual void draw(Transform* transform) = 0;
};

