#include "Sphere.h"

//Sphere::Sphere(Graphics* graphics)
//{
//	this->graphics = graphics;
//	model = new Model(graphics, (char*)"Models//sphere.obj", graphics->shadersContent->defaultVS, graphics->shadersContent->defaultPS);
//	model->setTexture(graphics->texturesContent->stoneWallAlbedo, 0);
//	model->setTexture(graphics->texturesContent->stoneWallNormalMap, 1);
//}
//
//void Sphere::draw(Transform* transform)
//{
//	this->transfrom.Update(position, rotation, scale);
//	model->position = position;
//	model->rotation = rotation;
//	model->scale = scale;
//	model->draw(graphics, graphics->cameraToDraw, transform);
//}

Sphere::Sphere(RenderWindow* renderWindow)
{
	this->renderWindow = renderWindow;
	Graphics* graphics = renderWindow->graphics;

	model = new Model(graphics, (char*)"Models//sphere.obj", graphics->shadersContent->defaultVS, graphics->shadersContent->defaultPS);
	model->setTexture(graphics->texturesContent->stoneWallAlbedo, 0);
	model->setTexture(graphics->texturesContent->stoneWallNormalMap, 1);
}

RenderWindow* Sphere::getRenderWindow()
{
	return renderWindow;
}

void Sphere::draw(RenderTarget* renderTarget, RenderState* state)
{
	state->modelMatrix = state->modelMatrix * modelMatrix;
	renderTarget->draw(model, state);

	//model->position = position;
	//model->rotation = rotation;
	//model->scale = scale;
	//model->draw(renderWindow->graphics, renderWindow->boundCamera);
}
