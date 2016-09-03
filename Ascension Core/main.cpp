#include <iostream>
#include "Engine.h"
#include "TestSystem.h"
#include <vector>
#include "D3D11ModelRenderer.h"
#include "D3D11RenderSystem.h"
#include "Camera.h"
#include "D3D11Model.h"
#include "D3D11SkyBoxShaderSet.h"
#include "D3D11StandardShaderSet.h"
#include "D3D11TexturedAmbientDiffuseShaderSet.h"
#include "CoreSystem.h"
#include <Model.h>
#include <DirectXMesh.h>
#include <WaveFrontReader.h>
#include "ProceduralMeshGeneration.h"
#include "D3D11GUITextureRenderer.h"
#include "HelperFunctions.h"

using namespace std;

static Engine* e = new Engine;

int main()
{
	Handle<EngineSystem> tRenderS = e->SystemsManager.AddRenderSystem<D3D11RenderSystem>(1920,1080);

	Handle<GameObject> a = e->ObjectsFactory.CreateGameObject();
	ComponentHandle c = e->ObjectsFactory[a.GetIndex()].AddComponent<Camera>();
	e->SystemsManager.GetRenderSystem().SetCamera(c);


	CoreSystem& cSystem = Engine::MainInstance().SystemsManager.GetCoreSystem();

	D3D11Renderer& rs = *static_cast<D3D11RenderSystem*>(&e->SystemsManager.GetRenderSystem())->Renderer.get();

	D3D11Mesh*  Meshd = new D3D11Mesh(
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

	D3D11Mesh*  Mesh2 = new D3D11Mesh(
		std::vector<DWORD>{
		// Front Face
		0, 1, 2,
			0, 2, 3,

			// Back Face
			4, 5, 6,
			4, 6, 7,

			// Top Face
			8, 9, 10,
			8, 10, 11,

			// Bottom Face
			12, 13, 14,
			12, 14, 15,

			// Left Face
			16, 17, 18,
			16, 18, 19,

			// Right Face
			20, 21, 22,
			20, 22, 23
	},
		std::vector<D3D11Vertex>{
			// Front Face
			D3D11Vertex(Vertex(-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, -1.0f, 1.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, -1.0f, -1.0f, 1.0f, 1.0f,0.0f)),
			// Back Face
			D3D11Vertex(Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, -1.0f, 1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 0.0f,0.0f)),
			// Top Face
			D3D11Vertex(Vertex(-1.0f, 1.0f, -1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f,0.0f)),
			// Bottom Face
			D3D11Vertex(Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f,0.0f)),
			// Left Face
			D3D11Vertex(Vertex(-1.0f, -1.0f, 1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, 1.0f, 1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f,0.0f)),
			// Right Face
			D3D11Vertex(Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, 1.0f, 1.0f, 1.0f, 0.0f,0.0f)),
			D3D11Vertex(Vertex(1.0f, -1.0f, 1.0f, 1.0f, 1.0f,0.0f)),
		});

	D3D11SkyBoxShaderSet shaderSet(L"Skybox.dds");
	D3D11SkyBoxShaderSet shaderSet2(L"Skybox2.dds");
	D3D11StandardShaderSet shaderSet3(L"box_texture.dds");
	//D3D11StandardShaderSet shaderSet3(L"chalet.jpg");

	//Mesh2->CalculateNormals();

	Mesh plane = ProceduralMeshGeneration::GeneratePlane(500, 500, 0.1f, 0.1f);
	Mesh plane2 = ProceduralMeshGeneration::GenerateQuad(25,25);
	//Mesh plane = ProceduralMeshGeneration::GenerateCircle(5, 5);
	//Mesh plane = ProceduralMeshGeneration::GenerateCone(5.0f, 5.0f, 1500);
	D3D11Mesh* planed = new D3D11Mesh(plane);
	D3D11Mesh* planed2 = new D3D11Mesh(plane2);
	D3D11Model* Model = new D3D11Model(shaderSet, *Meshd);
	D3D11Model* Model3= new D3D11Model(shaderSet3, *planed);
	D3D11Model* Model4 = new D3D11Model(shaderSet3, *planed2);

	Handle<GameObject> gHandle = e->ObjectsFactory.CreateGameObject();
	Handle<GameObject> gHandle2 = e->ObjectsFactory.CreateGameObject();
	

	//Handle<DirectionalLight> Dl = cSystem.AddDirectionalLight(); 
	//cSystem.lightManager.AddDirectionalLight();
	
	//cSystem.lightManager.AddPointLight();
	//Handle<PointLight> pl = cSystem.lightManager.AddPointLight();

	//PointLight& pLight = const_cast<PLPool& >(cSystem.lightManager.GetPointLightsList())[pl.GetIndex()];
	//DirectionalLight& dLight = const_cast<DLPool& >(cSystem.GetDirectionalLightsList())[Dl.GetIndex()];
	//dLight.SetColor(255, 255, 255);
	//dLight.SetDirection(Vector3f(1.0f, 1.0f, 1.0f));
	//dLight.SetIntensity(0.72f);
//	pLight.SetColor(0, 255, 0);

	//e->ObjectsFactory[gHandle].AddComponent<D3D11ModelRenderer>(Model4);
	ComponentHandle cHandle = e->ObjectsFactory[gHandle].AddComponent<D3D11ModelRenderer>(Model3);
	e->ObjectsFactory[gHandle].AddComponent<D3D11GUITextureRenderer>(0.0f, 0.0f, 0.1f, 0.1f, wstring(L"box_texture.dds"));
	GameObject& gOb = e->ObjectsFactory[gHandle];

	D3D11ModelRenderer& r = GetComponentReference<D3D11ModelRenderer>(cHandle);

	e->ObjectsFactory.at(gHandle).ObjectTransform.Position = Vector3f(0.0f, -5.0f, 0.0f);
	e->ObjectsFactory.at(a).ObjectTransform.Position = Vector3f(0.0f, 0.0f, -8.0f);

	Engine::MainInstance().ObjectsFactory[gHandle2].ObjectTransform.Scale = Vector3f(50.0f, 50.0f, 50.0f);
	ComponentHandle cHandle2 = e->ObjectsFactory[gHandle2].AddComponent<D3D11ModelRenderer>(Model);

	e->GameLoop();

	e->ObjectsFactory[gHandle].RemoveComponent<D3D11ModelRenderer>(cHandle);
	e->ObjectsFactory.DeleteGameObject(gHandle);


	delete e;
	delete Meshd;
    return 0;
}