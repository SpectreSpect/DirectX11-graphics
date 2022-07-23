#include "Graphics.h"

void Graphics::initDirectX11(HWND outputWindow, int backWidth, int backHeight)
{
    hwnd = outputWindow;
    RECT clientRect;
    GetClientRect(outputWindow, &clientRect);
    if (backWidth == -1 || backHeight == -1)
    {
        backWidth = clientRect.right;
        backHeight = clientRect.bottom;
    }
    resWidth = backWidth;
    resHeight = backHeight;

	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    //swapChainDesc.BufferDesc.Width = backWidth;
    //swapChainDesc.BufferDesc.Height = backHeight;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.OutputWindow = outputWindow;
    swapChainDesc.Windowed = true;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, NULL, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &swapChain, &device, NULL, &deviceCon);
    if (FAILED(hr))throw;

    ID3D11Texture2D* backBuffer;
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)& backBuffer);
    if (FAILED(hr))throw;

    hr = device->CreateRenderTargetView(backBuffer, NULL, &backRenderTarget);
    if (FAILED(hr)) throw;

    D3D11_VIEWPORT viewPort{};
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.Width = clientRect.right;
    viewPort.Height = clientRect.bottom;
    deviceCon->RSSetViewports(1, &viewPort);
}

void Graphics::initDepthStencil()
{
    D3D11_TEXTURE2D_DESC depthStencilTextureDesc{};
    depthStencilTextureDesc.Width = resWidth;
    depthStencilTextureDesc.Height = resHeight;
    depthStencilTextureDesc. MipLevels = 1;
    depthStencilTextureDesc.ArraySize = 1;
    depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthStencilTextureDesc.SampleDesc.Count = 1;
    depthStencilTextureDesc.SampleDesc.Quality = 0;
    depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthStencilTextureDesc.CPUAccessFlags = 0;
    depthStencilTextureDesc.MiscFlags = 0;

    device->CreateTexture2D(&depthStencilTextureDesc, NULL, &depthStencilTexture);
    device->CreateDepthStencilView(depthStencilTexture, NULL, &depthStencilView);
    oldClock = clock();
}

void Graphics::setFirstOldClockAndDeltaTime()
{
    oldClock = clock();
    deltaTime = 1.0 / 60.0;
}

void Graphics::updateDeltaTime()
{
    deltaTime = max((double)(clock() - oldClock) / 1000.0, 0.0000001);
    oldClock = clock();
}
