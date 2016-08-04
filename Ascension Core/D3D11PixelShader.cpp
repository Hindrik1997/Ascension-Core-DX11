#include "D3D11PixelShader.h"

D3D11PixelShader::D3D11PixelShader(D3D11Renderer& renderer, wstring fileName) : ParentRenderer(renderer), FileName(fileName)
{
	D3DReadFileToBlob(FileName.c_str(), &PS_Buffer);
	if (PS_Buffer == nullptr)
		throw "Invalid pixel shader filename!";

	ParentRenderer.Device->CreatePixelShader(PS_Buffer->GetBufferPointer(), PS_Buffer->GetBufferSize(), NULL, &PS);
}


D3D11PixelShader::~D3D11PixelShader()
{
	ReleaseCOM(PS);
	ReleaseCOM(PS_Buffer);
}
