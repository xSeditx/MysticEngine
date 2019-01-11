#pragma once

/*========================================================================================================================================================================================

WE IMPLIMENT THE API AS SUCH. 

Make your Object via the appropriate object type,

Sprite generally for HUD or Sprites since it produces a renderable Quad containing a Texture Material whos UV coords can be adjusted for various animation effects.

Mesh is generally for 3D objects, Primatives are avalible for creation and are derived from the Mesh class as well as an OBJ loader( currently not working ).


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------

   USE: 
_________

Create your object:
___________________
____| Create Primative
____| Load Mesh OBJ file

Set its Position:
________________
____| void Set_Position(Vec3 pos)

Set its Rotation:  ( generally in part the job of the Ctor of the Object type if its a Primative Object ) 
_________________________________
____| void Set_Rotation(Vec3 rot)

Set its Scale: (normally just 1.0f but other values are acceptable yet may lead to problems and one should be cautious )
_____________
____| void Set_Scale(Vec3 scale)

Or.....

Set full Transform if Desired:
_____________________________
____| void Set_Transform(Matrix mat)

Add a Material to the object using...
_____________________________________
____| Add(Material *) method;

Add a Vertices and Attributes:
_____________________________
____| Add(VAOBuffer *vao) 

if needed For Added Flexibility in future use. 
Allows for the creation of a blank object which can be built later.
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------


void Set_VertexCount(GLuint Vcount)

The Following Methods of the Object class are pure Virtual and are implemented in the Appropriate Derived class type

void Bind() override;
---- Binds all your Buffers Via a VAOBuffer Bind which handles all the binding of any Buffers and VAOs it has. 
---- It also binds any Materials the Object contains and sets up and Uniforms and Texture Samplers the Shaders will need

void Unbind() override;
---- Reverses the process of the Above clearing OpenGLs state for the various stuff

void Render() override;
---- Handles the Bind() function described above...
---- Performs the Drawcall for the Object rendering it to the screen or currently active Framebuffer

void Update() override;
---- Updates any Transforms or Uniforms that will need to be bound using bind. This allows for seperation of the Rendering from the Physics if Implemented properly.

========================================================================================================================================================================================*/

#include"GameObject.h"
#include"Window.h"
#include"Renderer.h"
#include"Material.h"
//#include"Object.h"


class Mesh : public GameObject
{
public:
	Mesh();

	void Bind() override;
	void Unbind() override;
	void Render() override;
	void Update() override;


	Material Get_Surface() { return *Surface; }

	int Get_ID() { return ID; } // TODO: This will prob become part of the GameObject class, perhaps part of the Asset class when fully implemented

	inline void Mesh::Add(VertexArrayObject *vao) { VAO = vao; }
	inline void Mesh::Add(Material *surface) { Surface = surface; }


	void Mesh::LoadOBJ(char *file); // TODO: Might make this a static and return a pointer to the created object // WARNING: I do not like this and the SOB does not even work yet I don't think
protected:

	VertexArrayObject *VAO;
	Material
		*Surface;
};


/*
GameObject
---- Empty
---- 2D
---- 3D
---- Sprite
---- Effect
---- Light
---- Audio
---- Video
---- Camera

*/