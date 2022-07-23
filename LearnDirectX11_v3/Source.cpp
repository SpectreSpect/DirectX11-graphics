#include "MainWindow.h"
#include "Graphics.h"
#include "Shape.h"
#include "Box.h"
#include "DirectLightSource.h"
#include "Model.h"
#include "Camera.h"
#include "DirectLightSource.h"

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
	Model bug = Model(&graphics, (char*) "Models//Graphosoma.obj", new DefaultVertexShader(&graphics, L"VertexShader.hlsl"), new PixelShader(&graphics, L"PixelShader.hlsl"));
	Model hourse = Model(&graphics, (char*) "HorseModel.obj");
	DirectLightSource directLight = DirectLightSource(&graphics, (char*)"Models//sphere.obj");

	float color[4] = { 0.4f, 0.6f, 1.0f, 1.0f };
	bool gameLoop = true;
	float anlge = 0;
	MSG msg{};
	graphics.setFirstOldClockAndDeltaTime();
	mainWindow.activateCursor(false);
	float k = 0;
	float a = 0;
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
		graphics.deviceCon->OMSetRenderTargets(1, &graphics.backRenderTarget, graphics.depthStencilView);
		graphics.deviceCon->ClearRenderTargetView(graphics.backRenderTarget, color);

		box.camPos = mainCamera.position;
		box.draw(&graphics, &mainWindow, mainCamera.viewMatrix, mainCamera.projectionMatrix);

		k += 3.14 * graphics.deltaTime;
		a += 3.14 * graphics.deltaTime;

		hourse.position = float3{50, 0, 15};
		hourse.draw(&graphics, &mainCamera);
		//for (int y = 0; y < 3; y++)
		//	for(int x = 0; x < 3; x++)
		//{
		//	bug.position = float3{ x * 10.0f, y * 10.0f, sin((x + y) * 0.5f + k + ((rand() % 1000) / 1000) * 3) * 5};
		//	bug.rotationAngle = float3{ sin(k + 0.5f) * 3.14f * 0.1f, 0, cos(a) * 3.14f * 0.1f };
		//	bug.draw(&graphics, &mainCamera);
		//}

		bug.position = float3{10.0f, 10.0f + cos(a) * 3, 0};
		bug.rotationAngle = float3{ 0, a, 0 };
		bug.draw(&graphics, &mainCamera);

		directLight.draw(&graphics, &mainCamera);

		graphics.deviceCon->ClearDepthStencilView(graphics.depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
		mainWindow.rawMouseDelta = {};
		graphics.swapChain->Present(0, 0);
	}
}