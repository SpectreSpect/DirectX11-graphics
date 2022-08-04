#pragma once
#include "IDrawable.h"
#include "Transformable.h"
#include "Texture.h"
#include "Model.h"
#include <vector>


class Model;
class RenderWindow;

class ModeledObject : public Transformable, public IDrawable
{
public:
	ModeledObject(Model* const model);
	~ModeledObject();
	void setModel(Model* model);
	Model* getModel() const;
	void setTexture(Texture* const texture, const unsigned int slot);
	//Texture* getTexture(const unsigned int slot) const;
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	Model* model;
	std::map<unsigned int, Texture*> textures;
	void bindAllTextures();
};

