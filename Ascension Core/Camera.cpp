#include "Camera.h"
#include "GameObject.h"
#include "GameObjectFactory.h"
#include "Engine.h"
#include "CoreSystem.h"

Handle<EngineSystem> Camera::sysHandle;

Camera::Camera(Handle<GameObject> parentObject) : Component(parentObject)
{
	UpVector = Vector3f(0.0f, 1.0f, 0.0f);
	LookAtVector = Vector3f();
	Engine::MainInstance().ObjectsFactory[ParentObject].ObjectTransform.Position.z = -0.5f;
}

Camera::~Camera()
{
}

Vector3f Camera::GetCamPosition()
{
	return Engine::MainInstance().ObjectsFactory[ParentObject].ObjectTransform.Position;
}

Handle<EngineSystem> Camera::GetSystemHandle()
{
	return (sysHandle.GetIndex() == -1) ? CoreSystem::GetHandle() : sysHandle;
}


//template implementations
template<typename... ResetArgs>
Handle<Component> Camera::AddComponent(Handle<GameObject> parentObject, ResetArgs... arguments)
{
	return static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->GetCamera(parentObject, arguments...);
}

template<typename ...ResetArgs>
void Camera::RemoveComponent(ComponentHandle cHandle, ResetArgs ...arguments)
{
	static_cast<CoreSystem*>(&Engine::MainInstance().SystemsManager[GetSystemHandle().GetIndex()])->RemoveCamera(cHandle, arguments...);
}

//explicit instantiations
template Handle<Component> Camera::AddComponent(Handle<GameObject> parentObject);
template void Camera::RemoveComponent(ComponentHandle cHandle);