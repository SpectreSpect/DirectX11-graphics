#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Model.h"
#include "RenderWindow.h"

class Sphere : public Transformable, public IDrawable
{
public:
	Sphere(RenderWindow* renderWindow);
	RenderWindow* getRenderWindow();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	RenderWindow* renderWindow;
	Model* model;
};

