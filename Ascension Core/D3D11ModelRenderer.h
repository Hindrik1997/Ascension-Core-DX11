//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11MODELRENDERER_H
#define ASCENSION_CORE_D3D11MODELRENDERER_H

#include "EngineSystem.h"
#include "Component.h"
#include "ComponentHandle.h"
#include "D3D11Model.h"

class D3D11RenderSystem;

class D3D11ModelRenderer : public Component
{
public:
	D3D11ModelRenderer(Handle<GameObject> parentObject, D3D11Model* model);
	D3D11ModelRenderer(Handle<GameObject> parentObject);
	~D3D11ModelRenderer();

	//Component stuff
public:
	static Handle<EngineSystem> GetSystemHandle();

	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	static D3D11RenderSystem& ConvertToParentSystemType(EngineSystem& system);
private:
	friend class D3D11RenderSystem;
	static Handle<EngineSystem> sysHandle;
	D3D11Model* Model;
	//Methods
public:
	void Render();
	XMMATRIX GetWorldViewProjectionMatrix();
	XMMATRIX GetWorldViewMatrix();
	XMMATRIX GetWorldMatrix();
};
#endif
