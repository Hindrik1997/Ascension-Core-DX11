#pragma once
#include "Engine.h"
#include "ComponentHandle.h"


template<typename T>
T& GetComponentReference(ComponentHandle cHandle)
{
	return T::ConvertToParentSystemType(Engine::MainInstance().SystemsManager[cHandle.GetSysHandle().GetIndex()]).GetFromStorage<T>(cHandle.GetCompHandle().GetIndex());
}