#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"
#include <iostream>
#include "DirectionalLight.h"

D3D11RenderSystem::D3D11RenderSystem(int width, int height) : MainWindow(new Win32Window<D3D11Renderer>(width, height)), Renderer(new D3D11Renderer(*MainWindow))
{
	renderFunction = &D3D11RenderSystem::RenderForward;
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
	XMMATRIX t = XMMatrixPerspectiveFovLH(0.4f * 3.14f, static_cast<float>(MainWindow->Width) / static_cast<float>(MainWindow->Height), 0.1f, 1000.0f);

	XMStoreFloat4x4(&ProjectionMatrix, t);
	return t;
}

XMMATRIX D3D11RenderSystem::RecalculateViewMatrix()
{	
	if (CurrentMainCamera.GetCompHandle().GetIndex() == -1)
		throw "No camera found!";

	Camera& CurrentCamera = static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[CurrentMainCamera.GetSysHandle()])->cameras[CurrentMainCamera.GetCompHandle().GetIndex()];
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[CurrentCamera.ParentObject];

	XMMATRIX World = GetWorldMatrix(Parent);

	XMMATRIX View = XMMatrixInverse(&XMMatrixDeterminant(World), World);
	XMStoreFloat4x4(&ViewMatrix, View);
	return View;
}

void D3D11RenderSystem::Update(float deltaTime)
{
	float MoveSpeed = 5.0f;
	float RotateSpeed = 1.8f;
	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if (ModelRendererPool.GetStorageRef()[i].IsUsed && i == 0)
		{
			//Engine::MainInstance().ObjectsFactory[ModelRendererPool[i].ParentObject].ObjectTransform.RotateToWorldAxisY(430 * deltaTime);
		}
	}

	Camera& CurrentCamera = static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[CurrentMainCamera.GetSysHandle()])->cameras[CurrentMainCamera.GetCompHandle().GetIndex()];
	GameObject& CParent = Engine::MainInstance().ObjectsFactory[CurrentCamera.ParentObject];

	XMMATRIX WorldMatrix = D3D11RenderSystem::GetWorldMatrix(CParent);



	Transform& ct = CParent.ObjectTransform;
	Transform LocalTransformChanges;

	//Camera rotate left or right
	if (MainWindow->Input.IsKeyDown(0x45)) //E
	{
		//ct.RotateToWorldAxisZ(-1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x51)) //Q
	{
		//ct.RotateToWorldAxisZ(RotateSpeed * deltaTime);
	}

	//Camera up down
	if (MainWindow->Input.IsKeyDown(VK_UP)) //Up
	{
		ct.RotateToWorldAxisX(- 1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(VK_DOWN)) //DOWN
	{
		ct.RotateToWorldAxisX(RotateSpeed * deltaTime);
	}

	//Camera look left or right
	if (MainWindow->Input.IsKeyDown(VK_LEFT)) //S
	{
		ct.RotateToWorldAxisY(-1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(VK_RIGHT))
	{
		ct.RotateToWorldAxisY(RotateSpeed * deltaTime);
	}

	CoreSystem& cSystem = Engine::MainInstance().SystemsManager.GetCoreSystem();

	DirectionalLight& dLight = const_cast<Pool<DirectionalLight, 8>&>(cSystem.lightManager.GetDirectionalLightsList())[0];
	PointLight& pLight = const_cast<PLPool&>(cSystem.lightManager.GetPointLightsList())[0];
	Transform t2;


	float intensity = 0.0f;
	Transform t;
	Vector3f v = dLight.GetDirection();;
	t.Rotation = Quaternion(v.x, v.y, v.z, 0.0f);
	
	if (MainWindow->Input.IsKeyDown(0x31)) // x-left
	{
		t.RotateToWorldAxisX(RotateSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x32)) // x-right
	{
		t.RotateToWorldAxisX(-1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x33)) // y-left
	{
		t.RotateToWorldAxisY(RotateSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x34)) // y-right
	{
		t.RotateToWorldAxisY(-1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x35)) // z-left
	{
		t.RotateToWorldAxisZ(RotateSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x36)) // z-right
	{
		t.RotateToWorldAxisZ(-1.0f * RotateSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x37))
	{
		intensity += 5.0f * deltaTime;
	}
	if (MainWindow->Input.IsKeyDown(0x38))
	{
		intensity += -5.0f * deltaTime;
	}

	dLight.SetIntensity(dLight.GetIntensity() + intensity);
	dLight.SetDirection(Vector3f(t.Rotation.x, t.Rotation.y, t.Rotation.z));


	if (MainWindow->Input.IsKeyDown(VK_SHIFT))
	{
		ct.MoveToLocalAxisY(MoveSpeed * deltaTime * -1.0f);
	}
	if (MainWindow->Input.IsKeyDown(VK_SPACE))
	{
		ct.MoveToLocalAxisY(MoveSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x41)) //A
	{
		ct.MoveToLocalAxisX(MoveSpeed * deltaTime * -1.0f);
	}
	if (MainWindow->Input.IsKeyDown(0x44)) //D
	{
		ct.MoveToLocalAxisX(MoveSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x57)) //W
	{
		ct.MoveToLocalAxisZ(MoveSpeed * deltaTime);
	}
	if (MainWindow->Input.IsKeyDown(0x53)) //S
	{
		ct.MoveToLocalAxisZ(MoveSpeed * deltaTime * -1.0f);
	}


	if (MainWindow->Input.IsKeyDown(0x49)) //I
	{
		t2.MoveToLocalAxisZ(MoveSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x4B)) //K
	{
		t2.MoveToLocalAxisZ(MoveSpeed * deltaTime * -1.0f);
	}

	if (MainWindow->Input.IsKeyDown(0x4A)) //J
	{
		t2.MoveToLocalAxisX(MoveSpeed * deltaTime);
	}

	if (MainWindow->Input.IsKeyDown(0x4C)) //L
	{
		t2.MoveToLocalAxisX(MoveSpeed * deltaTime * -1.0f);
	}

	pLight.SetPosition(pLight.GetPosition() + t2.Position);

	//mouse->SetWindow(MainWindow->hWnd);
	//mouse->SetMode(mstate.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);
}

XMMATRIX D3D11RenderSystem::GetWorldViewProjectionMatrix(GameObject& gameObject)
{
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());
	XMMATRIX Projection = RS.RecalculateProjectionMatrix();

	XMMATRIX WV = GetWorldViewMatrix(gameObject);
	return WV * Projection;
}

XMMATRIX D3D11RenderSystem::GetWorldViewMatrix(GameObject& gameObject)
{
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());

	XMMATRIX View = RS.RecalculateViewMatrix();

	XMMATRIX World = GetWorldMatrix(gameObject);

	return World * View;
}

