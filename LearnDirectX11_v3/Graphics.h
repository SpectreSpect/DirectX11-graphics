#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <iostream>
#include "ShadersContent.h"
#include "TexturesContent.h"
#include <vector>
#include "RenderTarget.h"

class Camera;
class PointLight;
class Graphics
{
public:
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceCon;
	ID3D11RenderTargetView* backRenderTarget;
	RenderTarget* renderTarget;
	ID3D11Texture2D* depthStencilTexture;
	ID3D11DepthStencilView* depthStencilView;
	ShadersContent* shadersContent;
	TexturesContent* texturesContent;
	HWND hwnd;
	Camera* cameraToDraw;
	std::vector<PointLight*> pointLights;
	int maxPointLightsCount = 500;
	ID3D11Buffer* pointLightsBuffer;
	ID3D11ShaderResourceView* pointLightsSRV;
	ID3D11Buffer* lightsCountsBuffer;
	int resWidth;
	int resHeight;
	double deltaTime = 1 / 60.0;
	Graphics();
	void initDirectX11(HWND outputWindow, int backWidth = -1, int backHeight = -1);
	void initDepthStencil();
	void initTexturesContent();
	void setFirstOldClockAndDeltaTime();
	void updateDeltaTime();
	void bindPointLights();
	void updatePointLights();
	void setCameraToDraw(Camera* camera);
private:
	long long oldClock;
};

