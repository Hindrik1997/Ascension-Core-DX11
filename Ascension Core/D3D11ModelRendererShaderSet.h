#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "ReleaseCOM.h"
#include "D3D11PSBase.h"
#include "D3D11VSBase.h"


class D3D11ModelRenderer;

class D3D11ModelRendererShaderSet
{
public:
	D3D11ModelRendererShaderSet();

	virtual void Set(D3D11ModelRenderer& renderer) = 0;
	virtual void Update(D3D11ModelRenderer& renderer) = 0;
	virtual void RevertState(D3D11ModelRenderer& renderer) = 0;

	virtual ~D3D11ModelRendererShaderSet() = 0;
};

