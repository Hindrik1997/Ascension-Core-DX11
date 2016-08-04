//
// Created by Hindrik Stegenga on 7/23/2016.
//

#ifndef ASCENSION_CORE_D3D11MODELRENDERER_H
#define ASCENSION_CORE_D3D11MODELRENDERER_H

#include "EngineSystem.h"
#include "Component.h"
#include "ComponentHandle.h"

class D3D11ModelRenderer : public Component
{
public:
	D3D11ModelRenderer(Handle<GameObject> parentObject);
	~D3D11ModelRenderer();

	//Component stuff
public:
	static Handle<EngineSystem> GetSystemHandle();

	template<typename... ResetArgs>
	static Handle<Component> AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments);

	template<typename... ResetArgs>
	static void RemoveComponent(ComponentHandle cHandle, ResetArgs... arguments);

	inline void Reset(Handle<GameObject> parentObject);
private:
	static Handle<EngineSystem> sysHandle;

	//Methods
public:
	
};

inline void D3D11ModelRenderer::Reset(Handle<GameObject> parentObject)
{
	ParentObject = parentObject;
}

#endif