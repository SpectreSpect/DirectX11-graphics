#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "mymath.h"
#include <DirectXMath.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "Buffer.h"
#include "VertexShader.h"
#include "pixelShader.h"
#include "DefaultVertexShader.h"
#include "SampleState.h"

class Shape
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
	int vertexSize;
	float vertices[24 * 8]{
		// Front Face
	 -1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
	 -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f ,
	 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f ,
	 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f ,

		// Back Face
	 -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f ,
	 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f ,
	 -1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f ,

		// Top Face
	 -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	 -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
	 1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		// Bottom Face
	 -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
	 -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,

		// Left Face
	 -1.0f, -1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
	 -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	 -1.0f, 1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	 -1.0f, -1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,

		// Right Face
	 1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	};
	int indicesCount = 36;
	//int* indices;
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
	Buffer* vertexBuffer;
	Buffer* constantBuffer;
	Buffer* indexBuffer;
	DefaultVertexShader* defaultVertexShader;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11ShaderResourceView* SRVMink;
	SampleState* sampleState;
	DirectX::XMMATRIX MVP;
	float someAngle;
	float3 camPos;
	float3 objPos;
	Shape(Graphics* graphics);
	Shape();
	virtual void draw(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix);
private:
	void update(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix);
};
















/*
#pragma once
#include "Graphics.h"
#include "MainWindow.h"
#include "mymath.h"
#include <DirectXMath.h>
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>

class Shape
{
public:
	struct VERTEX
	{
		float3 pos;
		float2 texCoord;
	};
	int verticesCount = 24;
	VERTEX vertices[24]{
	{ -1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
	{ -1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ 1.0f, 1.0f, -1.0f, 1.0f, 0.0f },
	{ 1.0f, -1.0f, -1.0f, 1.0f, 1.0f },

		// Back Face
	{ -1.0f, -1.0f, 1.0f, 1.0f, 1.0f },
	{ 1.0f, -1.0f, 1.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ -1.0f, 1.0f, 1.0f, 1.0f, 0.0f },

		// Top Face
	{ -1.0f, 1.0f, -1.0f, 0.0f, 1.0f },
	{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
	{ 1.0f, 1.0f, -1.0f, 1.0f, 1.0f },

		// Bottom Face
	{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f },
	{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
	{ 1.0f, -1.0f, 1.0f, 0.0f, 0.0f },
	{ -1.0f, -1.0f, 1.0f, 1.0f, 0.0f },

		// Left Face
	{ -1.0f, -1.0f, 1.0f, 0.0f, 1.0f },
	{ -1.0f, 1.0f, 1.0f, 0.0f, 0.0f },
	{ -1.0f, 1.0f, -1.0f, 1.0f, 0.0f },
	{ -1.0f, -1.0f, -1.0f, 1.0f, 1.0f },

		// Right Face
	{ 1.0f, -1.0f, -1.0f, 0.0f, 1.0f },
	{ 1.0f, 1.0f, -1.0f, 0.0f, 0.0f },
	{ 1.0f, 1.0f, 1.0f, 1.0f, 0.0f },
	{ 1.0f, -1.0f, 1.0f, 1.0f, 1.0f },
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
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constantBuffer;
	ID3D11Texture2D* depthStencilTex;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* inputLayout;
	ID3D11ShaderResourceView* SRVMink;
	ID3D11SamplerState* samplerState;
	DirectX::XMMATRIX LWVP;
	float3 camPos;
	float camMoveSpeed = 0.004f;
	float2 acAngle;
	Shape(Graphics* graphics);
	void draw(Graphics* graphics, MainWindow* mainWindow);
private:
	void update(Graphics* graphics, MainWindow* mainWindow);
};
*/