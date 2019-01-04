#pragma once
//include"window.h"
#include"Common.h"

class Image
{
public:
	Image();
	~Image();
	Image(char* name, const char *filename);
	Image(char* name, GLenum param, const char *filename);

	GLuint ID;

	GLuint
		Width,
		Height,
		ImageSize;

	GLubyte* LoadBMP(const char *filename); // Possibly make this Static and return an entire Image object

	char *Name;


	inline void SetSize(float width, float height);

	void GenColorTexture(float width, float height);
	void GenDepthTexture(float width, float height);
	void Bind();
	void Unbind();

	void VerticalFlip();// void *image, int w, int h, int bytes_per_pixel)

	GLint MaxTextureSize();
	Vec2 Get_Size() { return Vec2(Width, Height); }
	static AssetManager<Image> Manager;
private:

	GLubyte header[54];
	GLuint  dataPos;

	GLubyte *Data;
	GLint MaxTexture;
};


//_______________________________________________________________________________________________________________________________________________________________
class UVBuffer
{
public:
	UVBuffer(){}
	~UVBuffer();
	UVBuffer(Vec2 *UVdata, GLsizei count); //UVBuffer(Image &img, Vec2 *UVdata, GLsizei count);

	GLuint ID;
	GLuint ElementCount;

	Vec2    *Data;
public:

	void Bind();
	void Unbind();
};
//_______________________________________________________________________________________________________________________________________________________________
class TextureBuffer
{
	TextureBuffer();
	~TextureBuffer();


	Image    *Texture;
	UVBuffer *TextureCoords;

	void Bind();
	void Unbind();
};
//_______________________________________________________________________________________________________________________________________________________________

