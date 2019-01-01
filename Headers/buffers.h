#pragma once

#include"Window.h"
#include"texture.h"
#include"renderer.h"

using namespace glm;


struct Vertex
{
	Vec3 Position;
	Vec3 Normals;
	Vec2 Uv;
};


//================================================================================================================================================================================================ 
//   GLBuffer needs completion, This will become a Generic buffer class. Possibly typedef out the various buffer types to behave exactly how is currently setup for the multiple buffer types.	   
//================================================================================================================================================================================================ 
#ifdef __GLBUFFER_FINISHED
enum BufferType
{
	Vertex, Color, Normal, UV
};

// TODO: BIGTODO: Make this Buffer class the Default, All buffers should spawn from this eliminating Hundreds of lines as well as abiguity between the buffers. Implementation such as map buffer can be easily realized
template<typename T>
class GLBuffer
{

public:
	//GLBuffer(BufferType type, T *data, int count);

	template<typename T>
	GLBuffer::GLBuffer(BufferType type, T *data, GLsizei count)
		: // Assume Dynamic Draw as the default buffer access
		ElementCount(count),
		ID(0)
	{
		Data.resize(count);
		Data.insert(Data.begin(), count, *data);
		Stride = sizeof(T);
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(T), data, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template<typename T>
	GLBuffer::GLBuffer(GLenum access, T *data, GLsizei count)
		: // Specify default access
		ElementCount(count),
		ID(0)
	{
		Data.resize(count);
		Data.insert(Data.begin(), count, *data);
		Stride = sizeof(T);
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ARRAY_BUFFER, ID);
		glBufferData(GL_ARRAY_BUFFER, ElementCount * sizeof(T), data, access);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	//	GLBuffer::GLBuffer(Vec3 *vertexdata, GLsizei vcount)
	//		: // Pad Vec3 buffer to produce a Vec4 buffer for better alignment on the GPU
	/// Must make alterations due to templation of this function
	//		ElementCount(vcount),
	//		ID(0)
	//	{
	//		Vec4 *tempdata = new Vec4[vcount];
	//		for_loop(Index, vcount)
	//		{
	//			tempdata[Index] = Vec4(vertexdata[Index].r, vertexdata[Index].g, vertexdata[Index].b, 1.0f);
	//		}
	//		*this = GLBuffer(tempdata, vcount);
	//		delete[]tempdata;
	//	}

	GLuint ID = 0;
	GLuint ElementCount = 0;

	void Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}
	void Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, NULL);
	}

	std::vector<T> Data;

	enum AccessType
	{

	};

	void Map(AccessType accessflags);
	void MapRange(int offset, int count, AccessType accessflags);
	void Release();
	void Destroy();

	int size() const { return Data.size(); }
	GLBuffer operator = (std::vector<T> data);          // Map the whole buffer, resize if needed and make the data of the buffer equal to that of the Rvalue
	GLBuffer operator = (GLBuffer &other) { return other; }  // Same but perform a shallow copy of the buffer
	GLBuffer operator += (GLBuffer &data); // Map the buffer and add to the end of it, updating the data, and size while retaining access type and ID

	GLuint Stride;

};
typedef GLBuffer<Vec4>  Buffer;



//=========================================================================================================================================================================================================================================
//   GLBuffer needs completion, This will become a Generic buffer class. Possibly typedef out the various buffer types to behave exactly how is currently setup for the multiple buffer types.
//=========================================================================================================================================================================================================================================

																																			   
#endif





///     OpenGL BUFFER ABSTRACTIONS
/*
================================================================================================================================================================
//
//
//      BUFFERs MODULE
//
//
=================================================================================================================================================================
*/

//_______________________________________________________________________________________________________________________________________________________________
class VertexBuffer
{
public:
	VertexBuffer() {}
	~VertexBuffer();
	
	VertexBuffer(Vec3 *Vertexdata, GLsizei count);
	VertexBuffer(Vec4 *vertexdata, GLsizei vcount);

	GLuint ID;
	GLint  ElementCount;

	void Bind();
	void Unbind();

	void Lock(GLenum access);
	void Unlock();
	Vec4  *Data;
	GLfloat *Read();
	void Write(GLuint pos, GLfloat *data);
	void Rebuild();
private:

};
//_______________________________________________________________________________________________________________________________________________________________
class ColorBuffer
{
public:
	ColorBuffer() {}
	~ColorBuffer();
	ColorBuffer(Vec3 *ColorData, GLsizei count)
	{
		Vec4 *tempdata = new Vec4[count];

		for_loop(Index, count)
		{
			tempdata[Index] = Vec4(ColorData[Index].r, ColorData[Index].g, ColorData[Index].b, 1.0f);
		}
		*this = ColorBuffer(tempdata, count);
		delete[]tempdata;
	}
	ColorBuffer(Vec4 *ColorData, GLsizei count);

