#include "D3D11RenderSystem.h"
#include "Engine.h"
#include "CoreSystem.h"
#include <iostream>

unique_ptr<Mouse> mouse = std::make_unique<Mouse>();
unique_ptr<Keyboard> keyboard = std::make_unique<Keyboard>();

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
	XMMATRIX t = XMMatrixPerspectiveFovLH(0.4f * 3.14f, static_cast<float>(MainWindow->Width) / static_cast<float>(MainWindow->Height), 1.0f, 1000.0f);

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

	/*
	Transform CT = Parent.ObjectTransform;
	Transform LCT = CurrentCamera.ChangeSinceLastFrame;
	
	XMVECTOR DefaultForward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR DefaultRight = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR DefaultUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(XMConvertToRadians(CT.Rotation.x), XMConvertToRadians(CT.Rotation.y), XMConvertToRadians(CT.Rotation.z));
	XMVECTOR camTarget = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	camTarget = XMVector3Normalize(camTarget);
	
	XMVECTOR camRight = XMVector3TransformCoord(DefaultRight, camRotationMatrix);
	XMVECTOR camForward = XMVector3TransformCoord(DefaultForward, camRotationMatrix);
	XMVECTOR camUp = XMVector3TransformCoord(DefaultUp, camRotationMatrix);

	XMVECTOR camPosition = XMVectorSet(CT.Position.x, CT.Position.y, CT.Position.z, 0.0f);

	camPosition += LCT.Position.x * camRight;
	camPosition += LCT.Position.y * camUp;
	camPosition += LCT.Position.z * camForward;

	XMFLOAT3 cp;
	XMStoreFloat3(&cp, camPosition);

	CurrentCamera.ChangeSinceLastFrame = Transform();
	CurrentCamera.ChangeSinceLastFrame.Scale = Vector3f();

	Parent.ObjectTransform.Position = Vector3f(cp.x, cp.y, cp.z);
	camTarget = camPosition + camTarget;

	XMMATRIX View = XMMatrixLookAtLH(camPosition, camTarget,camUp);
	XMStoreFloat4x4(&ViewMatrix, View);
	return View;
	
	*/
}

void D3D11RenderSystem::Update(float deltaTime)
{
	//Nothing to happen here yet...

	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if (ModelRendererPool.GetStorageRef()[i].IsUsed && i == 0)
		{
			//Engine::MainInstance().ObjectsFactory[ModelRendererPool[i].ParentObject].ObjectTransform.Rotation.y += 0.05f;
		}
	}

	Camera& CurrentCamera = static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[CurrentMainCamera.GetSysHandle()])->cameras[CurrentMainCamera.GetCompHandle().GetIndex()];
	GameObject& CParent = Engine::MainInstance().ObjectsFactory[CurrentCamera.ParentObject];

	XMMATRIX WorldMatrix = D3D11RenderSystem::GetWorldMatrix(CParent);

	float MoveSpeed = 5.0f;
	float RotateSpeed = 1.8f;

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

	auto mstate = mouse->GetState();

	if (mstate.positionMode == Mouse::MODE_RELATIVE)
	{
		Vector3f v = Vector3f(float(mstate.x), float(mstate.y), 0.f);

		if (v.x != 0.0f)
		{
			if (v.x > 0.0f)
				ct.RotateToWorldAxisY(RotateSpeed * deltaTime * 3.0f);
			else
				ct.RotateToWorldAxisY(-1.0f * RotateSpeed * deltaTime * 3.0f);
		}

		if (v.y != 0.0f)
		{
			if (v.y > 0.0f)
				ct.RotateToWorldAxisX(RotateSpeed * deltaTime * 3.0f);
			else
				ct.RotateToWorldAxisX(RotateSpeed * deltaTime * -1.0f * 3.0f);
		}

	}

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

	mouse->SetWindow(MainWindow->hWnd);
	mouse->SetMode(mstate.leftButton ? Mouse::MODE_RELATIVE : Mouse::MODE_ABSOLUTE);
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

	for (size_t i = 0; i < ModelRendererPool.size(); ++i)
	{
		if (ModelRendererPool.GetStorageRef()[i].IsUsed)
		{
			ModelRendererPool[i].Render();
			Renderer->DeviceContext->DrawIndexed(static_cast<int>(ModelRendererPool[i].Model->Mesh.Indices.size()), 0, 0);
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
