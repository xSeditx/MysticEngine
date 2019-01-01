#pragma once
 


#include<vector>

#include"WindowGLSDL.h"
#include"shader.h"
#include"camera.h"

#include"Buffers.h" // remove this later down the line.

#include"FrameBuffer.h"



//=========================================== DEBUG SWITCHES ==========================================================
#define _TEXTURE_DEBUG    0
#define      _UV_DEBUG    0
 //====================================================================================================================

// LEFTOVERS FROM FIXED FUNCTION, DELETE SOON AS SURE ITS NOT NEEDED
//#define VERTEX_ATTRIB     0
//#define NORMAL_ATTRIB     1
//#define TEXTURE_ATTRIB    2
//#define COLOR_ATTRIB      3
//
#define BUFFER_OFFSET(i)   ((char *)NULL + (i))
 

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
