#pragma once
#include "IDrawable.h"
#include "Transformable.h"


class RenderWindow;
class ModeledObject;

class PointLight2 : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	ModeledObject* model;
	struct PointLightDesc
	{
		float3 position;
		float kc;
		float kl;
		float kq;
		float4 color;
		bool turnedOn;
	};
	float kc = 1;
	float kl = 0.010f;
	float kq = 0.0005f;
	float4 color = { 1, 1, 1, 1 };
	bool turnedOn = true;


	PointLight2(RenderWindow* renderWindow, Model* model, bool bind = true);
	~PointLight2();
	void bind(RenderWindow* renderWindow);
	virtual void setPosition(float3 position) override;
	void setColor(float4 color);
	void setFactors(float3 factors);
	void setParams(float3 position, float4 color, float3 factors);
	void turn(bool on);




	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

