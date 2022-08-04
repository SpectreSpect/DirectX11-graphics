#include "ModeledObject.h"

ModeledObject::ModeledObject(Model* const model)
{
	this->model = model;
}

ModeledObject::~ModeledObject()
{
	// nothing
}

void ModeledObject::setModel(Model* model)
{
	this->model = model;
}

Model* ModeledObject::getModel() const
{
	return model;
}

void ModeledObject::setTexture(Texture* const texture, const unsigned int slot)
{
	textures[slot] = texture;
}

void ModeledObject::bindAllTextures()
{
	for (auto it = textures.begin(); it != textures.end(); it++)
		it->second->bind(it->first);
}

void ModeledObject::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	bindAllTextures();
	renderTarget->draw(model, state);
}

