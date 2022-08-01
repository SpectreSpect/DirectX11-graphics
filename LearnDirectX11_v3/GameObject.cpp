#include "GameObject.h"

GameObject::GameObject(Graphics* graphics)
{
	this->graphics = graphics;
}

void GameObject::setModel(Model* model)
{
	this->model = model;
}

void GameObject::update()
{
}

void GameObject::draw()
{
	model->position = position;
	model->rotation = rotation;
	model->scale = scale;
	model->draw(graphics, graphics->cameraToDraw);
}
