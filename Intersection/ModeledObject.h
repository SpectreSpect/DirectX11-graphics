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
	RenderWindow* renderWindow;
	ModeledObject(RenderWindow* const renderWindow, Model* const model);
	ModeledObject(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader);
	~ModeledObject();
	void setModel(Model* model);
	Model* getModel() const;
	void setTexture(Texture* const texture, const unsigned int slot);
	void setVertexShader(VertexShader* vertexShader);
	void setPixelShader(PixelShader* pixelShader);
	//Texture* getTexture(const unsigned int slot) const;
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
private:
	Model* model;
	std::map<unsigned int, Texture*> textures;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	void bindAllTextures();
	void constructor(RenderWindow* const renderWindow, Model* const model, VertexShader* vertexShader, PixelShader* pixelShader);
};

