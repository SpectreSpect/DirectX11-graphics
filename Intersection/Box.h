#pragma once
#include "Shape.h"
#define VALUE 0 
class Box : public Shape
{
public:
	struct VERTEX
	{
		float3 pos;
		float2 texCoord;
		float3 normal;
		float3 tangent;
		float3 bitangent;
	};
	int verticesCount = 24;

	//VERTEX vertices[24]
	//{
	//	// Front Face
	//	{ -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0, 0, 0, 0, 0, 0 },
	//	{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0, 0, 0, 0, 0, 0 },

	//	// Back Face
	//	{ -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0 },
	//	{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0 },
	//	{ -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0, 0, 0, 0, 0, 0 },

	//	// Top Face
	//	{ -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0, 0, 0, 0, 0, 0},

	//	// Bottom Face
	//	{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0, 0, 0, 0, 0, 0},

	//	// Left Face
	//	{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},

	//	// Right Face
	//	{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//	{ 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0},
	//};

	VERTEX vertices[24]
	{
		// Front Face
		{ -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE},
		{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE},
		{ 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },

		// Back Face
		{ -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },

		// Top Face
		{ -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },

		// Bottom Face
		{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },

		// Left Face
		{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },

		// Right Face
		{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
		{ 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE },
	};
	int indicesCount = 36;
	int indices[36]
	{
		// Front Face
		0, 1, 2,
		0, 2, 3,

		// Back Face
		4, 5, 6,
		4, 6, 7,

		// Top Face
		8, 9, 10,
		8, 10, 11,

		// Bottom Face
		12, 13, 14,
		12, 14, 15,

		// Left Face
		16, 17, 18,
		16, 18, 19,

		// Right Face
		20, 21, 22,
		20, 22, 23
	};
	ID3D11ShaderResourceView* SRVnormalMap;
	Box(Graphics* graphics);
	virtual void draw(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix) override;
};

