
#include "Shape.h"

Shape::Shape(Graphics* graphics)
{
    constantBuffer = new Buffer(graphics, D3D11_BIND_CONSTANT_BUFFER, nullptr, sizeof(DirectX::XMMATRIX) * 2 + sizeof(float4), D3D11_USAGE_DYNAMIC, D3D11_CPU_ACCESS_WRITE);
    indexBuffer = new Buffer(graphics, D3D11_BIND_INDEX_BUFFER, indices, sizeof(indices));
    sampleState = new SampleState(graphics);
    vertexSize = sizeof(VERTEX);
}

Shape::Shape()
{
}

void Shape::update(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix)
{
    someAngle += 0.0001f;
    DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixRotationX(someAngle) * DirectX::XMMatrixTranslation(objPos.x, objPos.y, objPos.z);   
    //DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixTranslation(objPos.x, objPos.y, objPos.z);
    MVP = DirectX::XMMatrixTranspose(modelMatrix * viewMatrix * projectionMatrix);
    modelMatrix = DirectX::XMMatrixTranspose(modelMatrix);

    D3D11_MAPPED_SUBRESOURCE ms{};
    graphics->deviceCon->Map(constantBuffer->get(), NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

    memcpy(ms.pData, &modelMatrix, sizeof(modelMatrix));
    char* lastPos = (char*)ms.pData + sizeof(modelMatrix);
    memcpy(lastPos, &MVP, sizeof(MVP));
    lastPos = lastPos + sizeof(MVP);
    memcpy(lastPos, &camPos, sizeof(float4));
    graphics->deviceCon->Unmap(constantBuffer->get(), NULL);
}

void Shape::draw(Graphics* graphics, MainWindow* mainWindow, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX projectionMatrix)
{
    UINT strides = vertexSize;
    UINT offset = 0;
    update(graphics, mainWindow, viewMatrix, projectionMatrix);
    graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
    sampleState->set(graphics);
    graphics->deviceCon->IASetVertexBuffers(0, 1, vertexBuffer->getpp(), &strides, &offset);
    graphics->deviceCon->VSSetConstantBuffers(0, 1, constantBuffer->getpp());
    graphics->deviceCon->IASetIndexBuffer(indexBuffer->get(), DXGI_FORMAT_R32_UINT, 0);
    vertexShader->setVertexShader(graphics);
    graphics->deviceCon->PSSetShader(pixelShader->get(), NULL, NULL);
    vertexShader->setLayout(graphics);
    graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    graphics->deviceCon->DrawIndexed(indicesCount, 0, 0);
}













//
//#include "Shape.h"
//
//Shape::Shape(Graphics* graphics)
//{
//    D3D11_BUFFER_DESC vertexBufferDesc{};
//    vertexBufferDesc.ByteWidth = sizeof(vertices);
//    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA vertexSd{};
//    vertexSd.pSysMem = vertices;
//
//    HRESULT hr = graphics->device->CreateBuffer(&vertexBufferDesc, &vertexSd, &vertexBuffer);
//    if (FAILED(hr)) throw;
//
//    D3D11_BUFFER_DESC constantBufferDesc{};
//    constantBufferDesc.ByteWidth = sizeof(DirectX::XMMATRIX);
//    constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
//    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//    constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
//
//    hr = graphics->device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);
//    if (FAILED(hr)) throw;
//
//    D3D11_BUFFER_DESC indexBufferDesc{};
//    indexBufferDesc.ByteWidth = sizeof(indices);
//    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
//    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
//
//    D3D11_SUBRESOURCE_DATA indexSd{};
//    indexSd.pSysMem = indices;
//    hr = graphics->device->CreateBuffer(&indexBufferDesc, &indexSd, &indexBuffer);
//    if (FAILED(hr)) throw;
//
//    D3D11_TEXTURE2D_DESC depthTexDesc{};
//    depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
//    depthTexDesc.Width = graphics->resWidth;
//    depthTexDesc.Height = graphics->resHeight;
//    depthTexDesc.MipLevels = 1;
//    depthTexDesc.ArraySize = 1;
//    depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
//    depthTexDesc.SampleDesc.Count = 1;
//    depthTexDesc.SampleDesc.Quality = 0;
//    depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
//
//    hr = graphics->device->CreateTexture2D(&depthTexDesc, NULL, &depthStencilTex);
//    if (FAILED(hr)) throw;
//    hr = graphics->device->CreateDepthStencilView(depthStencilTex, NULL, &depthStencilView);
//    if (FAILED(hr)) throw;
//
//    ID3DBlob* vertexShaderCode;
//    ID3DBlob* pixelShaderCode;
//
//    hr = D3DCompileFromFile(L"VertexShader.hlsl", NULL, NULL, "main", "vs_5_0", NULL, NULL, &vertexShaderCode, NULL);
//    if (FAILED(hr)) throw;
//    hr = D3DCompileFromFile(L"PixelShader.hlsl", NULL, NULL, "main", "ps_5_0", NULL, NULL, &pixelShaderCode, NULL);
//    if (FAILED(hr)) throw;
//
//    hr = graphics->device->CreateVertexShader(vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), NULL, &vertexShader);
//    if (FAILED(hr)) throw;
//    hr = graphics->device->CreatePixelShader(pixelShaderCode->GetBufferPointer(), pixelShaderCode->GetBufferSize(), NULL, &pixelShader);
//    if (FAILED(hr)) throw;
//
//    D3D11_INPUT_ELEMENT_DESC elementDesc[2]
//    { {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0},
//      {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT , 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0}
//    };
//
//    hr = graphics->device->CreateInputLayout(elementDesc, 2, vertexShaderCode->GetBufferPointer(), vertexShaderCode->GetBufferSize(), &inputLayout);
//    if (FAILED(hr)) throw;
//
//    D3D11_SAMPLER_DESC samplerDesc{};
//    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
//    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
//    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
//    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
//    samplerDesc.MipLODBias = 0;
//    samplerDesc.MaxAnisotropy = 0;
//    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
//    samplerDesc.BorderColor[4] = {};
//    samplerDesc.MinLOD = 0;
//    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
//    hr = graphics->device->CreateSamplerState(&samplerDesc, &samplerState);
//    if (FAILED(hr)) throw;
//
//    hr = DirectX::CreateWICTextureFromFile(graphics->device, L"mink.jpg", nullptr, &SRVMink);
//    if (FAILED(hr)) throw;
//}
//
//void Shape::update(Graphics* graphics, MainWindow* mainWindow)
//{
//
//    acAngle.x += (float)mainWindow->rawMouseDelta.x * 0.001f;
//    acAngle.y += (float)mainWindow->rawMouseDelta.y * 0.001f;
//    mainWindow->rawMouseDelta = {};
//
//    DirectX::XMVECTOR tangent = DirectX::XMVector3Transform(DirectX::XMVectorSet(0, 0, 1, 0), DirectX::XMMatrixRotationX(acAngle.y) * DirectX::XMMatrixRotationY(acAngle.x));
//    DirectX::XMVECTOR binormal = DirectX::XMVector3Transform(DirectX::XMVectorSet(1, 0, 0, 0), DirectX::XMMatrixRotationX(acAngle.y) * DirectX::XMMatrixRotationY(acAngle.x));
//
//    if (GetAsyncKeyState('W'))
//    {
//        camPos.x += DirectX::XMVectorGetX(tangent) * camMoveSpeed;
//        camPos.y += DirectX::XMVectorGetY(tangent) * camMoveSpeed;
//        camPos.z += DirectX::XMVectorGetZ(tangent) * camMoveSpeed;
//    }
//    if (GetAsyncKeyState('D'))
//    {
//        camPos.x += DirectX::XMVectorGetX(binormal) * camMoveSpeed;
//        camPos.y += DirectX::XMVectorGetY(binormal) * camMoveSpeed;
//        camPos.z += DirectX::XMVectorGetZ(binormal) * camMoveSpeed;
//    }
//    if (GetAsyncKeyState('S'))
//    {
//        camPos.x -= DirectX::XMVectorGetX(tangent) * camMoveSpeed;
//        camPos.y -= DirectX::XMVectorGetY(tangent) * camMoveSpeed;
//        camPos.z -= DirectX::XMVectorGetZ(tangent) * camMoveSpeed;
//    }
//    if (GetAsyncKeyState('A'))
//    {
//        camPos.x -= DirectX::XMVectorGetX(binormal) * camMoveSpeed;
//        camPos.y -= DirectX::XMVectorGetY(binormal) * camMoveSpeed;
//        camPos.z -= DirectX::XMVectorGetZ(binormal) * camMoveSpeed;
//    }
//
//    RECT clientRect{};
//    GetClientRect(graphics->hwnd, &clientRect);
//    DirectX::XMMATRIX localMatrix = DirectX::XMMatrixIdentity();
//    DirectX::XMMATRIX worldMatrix = DirectX::XMMatrixTranslation(objPos.x, objPos.y, objPos.z);
//    DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixTranslation(-camPos.x, -camPos.y, -camPos.z) * DirectX::XMMatrixRotationY(-acAngle.x) * DirectX::XMMatrixRotationX(-acAngle.y);
//    DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(0.4 * 3.14, (float)clientRect.right / clientRect.bottom, 0.1f, 1000);
//    LWVP = DirectX::XMMatrixTranspose(localMatrix * worldMatrix * viewMatrix * projectionMatrix);
//
//    D3D11_MAPPED_SUBRESOURCE ms{};
//    graphics->deviceCon->Map(constantBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
//    memcpy(ms.pData, &LWVP, sizeof(LWVP));
//    graphics->deviceCon->Unmap(constantBuffer, NULL);
//}
//
//void Shape::draw(Graphics* graphics, MainWindow* mainWindow)
//{
//    UINT strides = sizeof(VERTEX);
//    UINT offset = 0;
//    update(graphics, mainWindow);
//    graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
//    graphics->deviceCon->PSSetSamplers(0, 1, &samplerState);
//    graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
//    graphics->deviceCon->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);
//    graphics->deviceCon->VSSetConstantBuffers(0, 1, &constantBuffer);
//    graphics->deviceCon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//    graphics->deviceCon->VSSetShader(vertexShader, NULL, NULL);
//    graphics->deviceCon->PSSetShader(pixelShader, NULL, NULL);
//    graphics->deviceCon->IASetInputLayout(inputLayout);
//    graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//    objPos = { 0, 0, 0 };
//    graphics->deviceCon->DrawIndexed(indicesCount, 0, 0);
//
//
//
//    update(graphics, mainWindow);
//    graphics->deviceCon->OMSetRenderTargets(1, &graphics->backRenderTarget, graphics->depthStencilView);
//    graphics->deviceCon->PSSetSamplers(0, 1, &samplerState);
//    graphics->deviceCon->PSSetShaderResources(0, 1, &SRVMink);
//    graphics->deviceCon->IASetVertexBuffers(0, 1, &vertexBuffer, &strides, &offset);
//    graphics->deviceCon->VSSetConstantBuffers(0, 1, &constantBuffer);
//    graphics->deviceCon->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
//    graphics->deviceCon->VSSetShader(vertexShader, NULL, NULL);
//    graphics->deviceCon->PSSetShader(pixelShader, NULL, NULL);
//    graphics->deviceCon->IASetInputLayout(inputLayout);
//    graphics->deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//    objPos = { 0, 0, 3 };
//    graphics->deviceCon->DrawIndexed(indicesCount, 0, 0);
//
//    graphics->deviceCon->ClearDepthStencilView(graphics->depthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
//}
