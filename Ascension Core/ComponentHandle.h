//
// Created by Hindrik Stegenga on 7/25/2016.
//

#ifndef ASCENSION_CORE_COMPONENTHANDLE_H
#define ASCENSION_CORE_COMPONENTHANDLE_H

#include "Handle.h"

class Engine;
class Component;
class EngineSystem;

class ComponentHandle {
public:
	ComponentHandle();
    ComponentHandle(Handle<Component> componentHandle, Handle<EngineSystem> systemHandle);
private:
    Handle<Component> CompHandle;
    Handle<EngineSystem> SysHandle;
public:
	inline Handle<Component> GetCompHandle() const;
	inline Handle<EngineSystem> GetSysHandle() const;
};

inline Handle<Component> ComponentHandle::GetCompHandle() const
{
	return CompHandle;
}

inline Handle<EngineSystem> ComponentHandle::GetSysHandle() const
{
	return SysHandle;
}

#endif //ASCENSION_CORE_COMPONENTHANDLE_H
