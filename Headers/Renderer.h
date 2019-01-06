#pragma once
 


#include<vector>

#include"Window.h"
#include "Shader.h"
#include "Camera.h"
#include "FrameBuffer.h"
#include"Texture.h"
 


//=========================================== DEBUG SWITCHES ==========================================================
#define _TEXTURE_DEBUG    0
#define      _UV_DEBUG    0
 //====================================================================================================================

#define BUFFER_OFFSET(i)   ((char *)NULL + (i))
 

struct Vertex
{
	Vec3 Position;
	Vec3 Normals;
	Vec2 Uv;
};

//#define __GLBUFFER_FINISHED
enum BufferTypes
{
	VERTEX,
	COLOR,
	NORMAL,
	UVCOORD,
	TEXTURE,
	INDICE
};


//================================================================================================================================================================================================ 
//   GLBuffer needs completion, This will become a Generic buffer class. Possibly typedef out the various buffer types to behave exactly how is currently setup for the multiple buffer types.	   
//================================================================================================================================================================================================ 
// TODO: BIGTODO: Make this Buffer class the Default, All buffers should spawn from this eliminating Hundreds of lines as well as abiguity between the buffers. Implementation such as map buffer can be easily realized

class Attribute
{
public:
	Attribute() {}
	Attribute(BufferTypes t)
	{
		AttributeType = t;
	}
	BufferTypes AttributeType;
};

template<class T>
class VertexBufferObject : public Attribute
{
public:
	VertexBufferObject() {}
	VertexBufferObject(T *data, GLsizei count)
		: // Assume Dynamic Draw as the default buffer access
		ElementCount(count),
		ID(0)
	{
		Data.resize(count);
		Data.insert(Data.begin(), count, *data);
		Stride = sizeof(T);
		_GL(glGenBuffers(1, &ID));
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(T), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	VertexBufferObject(GLenum access, T *data, GLsizei count)
		: // Specify default access
		ElementCount(count),
		ID(0)
	{
		Data.resize(count);
		Data.insert(Data.begin(), count, *data);
		Stride = sizeof(T);
		_GL(glGenBuffers(1, &ID));
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(T), data, access);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	GLuint ID = 0;
	GLuint ElementCount = 0;
	GLuint Stride;

	void Bind()
	{
		_GL(glBindBuffer(GL_ARRAY_BUFFER, ID));
	}
	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	void Map(GLenum accessflags)
	{
		glMapBuffer(GL_ARRAY_BUFFER, accessflags);
	}
	void MapRange(int offset, int count, GLenum accessflags)
	{

	}
	void Release()
	{

	}
	void Destroy()
	{
		glDeleteBuffer(ID);
	}

	VertexBufferObject operator = (std::vector<T> data);          // Map the whole buffer, resize if needed and make the data of the buffer equal to that of the Rvalue
	VertexBufferObject operator = (VertexBufferObject &other) { return other; }  // Same but perform a shallow copy of the buffer
	VertexBufferObject operator += (VertexBufferObject &data); // Map the buffer and add to the end of it, updating the data, and size while retaining access type and ID

	int size() const { return Data.size(); }

protected:
	std::vector<T> Data;
};

class VertexArrayObject
{
public:
	VertexArrayObject()
	{
		glGenVertexArrays(1, &VAO);
	}
	void Bind()
	{
		glBindVertexArray(VAO);
	}
	void Unbind()
	{
		glBindVertexArray(0);
	}

