#include "D3D11GUITextureRenderer.h"
#include "D3D11RenderSystem.h"
#include "Engine.h"

Handle<EngineSystem> D3D11GUITextureRenderer::sysHandle;

D3D11GUITextureRenderer::D3D11GUITextureRenderer(Handle<GameObject> parentObject, float pos_x, float pos_y, float size_x, float size_y, wstring texName) : Component(parentObject), PositionX(pos_x), PositionY(pos_y), SizeX(size_x), SizeY(size_y)
{
}


D3D11GUITextureRenderer::~D3D11GUITextureRenderer()
{
}

void D3D11GUITextureRenderer::Set()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11RenderSystem& RSystem = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager.GetRenderSystem());
	D3D11Renderer& ParentRenderer = *RSystem.Renderer;







}

void D3D11GUITextureRenderer::Update()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11RenderSystem& RSystem = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager.GetRenderSystem());
	D3D11Renderer& ParentRenderer = *RSystem.Renderer;







}

void D3D11GUITextureRenderer::RevertState()
{
	Handle<EngineSystem> sysHandle = D3D11RenderSystem::GetHandle();
	D3D11RenderSystem& RSystem = *static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager.GetRenderSystem());
	D3D11Renderer& ParentRenderer = *RSystem.Renderer;







}


Handle<EngineSystem> D3D11GUITextureRenderer::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? D3D11RenderSystem::GetHandle() : sysHandle;
}

//Template implementations
template<typename... ResetArgs>
Handle<Component> D3D11GUITextureRenderer::AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments)
{
	return static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetD3D11GUITextureRenderer(parentObject, arguments...);
}

template<typename ...ResetArgs>
void D3D11GUITextureRenderer::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{
	static_cast<D3D11RenderSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemoveD3D11GUITextureRenderer(cHandle, arguments...);
}

//Explicit instantiations
template Handle<Component> D3D11GUITextureRenderer::AddComponent(Handle<GameObject> parentObject, float x, float y, float size_x, float size_y, wstring texName);
template void D3D11GUITextureRenderer::RemoveComponent(ComponentHandle cHandle);

D3D11RenderSystem& D3D11GUITextureRenderer::ConvertToParentSystemType(EngineSystem & system)
{
	return static_cast<D3D11RenderSystem&>(system);
}