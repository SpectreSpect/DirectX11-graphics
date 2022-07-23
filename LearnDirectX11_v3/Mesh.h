#pragma once
#include <vector>
#include "mymath.h"
#include "Graphics.h"
#include "MainWindow.h"
#include <DirectXMath.h>
#include "Buffer.h"
#include "VertexShader.h"
#include "pixelShader.h"
#include "DefaultVertexShader.h"
#include "SampleState.h"
#include <WICTextureLoader.h>
#include <DDSTextureLoader.h>
#include "Camera.h"

class Mesh
{
public:

	std::vector<Vertex> vertices;
	std::vector<int> indices;
	float3 position;
	float3 rotationAngle;
	float3 scale = {1, 1, 1};
	float someAngle;
	Mesh(Graphics* graphics, std::vector<Vertex> vertices, std::vector<int> indices, VertexShader* vertexShader, PixelShader* pixelShader);
	void draw(Graphics* graphics, Camera* camera);
private:
	Buffer* vertexBuffer;
	Buffer* constantBuffer;
	Buffer* indexBuffer;
	DefaultVertexShader* defaultVertexShader;
	VertexShader* vertexShader;
	PixelShader* pixelShader;
	ID3D11ShaderResourceView* SRVMink;
	SampleState* sampleState;
	DirectX::XMMATRIX MVP;
	ID3D11ShaderResourceView* SRVnormalMap;
	void setupMesh(Graphics* graphics, VertexShader* vertexShader, PixelShader* pixelShader);
	void update(Graphics* graphics, Camera* camera);
};

