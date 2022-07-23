#pragma once
#include "Graphics.h"
class VertexShader
{
public:
	VertexShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint = "main", LPCSTR pTarget = "vs_5_0");
	ID3D11VertexShader* get();
	ID3D11VertexShader** getpp();
	ID3D11InputLayout* getLayoutp();
	ID3D11InputLayout** getLayoutpp();
	LPVOID GetCodeBufferPointer();
	SIZE_T GetCodeBufferSize();
	void setVertexShader(Graphics* graphics);
	void setLayout(Graphics* graphics);
protected:
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderCode;
	ID3D11InputLayout* inputLayout;
};

