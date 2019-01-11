/*=============================================================================

                           Mystic Engine
_______________________________________________________________________________

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1.) The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2.) Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3.) This notice may not be removed or altered from any source distribution.
_______________________________________________________________________________
=============================================================================*/


#pragma once


#include "Renderer.h"
#include "material.h"
#include "mesh.h"
#include "Light.h"
#include "GameObject.h"


///      ENGINE 
/*=============================================================================================================================================================
//
//      ENGINE MODULE
//
=============================================================================================================================================================*/

/*===============================================================================================================================================================
                                                //
This handles buffers but not all:				//
												//
Scene->Groups->Mesh->Polygon->Buffers;			//
												//
												//
Scene											//
=====											//
-- Group										//
---- Mesh										//
=========										//
												//
------ Material									//
_________________								//
-------- Shader									//
------------ ?? Locations						//
-------- Lighting								//
------------ Diffuse							//
------------ Ambient							//
------------ Specular							//
-------- Surface								//
------------ Diffuse							//
------------ Ambient							//
------------ Specular							//
-------- Texture								//
-----------~ Diffuse							//
-----------~ Normals							//
-----------~ Specular							//
-----------~ Glow								//
------ Polygon									//
_________________								//
-------- UVBuffer								//
-------- VAO									//
-----------~ Indices							//
-----------~ Vertices							//
-----------~ Normals							//
-----------~ Colors								//
												//
=================================================================================================================================================================*/


//---------------------------------------------------------------------------------------------------------------------------------------------------------------


class Group : public Mesh
{
public:
	Group();
	Vec3 Position = Vec3(0.0f);
	Vec3 Rotation = Vec3(0.0f);

	std::vector<Mesh*> Objects;

	Material *Surface = NULL;

	Matrix *ProjectionMatrix = NULL;

	int ObjectCount = 0;

	void Add(Mesh *object);
	void Add(Mesh *object, Material *surface);
	void Attach(Material *surface);
	void Attach(Shader *shader);

	void Bind();
	void Unbind();
	void Update();
	void Render();
};
class Scene
{
public:
	Scene();
	Scene(Material *renderer);

	std::vector<Group> Groups;
	std::vector<Light> Lights;

	int LightCount = 0;
	int GroupCount = 0;

	Viewport Camera;
	Material *Surface;

	void Update();
	void Render();

	void AddGroup(const Group& group);
	void AddLight(const Light& light);

	void Attach(Material *renderer);
	void Attach(Shader *renderer);
	void Attach(Viewport camera);
};


////=========================================================================
////-------------------------------------------------------------------------
//   Current Default Shader Inputs, Uniforms... Attributes etc...
////=========================================================================
//
//    Matrix ProjectionMatrix;
//    Matrix ViewMatrix;
//    Matrix ModelMatrix;
//    
////-------------------------------------------------------------------------
////         VERTEX ATTRIBUTES IN
//    Vec4 VertexPosition;
//    Vec4 VertexColor;
//    Vec4 VertexNormal;
//    Vec2 TextureCoords;
//    
////-------------------------------------------------------------------------
////           MATERIAL IN + LIGHTING IN
//
//    Vec3 MaterialAmbient;
//    Vec3 MaterialDiffuse;
//    Vec3 MaterialSpecular;
//
//    Vec3 AmbientLight;
//    Vec3 DiffuseLight;
//    Vec3 SpecularLight;
//
//    Vec3 LightPosition1;
////-------------------------------------------------------------------------