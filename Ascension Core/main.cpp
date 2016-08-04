#include <iostream>
#include "Engine.h"
#include "TestSystem.h"
#include <vector>
#include "D3D11ModelRenderer.h"
#include "D3D11RenderSystem.h"
#include "Camera.h"

using namespace std;

static Engine* e = new Engine;

int main()
{
	e->SystemsManager.AddRenderSystem<D3D11RenderSystem>(1920,1080);

	e->SystemsManager.AddSystem<TestSystem>();
	vector<Handle<GameObject>> gameobjectHandles;
	vector <ComponentHandle> ComponentHandles;
	vector <ComponentHandle> ComponentHandles2;

	//D3D11VertexShader* VS = new D3D11VertexShader(*static_cast<D3D11RenderSystem*>(&e->SystemsManager.GetRenderSystem())->Renderer.get(), L"VertexShader.cso");
	//D3D11PixelShader* PS = new D3D11PixelShader(*static_cast<D3D11RenderSystem*>(&e->SystemsManager.GetRenderSystem())->Renderer.get(), L"PixelShader.cso");
	//D3D11Mesh*  Mesh = new D3D11Mesh(*static_cast<D3D11RenderSystem*>(&e->SystemsManager.GetRenderSystem())->Renderer.get(), std::vector<DWORD>{ 0, 1, 2 }, std::vector<D3D11Vertex>{ D3D11Vertex(-1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f), D3D11Vertex(0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f), D3D11Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f) });
	//D3D11Model*  Model = new D3D11Model(*VS, *PS, *Mesh);

	Handle<GameObject> a = e->ObjectsFactory.CreateGameObject();
	ComponentHandle c = e->ObjectsFactory[a.GetIndex()].AddComponent<Camera>();

	//e->CurrentScene->SceneObjectsFactory[a.GetIndex()].RemoveComponent<TestComponent>(c);
	//e->CurrentScene->SceneObjectsFactory.DeleteGameObject(a);


	for (int i = 0; i < DEFAULT_SIZE - 1; ++i)
	{
		gameobjectHandles.push_back(e->ObjectsFactory.CreateGameObject());
		ComponentHandles.push_back(e->ObjectsFactory[gameobjectHandles.back().GetIndex()].AddComponent<TestComponent>());
		ComponentHandles2.push_back(e->ObjectsFactory[gameobjectHandles.back().GetIndex()].AddComponent<D3D11ModelRenderer>());
	}

	e->GameLoop();

	for (int i = 0; i < DEFAULT_SIZE - 1; ++i)
	{
		e->ObjectsFactory[i].RemoveComponent<D3D11ModelRenderer>(ComponentHandles2[i]);
		e->ObjectsFactory[i].RemoveComponent<TestComponent>(ComponentHandles[i]);
		e->ObjectsFactory.DeleteGameObject(gameobjectHandles[i]);
	}



	std::cout << "The engine is done. Please press a key to terminate." << std::endl;
	cin.get();
    return 0;
}