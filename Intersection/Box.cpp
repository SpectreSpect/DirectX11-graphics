#include "Box.h"

Box::Box(Graphics* graphics) : Shape(graphics)
{

	vertexShader = new DefaultVertexShader(graphics, L"VertexShader.hlsl");
	pixelShader = new PixelShader(graphics, L"PixelShader.hlsl");
	HRESULT hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Wall_Stone_017_BaseColor.jpg", nullptr, &SRVMink);
	//HRESULT hr = DirectX::CreateWICTextureFromFile(graphics->device, L"KrekColor.jpg", nullptr, &SRVMink);
	//HRESULT hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Leather_011_basecolor.jpg", nullptr, &SRVMink);
	if (FAILED(hr)) throw;
	hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Wall_Stone_017_Normal.jpg", nullptr, &SRVnormalMap);
	//hr = DirectX::CreateWICTextureFromFile(graphics->device, L"KrekNormal.jpg", nullptr, &SRVnormalMap);
	//hr = DirectX::CreateWICTextureFromFile(graphics->device, L"Leather_011_normal.jpg", nullptr, &SRVnormalMap);
	if (FAILED(hr)) throw;
	vertexSize = sizeof(VERTEX);

	for (int i = 0; i < sizeof(indices) / sizeof(int); i += 3)
	{
		//int index0 = indices[i];
		//int index1 = indices[i + 1];
		//int index2 = indices[i + 2];
		//VERTEX A = vertices[index0]; // 1
		//VERTEX C = vertices[index1]; // 2
		//VERTEX B = vertices[index2]; // 3

		//double u1 = A.texCoord.x;
		//double v1 = A.texCoord.y;

		//double u2 = B.texCoord.x;
		//double v2 = B.texCoord.y;

		//double u3 = C.texCoord.x;
		//double v3 = C.texCoord.y;

		//double du1 = u2 - u1;
		//double du2 = u3 - u2;

		//double dv1 = v2 - v1;
		//double dv2 = v3 - v2;

		//float3 E1;
		//E1.x = C.pos.x - A.pos.x;
		//E1.y = C.pos.y - A.pos.y;
		//E1.z = C.pos.z - A.pos.z;

		//float3 E2;
		//E2.x = B.pos.x - C.pos.x;
		//E2.y = B.pos.y - C.pos.y;
		//E2.z = B.pos.z - C.pos.z;

		//double d = 1 / (du1 * dv2 - du2 * dv1);

		//float3 bitangent;
		//bitangent.x = d * (dv2 * E1.x - dv1 * E2.x);
		//bitangent.y = d * (dv2 * E1.y - dv1 * E2.y);
		//bitangent.z = d * (dv2 * E1.z - dv1 * E2.z);

		//float3 tangent;
		//tangent.x = d * (du1 * E2.x - du2 * E1.x);
		//tangent.y = d * (du1 * E2.y - du2 * E1.y);
		//tangent.z = d * (du1 * E2.z - du2 * E1.z);

		//vertices[index0].bitangent = bitangent;
		//vertices[index0].tangent = tangent;

		//vertices[index1].bitangent = bitangent;
		//vertices[index1].tangent = tangent;

		//vertices[index2].bitangent = bitangent;
		//vertices[index2].tangent = tangent;

		int vertex1 = indices[i];
		int vertex2 = indices[i + 1];
		int vertex3 = indices[i + 2];

		float dU1 = vertices[vertex2].texCoord.x - vertices[vertex1].texCoord.x;
		float dU2 = vertices[vertex3].texCoord.x - vertices[vertex2].texCoord.x;

		float dV1 = vertices[vertex2].texCoord.y - vertices[vertex1].texCoord.y;
		float dV2 = vertices[vertex3].texCoord.y - vertices[vertex2].texCoord.y;

		float d = 1.0f / (dU1 * dV2 - dU2 * dV1);

		float3 E1 = {
			vertices[vertex2].pos.x - vertices[vertex1].pos.x,
			vertices[vertex2].pos.y - vertices[vertex1].pos.y,
			vertices[vertex2].pos.z - vertices[vertex1].pos.z,
		};

		float3 E2 = {
			vertices[vertex3].pos.x - vertices[vertex2].pos.x,
			vertices[vertex3].pos.y - vertices[vertex2].pos.y,
			vertices[vertex3].pos.z - vertices[vertex2].pos.z,
		};

		float3 B = {
			d * (dV2 * E1.x - dV1 * E2.x),
			d * (dV2 * E1.y - dV1 * E2.y),
			d * (dV2 * E1.z - dV1 * E2.z),
		};

		float3 T = {
			d * (dU1 * E2.x - dU2 * E1.x),
			d * (dU1 * E2.y - dU2 * E1.y),
			d * (dU1 * E2.z - dU2 * E1.z),
		};

		vertices[vertex1].tangent = T;
		vertices[vertex1].bitangent = B;

		vertices[vertex2].tangent = T;
		vertices[vertex2].bitangent = B;

		vertices[vertex3].tangent = T;
		vertices[vertex3].bitangent = B;
	}
	vertexBuffer = new Buffer(graphics, D3D11_BIND_VERTEX_BUFFER, vertices, sizeof(vertices));
}

void Box::draw(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix)
{

	graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
	graphics->deviceCon->PSSetShaderResources(1, 1, &SRVnormalMap);
	Shape::draw(graphics, mainWindow, viewMatrix, projectionMatrix);
}
