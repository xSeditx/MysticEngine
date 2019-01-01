#pragma once
//==============================================================================================================================================================
// TODO: Attach the Framebuffer, RenderBuffer, PixelBuffer and the Image and Texture stuff together to work as abstracted Factory 
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//#include "Window.h"
//#include "Buffers.h"


///== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
//class RenderBuffer
//{
//public:
//	RenderBuffer() {}
//	~RenderBuffer();
//	RenderBuffer(GLuint Width, GLuint Height);
//
//	//        Shader RBShader;
//
//	GLuint ID,
//		TexCoordsID;
//
//	void Bind();
//	void Unbind();
//	void Render();
//
//	void PositionQuad(Vec3 pos);
//	void RotateQuad(Vec3 rot);
//
//private:
//	void MakeTestQuad();
//
//	GLsizei Width, Height;
//	GLsizei WindowWidth, WindowHeight;
//
//	VertexBuffer  *TestQuad;
//	IndexBuffer   *TestQuadIBO;
//
//	Vec3 Position,
//		Rotation;
//};
////_______________________________________________________________________________________________________________________________________________________________
////_______________________________________________________________________________________________________________________________________________________________
//class PBuffer
//{
//	PBuffer() {}
//	~PBuffer() {}
//	PBuffer(GLuint width, GLuint height);
//
//	GLuint width;
//	GLuint height;
//};
/////== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == ==
////_______________________________________________________________________________________________________________________________________________________________
//class FrameBuffer
//{
//public:
//
//	~FrameBuffer();
//	FrameBuffer(GLuint Width, GLuint Height);
//	FrameBuffer(RenderBuffer rendernb); // FUTURE AFTER RB CLASS IS FINISHED
//	GLuint ID;
//
//	Image ColorTexture;
//	Image DepthTexture;
//
//	void Bind();
//	void Unbind();
//	void Render();
//
//	void PositionQuad(Vec3 pos);
//	void RotateQuad(Vec3 rot);
//
//	void AttachRenderBuffer(RenderBuffer *rbuffer);
//	void AttachUVBuffer(Image *texture);
//private:
//	void MakeTestQuad();
//
//	GLsizei
//		Width,
//		Height;
//
//	GLsizei
//		WindowWidth,
//		WindowHeight;
//
//	VertexBuffer  *TestQuad;
//	IndexBuffer   *TestQuadIBO;
//
//	GLuint
//		TexCoordsID;
//
//	Vec3
//		Position,
//		Rotation;
//
//	GLubyte DrawBufferCount;
//};
////_______________________________________________________________________________________________________________________________________________________________
//
//
//
//
    //