#include <iostream>
#include "Engine.h"
#include "TestSystem.h"
#include <vector>
#include "D3D11ModelRenderer.h"
#include "D3D11RenderSystem.h"
#include "Camera.h"
#include "D3D11Model.h"
#include "D3D11SkyBoxShaderSet.h"



using namespace std;

static Engine* e = new Engine;

int main()
{
	Handle<EngineSystem> tRenderS = e->SystemsManager.AddRenderSystem<D3D11RenderSystem>(1920,1080);

	Handle<GameObject> a = e->ObjectsFactory.CreateGameObject();
	ComponentHandle c = e->ObjectsFactory[a.GetIndex()].AddComponent<Camera>();
	e->SystemsManager.GetRenderSystem().SetCamera(c);


	D3D11Renderer& rs = *static_cast<D3D11RenderSystem*>(&e->SystemsManager.GetRenderSystem())->Renderer.get();

	D3D11VertexShaderBase* VS = new D3D11VertexShaderBase(L"VertexShader.cso");
	D3D11PixelShaderBase* PS = new D3D11PixelShaderBase(L"PixelShader.cso");
	D3D11Mesh*  Mesh = new D3D11Mesh(
		std::vector<DWORD>{     
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7 
		},	
		std::vector<D3D11Vertex>{ 
			D3D11Vertex(Vertex(-1.0f, -1.0f, -1.0f)),
			D3D11Vertex(Vertex(-1.0f, +1.0f, -1.0f)),
			D3D11Vertex(Vertex(+1.0f, +1.0f, -1.0f)),
			D3D11Vertex(Vertex(+1.0f, -1.0f, -1.0f)),
			D3D11Vertex(Vertex(-1.0f, -1.0f, +1.0f)),
			D3D11Vertex(Vertex(-1.0f, +1.0f, +1.0f)),
			D3D11Vertex(Vertex(+1.0f, +1.0f, +1.0f)),
			D3D11Vertex(Vertex(+1.0f, -1.0f, +1.0f)),
	});

	D3D11SkyBoxShaderSet shaderset;

	D3D11Model* Model = new D3D11Model(shaderset, *Mesh);


	Handle<GameObject> gHandle = e->ObjectsFactory.CreateGameObject();

	Engine::MainInstance().ObjectsFactory[gHandle].ObjectTransform.Scale = Vector3f(999.0f,999.0f,999.0f);
	ComponentHandle cHandle = e->ObjectsFactory[gHandle].AddComponent<D3D11ModelRenderer>(Model);

	e->ObjectsFactory.at(a).ObjectTransform.Position = Vector3f(0.0f, 0.0f, -8.0f);
	e->ObjectsFactory.at(gHandle).ObjectTransform.Rotation = Vector3f(0.0f, 45.0f, 0.0f);
	e->GameLoop();

	e->ObjectsFactory[gHandle].RemoveComponent<D3D11ModelRenderer>(cHandle);
	e->ObjectsFactory.DeleteGameObject(gHandle);


	delete e;
	delete PS;
	delete VS;
	delete Mesh;
    return 0;
}