XMMATRIX D3D11RenderSystem::GetWorldMatrix(GameObject& gameObject)
{
	Transform T = gameObject.ObjectTransform;

	XMMATRIX Scale = XMMatrixScaling(T.Scale.x, T.Scale.y, T.Scale.z);
	//XMMATRIX Rotation = XMMatrixRotationQuaternion(XMVectorSet(T.Rotation.x, T.Rotation.y, T.Rotation.z, T.Rotation.w));
	XMMATRIX Rotation = XMMatrixRotationX(T.Rotation.x) * XMMatrixRotationY(T.Rotation.y) * XMMatrixRotationZ(T.Rotation.z);
	XMMATRIX Translation = XMMatrixTranslation(gameObject.ObjectTransform.Position.x, gameObject.ObjectTransform.Position.y, gameObject.ObjectTransform.Position.z);

	return Scale * Rotation * Translation;
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

void D3D11RenderSystem::RenderForward()
{
	ClearScreenAndBackBuffers();
	int DrawCallCount = 0;

	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if (ModelRendererPool.GetStorageRef()[i].IsUsed)
		{
			ModelRendererPool[i].Render();
			Renderer->DeviceContext->DrawIndexed(static_cast<int>(ModelRendererPool[i].Model->Mesh.Indices.size()), 0, 0);
			ModelRendererPool[i].Model->RevertState(ModelRendererPool[i]);
			DrawCallCount++;
		}
	}

	for (size_t i = 0; i < GUITextureRendererPool.size(); ++i)
	{
		if (GUITextureRendererPool.GetStorageRef()[i].IsUsed)
		{
			GUITextureRendererPool[i].Set();
			GUITextureRendererPool[i].Update();
			//Renderer->DeviceContext->DrawIndexed();
			GUITextureRendererPool[i].RevertState();

			DrawCallCount++;
		}
	}
	
	Renderer->SwapChain->Present(0, 0);
}

void D3D11RenderSystem::RenderDeferred()
{
}

void D3D11RenderSystem::RenderTiledForward()
{
}

void D3D11RenderSystem::RenderTiledDeferred()
{
}

void D3D11RenderSystem::ClearScreenAndBackBuffers()
{
	//Clear depthstencil
	Renderer->DeviceContext->ClearDepthStencilView(Renderer->DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Clear background to black
	float bgColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	Renderer->DeviceContext->ClearRenderTargetView(Renderer->RenderTargetView, bgColor);
}
