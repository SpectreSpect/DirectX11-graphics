#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <iostream>

class Graphics
{
public:
	IDXGISwapChain* swapChain;
	ID3D11Device* device;
	ID3D11DeviceContext* deviceCon;
	ID3D11RenderTargetView* backRenderTarget;
	ID3D11Texture2D* depthStencilTexture;
	ID3D11DepthStencilView* depthStencilView;
	HWND hwnd;
	int resWidth;
	int resHeight;
	double deltaTime;

	void initDirectX11(HWND outputWindow, int backWidth = -1, int backHeight = -1);
	void initDepthStencil();
	void setFirstOldClockAndDeltaTime();
	void updateDeltaTime();
private:
	long long oldClock;
};

