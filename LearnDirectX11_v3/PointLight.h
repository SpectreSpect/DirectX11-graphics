#pragma once
#include "Model.h"
class PointLight : public Model
{
public:
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
	float4 color = {1, 1, 1, 1};
	bool turnedOn = true;
	PointLight(Graphics* graphics, char* modelPath, bool bind = true);
	PointLight(Graphics* graphics, char* modelPath, VertexShader* vertexShader, PixelShader* pixelShader, bool bind = true);
	void bind(Graphics* graphics);
	void setPosition(float3 position) override;
	void setColor(float4 color);
	void setFactors(float3 factors);
	void setParams(float3 position, float4 color, float3 factors);
	void turn(bool on);
	virtual void draw(Graphics* graphics, Camera* camera) override;
private:
	Graphics* graphics;
};

