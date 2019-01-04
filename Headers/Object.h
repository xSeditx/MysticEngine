#pragma once

#include"Renderer.h"
#include"Component.h"
#include"Material.h"
#include"Common.h"


class Object : public Component
{
public:
	Object::Object();

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

//	void Set_VertexCount(GLuint Vcount) { VertexCount = Vcount; }

//	GLuint Get_ElementCount() { return IndexCount; }
//	GLuint Get_VertexCount() { return VertexCount; }

	Material Get_Surface() { return *Surface; }

	int Get_ID() { return ID; } // TODO: This will prob become part of the Component class, perhaps part of the Asset class when fully implemented

//	inline void Object::Add(VAOBuffer *vao) { Polygons = vao; }
	inline void Object::Add(VertexArrayObject *vao) { VAO = vao; }

	inline void Object::Add(Material *surface) { Surface = surface; }
	void Object::LoadOBJ(char *file); // TODO: Might make this a static and return a pointer to the created object // WARNING: I do not like this and the SOB does not even work yet I don't think
//
//	char
//		*Name;
//
protected:

	int ID;

//	GLuint
//		VertexCount,
//		IndexCount;

//	VAOBuffer
//		*Polygons;

	VertexArrayObject *VAO;

	Material
		*Surface;
};

