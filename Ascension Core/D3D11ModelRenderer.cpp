#include "D3D11ModelRenderer.h"
#include "D3D11RenderSystem.h"
#include "Engine.h"

Handle<EngineSystem> D3D11ModelRenderer::sysHandle;

D3D11ModelRenderer::D3D11ModelRenderer(Handle<GameObject> parentObject) : Component(parentObject)
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
template Handle<Component> D3D11ModelRenderer::AddComponent(Handle<GameObject> parentObject);
template void D3D11ModelRenderer::RemoveComponent(ComponentHandle cHandle);