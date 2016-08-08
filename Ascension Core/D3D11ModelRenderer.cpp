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
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11Renderer& ParentRenderer = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[sysHandle])->Renderer;

	Model->Set(*this);
	Model->Update(*this);
	ParentRenderer.DeviceContext->DrawIndexed(static_cast<int>(Model->Mesh.Indices.size()), 0, 0);
}

XMMATRIX D3D11ModelRenderer::GetWorldViewProjectionMatrix()
{
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[ParentObject];
	XMMATRIX Projection = RS.RecalculateProjectionMatrix();

	XMMATRIX WV = GetWorldViewMatrix();
	return WV * Projection;
}

XMMATRIX D3D11ModelRenderer::GetWorldViewMatrix()
{
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[ParentObject];

	XMMATRIX View = RS.RecalculateViewMatrix();

	XMMATRIX World = GetWorldMatrix();

	return World * View;
}

XMMATRIX D3D11ModelRenderer::GetWorldMatrix()
{
	D3D11RenderSystem& RS = static_cast<D3D11RenderSystem&>(Engine::MainInstance().SystemsManager.GetRenderSystem());
	GameObject& Parent = Engine::MainInstance().ObjectsFactory[ParentObject];

	XMMATRIX Scale = XMMatrixScaling(Parent.ObjectTransform.Scale.x, Parent.ObjectTransform.Scale.y, Parent.ObjectTransform.Scale.z);
	XMMATRIX Rotation = XMMatrixRotationX(XMConvertToRadians(Parent.ObjectTransform.Rotation.x)) *
						XMMatrixRotationY(XMConvertToRadians(Parent.ObjectTransform.Rotation.y)) *
						XMMatrixRotationZ(XMConvertToRadians(Parent.ObjectTransform.Rotation.z));
	XMMATRIX Translation = XMMatrixTranslation(Parent.ObjectTransform.Position.x, Parent.ObjectTransform.Position.y, Parent.ObjectTransform.Position.z);

	return Scale * Rotation * Translation;
}