#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Sphere.h"

class SkySphere : public Transformable, public IDrawable
{
public:
	Sphere* sphere;
	SkySphere(RenderWindow* renderWindow, Texture* texture);
	~SkySphere();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
};