#include "MainWindow.h"
#include "Graphics.h"
#include "Shape.h"
#include "Box.h"
#include "DirectLightSource.h"
#include "Model.h"
#include "Camera.h"
#include "DirectLightSource.h"
#include "PointLight.h"

D3D11_VIEWPORT updateViewPort(Graphics* graphics)
{
	RECT clientRect;
	GetClientRect(graphics->hwnd, &clientRect);
	D3D11_VIEWPORT viewPort{};
	viewPort.Width = clientRect.right - clientRect.left;
	viewPort.Height = clientRect.bottom - clientRect.top;
	return viewPort;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nCmdShow)
{
	MainWindow mainWindow;
	mainWindow.create(L"Main window");
	Graphics graphics;
	graphics.initDirectX11(mainWindow.hwnd);
	graphics.initDepthStencil();
	ShowWindow(mainWindow.hwnd, nCmdShow);

	Shape shape(&graphics);
	Shape light(&graphics);
	Box box = Box(&graphics);

	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = nullptr;

	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		throw;

	Camera mainCamera = Camera();
	mainCamera.position = {0, 3, -10};

	Texture textureSky = Texture(&graphics, L"Textures//texturify_pano-1-2.jpg");
	Texture stoneWallNormalMap = Texture(&graphics, L"Wall_Stone_017_Normal.jpg");
	Texture stoneWallAlbedo = Texture(&graphics, L"Wall_Stone_017_BaseColor.jpg");
	Texture flatNormalMap = Texture(&graphics, L"Textures\\14015-normal.jpg");

	Texture bugAlbedo = Texture(&graphics, L"Textures//Graphosoma.png");

	float factor2 = 0.014f;
	float factor3 = 0.0007f;

	PointLight whitePointLight = PointLight(&graphics, (char*)"Models//sphere.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->lightSourcePS);
	whitePointLight.setPosition(float3{ 0, 10, 0 });
	whitePointLight.setColor(float4{ 1, 1, 1, 1 });
	whitePointLight.setFactors(float3{ 1, factor2, factor3 });


	//Model bug = Model(&graphics, (char*) "Models//Graphosoma.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	//bug.setTexture(&bugAlbedo, 0);
	//bug.setTexture(&stoneWallNormalMap, 1);
	//bug.position = { 0, 10, 0 };

	Model skySphere = Model(&graphics, (char*)"Models//sphere.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->skyPS);
	skySphere.setTexture(&textureSky, 0);
	skySphere.scale = {-100, -100, -100};
	skySphere.drawDepthStencil = false;

	Model plane = Model(&graphics, (char*)"Models//Plane.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	plane.setTexture(&stoneWallAlbedo, 0);
	plane.setTexture(&stoneWallNormalMap, 1);
	plane.scale = float3{ 1, 1, 1 }; 

	Model metalicHand = Model(&graphics, (char*)"Models\\crytek-sponza-huge-vray-obj\\crytek-sponza-huge-vray.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	//Model metalicHand = Model(&graphics, (char*)"Models\\Sponza-master\\sponza.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	//Model metalicHand = Model(&graphics, (char*)"Models\\grey-knight\\ggfggf.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	//Model metalicHand = Model(&graphics, (char*)"Models\\Geralt\\source\\model.obj", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	//Model metalicHand = Model(&graphics, (char*)"Models\\moon-knight\\source\\yueguangqishi_battle.fbx", graphics.shadersContent->defaultVS, graphics.shadersContent->defaultPS);
	metalicHand.setTexture(&textureSky, 0);
	metalicHand.setTexture(&flatNormalMap, 1);
	metalicHand.position = {0, -30, -10};
	metalicHand.scale = { 0.2f, 0.2f, 0.2f };

	//float color[4] = { 0.4f, 0.6f, 1.0f, 1.0f };
	float color[4] = { 0, 0, 0, 1.0f };
	bool gameLoop = true;
	RECT clientRect{};
	GetClientRect(mainWindow.hwnd, &clientRect);

	MSG msg{};
	graphics.setFirstOldClockAndDeltaTime();
	mainWindow.activateCursor(false);
	float time = 0;
	while (gameLoop)
	{
		while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
				gameLoop = false;
		}
		if (!gameLoop)
			break;
		graphics.updateDeltaTime();
		mainCamera.responseInput(&graphics, &mainWindow);
		mainCamera.update(&graphics);

		graphics.deviceCon->ClearRenderTargetView(graphics.backRenderTarget, color);

		graphics.deviceCon->OMSetRenderTargets(1, &graphics.backRenderTarget, NULL);
		skySphere.position = mainCamera.position;
		skySphere.draw(&graphics, &mainCamera);
		graphics.deviceCon->OMSetRenderTargets(1, &graphics.backRenderTarget, graphics.depthStencilView);

		graphics.deviceCon->PSSetShaderResources(9, 1, &graphics.pointLightsSRV);
		graphics.deviceCon->PSSetConstantBuffers(9, 1, &graphics.lightsCountsBuffer);
		//textureSky.bind(2);

		plane.draw(&graphics, &mainCamera);
		whitePointLight.draw(&graphics, &mainCamera);
		//bug.draw(&graphics, &mainCamera);
		metalicHand.draw(&graphics, &mainCamera);



		graphics.deviceCon->ClearDepthStencilView(graphics.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		mainWindow.rawMouseDelta = {};
		graphics.swapChain->Present(0, 0);
	}
}