#pragma once

#include "EngineSystem.h"
#include "Component.h"
#include "ComponentHandle.h"
#include <string>

using std::wstring;
class D3D11RenderSystem;

class D3D11GUITextureRenderer : public Component
{
public:
	D3D11GUITextureRenderer(Handle<GameObject> parentObject, float pos_x, float pos_y, float size_x, float size_y, wstring texName);
	~D3D11GUITextureRenderer();
	void Set();
	void Update();
	void RevertState();

	static Handle<EngineSystem> GetSystemHandle();

	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static D3D11RenderSystem& ConvertToParentSystemType(EngineSystem& system);
private:
	friend class D3D11RenderSystem;
	static Handle<EngineSystem> sysHandle;

	float PositionX;
	float PositionY;
	float SizeX;
	float SizeY;







};

