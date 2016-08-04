#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"
#include <iostream>

D3D11RenderSystem::D3D11RenderSystem(int width, int height) : MainWindow(new Win32Window<D3D11Renderer>(width, height)), Renderer(new D3D11Renderer(*MainWindow))
{
	MainWindow->WindowRenderer = Renderer.get();

#ifdef _DEBUG
	Renderer.get()->Device->QueryInterface(__uuidof(ID3D11Debug), (void**)&debug);
#endif


}

D3D11RenderSystem::~D3D11RenderSystem()
{

#ifdef _DEBUG
	std::cout << "[START] DIRECTX MEMORY LEAK RAPORT:" << std::endl;
	debug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	ReleaseCOM(debug);
	std::cout << "[END] DIRECTX MEMORY LEAK RAPORT" << std::endl;
#endif
}

XMMATRIX D3D11RenderSystem::RecalculateProjectionMatrix()
{
	if (MainWindow == nullptr)
		throw "No window attached??!!???";
	XMMATRIX t = XMMatrixPerspectiveFovLH(0.4f * 3.14f, static_cast<float>(MainWindow->Width) / static_cast<float>(MainWindow->Height), 1.0f, 1000.0f);

	XMStoreFloat4x4(&ProjectionMatrix, t);
	return t;
}

XMMATRIX D3D11RenderSystem::RecalculateViewMatrix()
{	
	if (CurrentMainCamera.GetCompHandle().GetIndex() == -1)
		throw "No camera found!";

	Camera& CurrentCamera = static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[CurrentMainCamera.GetSysHandle()])->cameras[CurrentMainCamera.GetCompHandle().GetIndex()];

	XMVECTOR CamPosV = XMVectorSet(CurrentCamera.GetCamPosition().x, CurrentCamera.GetCamPosition().y, CurrentCamera.GetCamPosition().z, 0.0f);
	XMVECTOR CamLookAtV = XMVectorSet(CurrentCamera.GetLookAtVector().x, CurrentCamera.GetLookAtVector().y, CurrentCamera.GetLookAtVector().z, 0.0f);
	XMVECTOR CamUpV = XMVectorSet(CurrentCamera.GetUpVector().x, CurrentCamera.GetUpVector().y, CurrentCamera.GetUpVector().z, 0.0f);

	XMMATRIX Temp = XMMatrixLookAtLH(CamPosV, CamLookAtV, CamUpV);
	XMStoreFloat4x4(&ViewMatrix,Temp);
	return Temp;
}

void D3D11RenderSystem::Update(float deltaTime)
{
	//Nothing to happen here yet...

	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if (ModelRendererPool.GetStorageRef()[i].IsUsed)
		{
			Engine::MainInstance().ObjectsFactory[ModelRendererPool[i].ParentObject].ObjectTransform.Rotation.y += 0.05f;
		}
	}

}

Handle<EngineSystem> D3D11RenderSystem::GetHandle()
{
	for (size_t i = 0; i < Engine::MainInstance().SystemsManager.GetSystems().size(); ++i)
	{
		if (typeid(D3D11RenderSystem) == typeid(*(Engine::MainInstance().SystemsManager.GetSystems())[i]))
		{
			return Handle<EngineSystem>(i);
		}
	}
	throw "System not found in engine!";
}

void D3D11RenderSystem::LoadVertexShader(wstring name)
{
}

void D3D11RenderSystem::LoadPixelShader(wstring name)
{
}

void D3D11RenderSystem::LoadMesh(wstring name)
{
}

void D3D11RenderSystem::UnLoadVertexShader(wstring name)
{
}

void D3D11RenderSystem::UnLoadPixelShader(wstring name)
{
}

void D3D11RenderSystem::UnLoadMesh(wstring name)
{
}