	GLuint ID;
	GLint  ElementCount;

public:
	void Bind();
	void Unbind();
	Vec4 *Data;
private:

};
//_______________________________________________________________________________________________________________________________________________________________
class NormalBuffer
{
public:
	NormalBuffer() {}
	~NormalBuffer();

	NormalBuffer(Vec4 *NormalData, GLsizei count);
	NormalBuffer(Vec3 *NormalData, GLsizei count);

	GLuint ID;
	GLint  ElementCount;

public:
	void Bind();
	void Unbind();
	Vec4 *Data;

private:
};
//_______________________________________________________________________________________________________________________________________________________________
class IndexBuffer
{
public:
	IndexBuffer() {}
	~IndexBuffer();
	IndexBuffer(GLuint *data, GLsizei count);

	GLuint ID;
	GLuint ElementCount;

public:
	void Bind();
	void Unbind();
private:
	GLuint *Data;
};
//_______________________________________________________________________________________________________________________________________________________________




// Poor naming and from a time i had no access to vao so i sought to simulate them. Bufferobject or just making this part of the object or mesh class might be prefered.
//_______________________________________________________________________________________________________________________________________________________________



class VAOBuffer
{
public:
	VAOBuffer();
	~VAOBuffer() {}


	GLuint BatchID = 0;
	GLuint VAO;
	bool Woven;

	int NormalsOffset;
	int UVOffset;
	int ColorsOffset;

	void Attach(VertexBuffer *vertices);
	void Attach(IndexBuffer  *indices);
	void Attach(NormalBuffer *normals);
	void Attach(UVBuffer     *textures);
	void Attach(ColorBuffer  *color);


 
	void Bind();
	void Unbind();

	struct VertexType
	{
		Vec4 Vertex;
		Vec4 Color;
		Vec4 Normals;
	};
	void Interleave();

	GLuint ElementCount() { return Indices->ElementCount; }
	
	enum BufferTypes
	{
		Vertextype, Colortype, Normalstype, UVtype, Texturetype
	};
	void Write(BufferTypes type, void *vertices, int amount);

	VertexBuffer *GetVertexBuffer() { return Vertices; }
	IndexBuffer  *GetIndexBuffer() { return Indices; }
	NormalBuffer *GetNormalBuffer() { return Normals; }
	UVBuffer     *GetUVBuffer() { return Textures; }
	ColorBuffer  *GetColorBuffer()    { return Colors;   }
private:

 	VertexBuffer *Vertices;
	IndexBuffer  *Indices;
	NormalBuffer *Normals;
	UVBuffer     *Textures;
	ColorBuffer  *Colors;
};




// 
// class NewMesh
// {
// 	NewMesh()
// 	{
// 
// 	}
// 	std::vector<Buffer> Buffers;
// 	Matrix Transform;
// };
/*

public variables:
enum	Access { ReadOnly, WriteOnly, ReadWrite }
enum	RangeAccessFlag { RangeRead, RangeWrite, RangeInvalidate, RangeInvalidateBuffer, RangeFlushExplicit, RangeUnsynchronized }
flags	RangeAccessFlags
enum	Type { VertexBuffer, IndexBuffer, PixelPackBuffer, PixelUnpackBuffer }
enum	UsagePattern { StreamDraw, StreamRead, StreamCopy, StaticDraw, ..., DynamicCopy }


QOpenGLBuffer()
QOpenGLBuffer(QOpenGLBuffer::Type type)
QOpenGLBuffer(const QOpenGLBuffer &other)~QOpenGLBuffer()

void	allocate(const void *data, int count)
void	allocate(int count)
bool	bind()
GLuint	bufferId() const
bool	create()
void	destroy()
bool	isCreated() const
void *	map(QOpenGLBuffer::Access access)
void *	mapRange(int offset, int count, QOpenGLBuffer::RangeAccessFlags access)
bool	read(int offset, void *data, int count)
void	release()
void	setUsagePattern(QOpenGLBuffer::UsagePattern value)
int	size() const

QOpenGLBuffer::Type	type() const
bool	unmap()
QOpenGLBuffer::UsagePattern	usagePattern() const

void	write(int offset, const void *data, int count)
QOpenGLBuffer &	operator=(const QOpenGLBuffer &other)

*/