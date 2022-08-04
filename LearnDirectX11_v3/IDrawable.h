#pragma once

class RenderTarget;
class RenderState;

class IDrawable
{
public:
	virtual void draw(RenderTarget* renderTarget, RenderState state) = 0;
	//virtual void draw(Transform* transform) = 0;
};