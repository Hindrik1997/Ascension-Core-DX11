#include "D3D11ModelRenderer.h"
#include "D3D11RenderSystem.h"
#include "Engine.h"

Handle<EngineSystem> D3D11ModelRenderer::sysHandle;

D3D11ModelRenderer::D3D11ModelRenderer(Handle<GameObject> parentObject, D3D11Model* model) : Component(parentObject), Model(model)
{
}

D3D11ModelRenderer::D3D11ModelRenderer(Handle<GameObject> parentObject) : Component(parentObject), Model(nullptr)
{
}


D3D11ModelRenderer::~D3D11ModelRenderer()
{
}

Handle<EngineSystem> D3D11ModelRenderer::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? D3D11RenderSystem::GetHandle() : sysHandle;
}

//Template implementations
template<typename... ResetArgs>
Handle<Component> D3D11ModelRenderer::AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments)
{
	return static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetD3D11ModelRenderer(parentObject, arguments...);
}

template<typename ...ResetArgs>
void D3D11ModelRenderer::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{
	static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemoveD3D11ModelRenderer(cHandle, arguments...);
}

//Explicit instantiations
template Handle<Component> D3D11ModelRenderer::AddComponent(Handle<GameObject> parentObject, D3D11Model* model);
template void D3D11ModelRenderer::RemoveComponent(ComponentHandle cHandle);


void D3D11ModelRenderer::Render()
{
	Model->Set();
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[ParentObject];

	XMMATRIX View = RS.RecalculateViewMatrix();
	XMMATRIX Projection = RS.RecalculateProjectionMatrix();

	//XMMATRIX World = XMMatrixIdentity();
	

	XMMATRIX Scale = XMMatrixScaling(Parent.ObjectTransform.Scale.x, Parent.ObjectTransform.Scale.y, Parent.ObjectTransform.Scale.z);
	XMMATRIX Rotation = XMMatrixRotationX(XMConvertToRadians(Parent.ObjectTransform.Rotation.x)) * XMMatrixRotationY(XMConvertToRadians(Parent.ObjectTransform.Rotation.y)) * XMMatrixRotationZ(XMConvertToRadians(Parent.ObjectTransform.Rotation.z));
	//XMMATRIX Rotation = XMMatrixIdentity();
	XMMATRIX Translation = XMMatrixTranslation(Parent.ObjectTransform.Position.x, Parent.ObjectTransform.Position.y, Parent.ObjectTransform.Position.z);
	
	XMMATRIX World = Scale * Rotation * Translation;
	

	XMMATRIX WVP = World * View * Projection;
	XMFLOAT4X4 WVPFL;
	XMStoreFloat4x4(&WVPFL, WVP);
	Model->VertexShader.UpdateConstantBuffer(WVPFL);

	Model->Mesh.ParentRenderer.DeviceContext->DrawIndexed(static_cast<int>(Model->Mesh.Indices.size()), 0, 0);
}