#include"core.h"
// TODO: Setup the entire system so that each Scene contains a Projection matrix making is so that in order to switch between 2D and 3D would require two different Scenes. 
//       Also having it setup this way will make each Scene Rendered for things like Shadows possible as the Default shader for the Scene as well as the default Projection Matrix
//       Is used at the start of the Scene Switch. This will make it so that I do not have to constantly test for a new projection matrix, only when a new Scene is presented.

Scene::Scene()
{
	Surface = NULL;
	AddGroup(Group());
}
Scene::Scene(Material *renderer)
{
	Surface = renderer;
	Groups.push_back(Group());
}
void Scene::Update()
{
	Camera.Update(); // If this breaks remove it....
	for (auto& G : Groups)
	{
		G.Update();
	}
}


// Kind of think I should make my Scene Transform and Rotation be my Main Camera, everything would translate and rotate based off of
// The rotation and location of the initial position of the Camera in the scene. This would effectively cause the entire World/Scene to rotate around me 
// Which is essentially what a Camera is anyway only that with the Camera class I abstracted away that behavior

void Scene::Render() 
{
	if (Surface != NULL)
	{
		Surface->Bind();
	}

	Lights[0].Bind(); // TODO: Make a GameObject class of which all things such as Lights, Cameras and Objects all inheirit from. With the use of an std::Unordered map I can look up and Camera, Object or Light as simple as calling it by name.
	Camera.Update();

	for (auto& G : Groups)
	{
		G.Render();
	}
	if (Surface != NULL)
	{
		Surface->Unbind();
	}
}
void Scene::AddGroup(const Group& group)
{
	Groups.push_back(group);
	GroupCount++;
}
void Scene::AddLight(const Light& light)
{
	Lights.push_back(light);
	LightCount++;
}
void Scene::Attach(Material *surf)
{
	Surface = surf;
}
void Scene::Attach(Viewport camera)
{
	Camera = camera;
}
void Scene::Attach(Shader *renderer)
{
	if (Surface == NULL)
	{
		Surface = new Material();
	}
	Surface->Attach(renderer);
}

Group::Group()
{
	Surface = NULL;
}
void Group::Add(Mesh *object)
{
	Objects.push_back(object);
	ObjectCount++;
}
void Group::Add(Mesh* object, Material *surface)
{
	object->Add(surface);
	Objects.push_back(object);
	ObjectCount++;
}


void Group::Attach(Material *surface)
{
	Surface = surface;
}
void Group::Attach(Shader *shader)
{
	if (Surface == NULL)
	{
		Surface = new Material();
	}
	Surface->Attach(shader);
}

void Group::Bind()
{

	if (ProjectionMatrix != NULL)
	{
		Viewport::Camera->PushProjectionMatrix();
		Viewport::Camera->Set_ProjectionMatrix(*ProjectionMatrix);
	}
	Viewport::Camera->PushViewMatrix();
	Viewport::Camera->RotateX(Rotation.x);
	Viewport::Camera->RotateY(Rotation.y);
	Viewport::Camera->Translate(Position);

	if (Surface != NULL)
	{
		Surface->Bind();
	}
}
void Group::Unbind()
{
	if (Surface != NULL)
	{
		Surface->Unbind();
	}
	if (ProjectionMatrix != NULL)
	{
		Viewport::Camera->PopProjectionMatrix();
    }
	Viewport::Camera->PopViewMatrix();
}
void Group::Update()
{
	for (auto& M : Objects)
	{
		M->Update(); // If this is called we will be updating the Object mesh twice I think....
	}
}
void Group::Render()
{
	Bind();
	for (auto& M : Objects)
	{
		M->Render();
	}
	Unbind();
}






// Mesh.cpp/h     245 Lines
// Light.cpp/h