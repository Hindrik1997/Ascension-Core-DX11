//
// Created by Hindrik Stegenga on 7/27/2016.
//

#include "D3D11Renderer.h"
#include "Win32Window.h"
#include "Engine.h"
#include "GameObjectFactory.h"
#include "GameObject.h"

#define NUM_VIEWPORTS 1


D3D11Renderer::D3D11Renderer(Win32Window<D3D11Renderer>& window) : CurrentWindow(window)
{
	window.WindowRenderer = this;
	Initialize();
}


D3D11Renderer::~D3D11Renderer()
{
	ReleaseCOM(Device);
	ReleaseCOM(SwapChain);
	ReleaseCOM(DeviceContext);
	ReleaseCOM(RenderTargetView);
	ReleaseCOM(DepthStencilBuffer);
	ReleaseCOM(DepthStencilView);
}

void D3D11Renderer::Initialize()
{
	HRESULT hr;

	//Client dimensies ophalen
	RECT clientRect;
	GetClientRect(CurrentWindow.hWnd, &clientRect);
	unsigned int clientWidth = clientRect.right - clientRect.left;
	unsigned int clientHeight = clientRect.bottom - clientRect.top;

	//Bufferdescription
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = clientWidth;
	bufferDesc.Height = clientHeight;
	bufferDesc.RefreshRate = { 0 };
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	//SwapChain description
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = CurrentWindow.hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

#ifdef _DEBUG
#define D3DDEVFLAG D3D11_CREATE_DEVICE_DEBUG
#else
#define D3DDEVFLAG NULL
#endif

	hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE, NULL, D3DDEVFLAG, NULL, NULL, D3D11_SDK_VERSION, &swapChainDesc, &SwapChain, &Device, NULL, &DeviceContext);
	CheckFail(hr, L"Device and Swapchain creation failed.");

	ID3D11Texture2D* BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
	CheckFail(hr, L"Getting the backbuffer failed.");

	hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RenderTargetView);
	CheckFail(hr, L"Creating the render target view failed.");
	BackBuffer->Release();

	//DepthStencil
	D3D11_TEXTURE2D_DESC depthStencilDesc;

	depthStencilDesc.Width = clientWidth;
	depthStencilDesc.Height = clientHeight;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; 
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;

	hr = Device->CreateTexture2D(&depthStencilDesc, NULL, &DepthStencilBuffer);
	CheckFail(hr, L"Creating the depth stencil failed.");
	hr = Device->CreateDepthStencilView(DepthStencilBuffer, NULL, &DepthStencilView);
	CheckFail(hr, L"Creating the depth stencil view failed.");
	DeviceContext->OMSetRenderTargets(NUM_VIEWPORTS, &RenderTargetView, DepthStencilView);
	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(viewport));

	viewport.MaxDepth = 1.0f;
	viewport.MinDepth = 0.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(CurrentWindow.Width);
	viewport.Height = static_cast<float>(CurrentWindow.Height);

	DeviceContext->RSSetViewports(1, &viewport);
}
