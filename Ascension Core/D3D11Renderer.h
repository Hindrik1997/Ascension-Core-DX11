//
// Created by Hindrik Stegenga on 7/27/2016.
//

#ifndef ASCENSION_CORE_D3D11RENDERER_H
#define ASCENSION_CORE_D3D11RENDERER_H

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "ReleaseCOM.h"

template<typename T>
class Win32Window;
class Engine;


class D3D11Renderer
{
public:
	IDXGISwapChain* SwapChain;
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	ID3D11RenderTargetView* RenderTargetView;

	ID3D11DepthStencilView* DepthStencilView;
	ID3D11Texture2D* DepthStencilBuffer;

	const Win32Window<D3D11Renderer>& CurrentWindow;


	D3D11Renderer(Win32Window<D3D11Renderer>& window);
	~D3D11Renderer();
public:
	void Initialize();
};

#endif