	template<typename T>
	void Attach(BufferTypes bufferT, VertexBufferObject<T> *buffer)
	{
		Bind();

		GLint
			Amount = 0,
			Attrib = 0;

		switch (bufferT)
		{
		case BufferTypes::VERTEX:
			Amount = 3;
			buffer->AttributeType = VERTEX;

			glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
			Attrib = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexPosition");
			Buffers.push_back(*buffer);
			break;

		case BufferTypes::COLOR:
			Amount = 4;
			buffer->AttributeType = COLOR;

			glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
			Attrib = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexColor");
			Buffers.push_back(*buffer);
			break;

		case BufferTypes::NORMAL:
			Amount = 3;
			buffer->AttributeType = NORMAL;

			glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
			Attrib = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "VertexNormal");
			Buffers.push_back(*buffer);
			break;

		case BufferTypes::UVCOORD:
			Amount = 2;
			buffer->AttributeType = UVCOORD;

			glBindBuffer(GL_ARRAY_BUFFER, buffer->ID);
			Attrib = glGetAttribLocation(Shader::GetActiveShader()->GetName(), "TextureCoords");
			Buffers.push_back(*buffer);
			break;
		case BufferTypes::INDICE:
			ElementCount = buffer->ElementCount;
			buffer->AttributeType = INDICE;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer->ID);
			Buffers.push_back(*buffer);
			return; // If its Indices we have done what we need to already in binding the VAO than the IndexBuffer. Exit before attempts at Enabling Attributes take place.
			break;
		}
		glEnableVertexAttribArray(Attrib);
		glVertexAttribPointer(Attrib, Amount, GL_FLOAT, GL_FALSE, 0, (char *)NULL);
	}
	GLuint VAO;
	int ElementCount;
	std::vector<Attribute> Buffers;
};
















/*
TODO: THIS WILL BE UPDATED TO PERFORM BATCHING OPERATIONS AS MUCH AS POSSIBLE AS THE ENGINE WILL LOG ALL DRAW CALLS AND DECIDE THE ORDERS TO PERFORM THEM IN
static class DrawCall
{
	DrawCall(int elementcount, GL_UNSIGNED_INT, nullptr);

	void Attach(VAOBuffer *buffer);	


	void Weave();
	void Render();
	void glDrawElements(GLenum mode,
		GLsizei count,
		GLenum type,
		const GLvoid * indices);

};*/



// LEFTOVERS FROM FIXED FUNCTION, DELETE SOON AS SURE ITS NOT NEEDED
//#define VERTEX_ATTRIB     0
//#define NORMAL_ATTRIB     1
//#define TEXTURE_ATTRIB    2
//#define COLOR_ATTRIB      3
//




/// look into this https://www.opengl.org/discussion_boards/showthread.php/155504-Render-to-Texture-vs-CopyTexSubImage
// CONVERT THIS NAME TO SOMETHING LIKE IMAGE SINCE IT DOES NOT MAKE A TEXTURE BUT INSTEAD LOADS AN IMAGE
// THE TEXTUREBUFFER SHOULD EITHER BECOME TEXTURE OR PROB EVEN BETTER CALLED UV_BUFFER OR SOMETHING AND HAVE 
// A TEXTURE CLASS WHICH IS ITSELF A COMBINATION OF THE IMAGE AND THE TEXTURE COORDS SO THAT THEY CAN BE LOADED
// AND UNLOADED AT THE SAME TIME OR SEPERATELY AS NEEDED.
//-------------------------------------------------------------
// ADD ALL VARIOUS BUFFERS TO A SINGLE BUFFER VERTEX, INDEX, COLOR, TEXTURE, NORMALS etc... 
// Into a single Buffer for their type, Bind each buffer than call  Draw Instances
//-----------------------
//1.	Uniform Buffer Objects
//2.	Texture Buffer Objects
//3.	Instanced_arrays_ARB
//=================================================================================================================== 
//___________________________________________________________________________________________________________________ 
//1. pbuffer extension initialization
//2. pbuffer creation
//3. pbuffer binding
//4. pbuffer destruction. 




// Obsolete but still might make a class to manage it just incase
//1. pbuffer extension initialization
//2. pbuffer creation
//3. pbuffer binding
//4. pbuffer destruction. 




//__________________________________________________________________________________________________________________________________________________
//==================================================================================================================================================
//   __forceinline void myInlineFunc() __attribute__((always_inline));

//======================================================================================================================================================================================
//                                         SHADER CLASS                                                                                                                                                   
//======================================================================================================================================================================================

// TODO: NEED A SHADER PARSER SO FRAGMENT AND VERTEX SHADER ARE THE SAME FILE
// Merge the two after ALL debugging is handled

//GLuint Shader::VertexLocation  = 0;
//GLuint Shader::ColorsLocation  = 0;
//GLuint Shader::NormalsLocation = 0;








