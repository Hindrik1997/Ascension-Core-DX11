//
// Created by Hindrik Stegenga on 7/25/2016.
//

#include "ComponentHandle.h"

ComponentHandle::ComponentHandle()
{	
}

ComponentHandle::ComponentHandle(Handle<Component> componentHandle, Handle<EngineSystem> systemHandle) : CompHandle(componentHandle), SysHandle(systemHandle)
{

}