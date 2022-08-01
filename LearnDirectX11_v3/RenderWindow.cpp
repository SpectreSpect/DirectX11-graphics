#include "RenderWindow.h"

RenderWindow::RenderWindow()
{
	window = new MainWindow();
	window->create(L"Window");
	graphics = new Graphics();
	graphics->initDirectX11(window->hwnd);
	graphics->initDepthStencil();
	ShowWindow(window->hwnd, NULL);
	graphics->initTexturesContent();

	RAWINPUTDEVICE rid{};
	rid.usUsagePage = 0x01;
	rid.usUsage = 0x02;
	rid.dwFlags = 0;
	rid.hwndTarget = nullptr;

	if (!RegisterRawInputDevices(&rid, 1, sizeof(rid)))
		throw;
}

RenderWindow::~RenderWindow()
{
	delete window;
	delete graphics;
}

//void RenderWindow::showWindow()
//{
//}

void RenderWindow::Draw(IDrawable* object)
{
	//object->draw();
}

void RenderWindow::display()
{
	graphics->deviceCon->ClearDepthStencilView(graphics->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	window->rawMouseDelta = {};
	graphics->swapChain->Present(0, 0);
}

void RenderWindow::setCamera(Camera* camera)
{
	boundCamera = camera;
}
