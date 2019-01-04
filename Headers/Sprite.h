#pragma once
/*
          Mystic Sprite Engine
_______________________________________________

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

*/

///      SPRITES 
/*=============================================================================================================================================================
//
//      SPRITE MODULE
//
=============================================================================================================================================================*/

/* =============================================================================================================================================================

										   //
Scene									   //
== == =									   //
--Group									   //
---- Sprite								   //
------ Material							   //
_________________						   //
-------- Shader							   //
------------ ?? Locations				   //
-------- Lighting						   //
------------ Diffuse					   //
------------ Ambient					   //
------------ Specular					   //
-------- Surface						   //
------------ Diffuse					   //
------------ Ambient					   //
------------ Specular					   //
-------- Texture						   //
-----------~ Diffuse					   //
-----------~ Normals					   //
-----------~ Specular					   //
-----------~ Glow						   //
------ Polygon							   //
_________________						   //
-------- UVBuffer						   //
------------ Animation					   //  Set of frames Acting like a State for instance Jumping or Running
---------------- Frame					   //  UV texture Coords to select from the Sprites Image sheet
-------- VAO							   //
-----------~ Indices					   //
-----------~ Vertices					   //
-----------~ Normals					   //
-----------~ Colors                   	   //
=============================================================================================================================================================*/


class Sprite;
#include"core.h"
#include"texture.h"
#include"Material.h"
#include"Renderer.h"

#include"time.h"

struct Quad
{
	Quad() {};
	Quad(int X, int Y, int W, int H)
		: x(X), y(Y), Width(W), Height(H) {}
	int x, y;
	int Height, Width;
};
struct Frame
{
public:
	Frame() {}
	Frame(Image*img, Quad f);

	Vec2 Coords[4];
	GLuint ID;

	void Bind();
	void Unbind();
};
class Animation
{
public:
	Animation() {}
	~Animation() {}

	Animation(Image *img, Quad sourcerect, unsigned int numframes);
	Animation(Image *img, Quad srcrect, int border, GLuint numframes);

	std::vector<Frame> Frames;

	unsigned int TotalFrames;
	unsigned int CurrentFrame;

	GLint  AnimationSpeed;

	Animation operator +=(Frame newframe)
	{
		this->AddFrame(newframe);
		return *this;
	}
	Animation operator +=(Animation newstate)
	{
		for_loop(count, newstate.TotalFrames)
		{
			this->AddFrame(newstate.Frames[count]);
			this->TotalFrames++;
		}
		return *this;
	}

	bool PlayOnce;
	bool Stopped;


	void Bind();
	void Unbind();
private:
	std::vector<Frame>& AddFrame(Frame frame);
};
class Sprite : public Object
{
public:
	Sprite(char *name, Image *source, Vec2 dimensions, int numstates);
	Sprite(char *name, Image *source, Vec2 dimensions);
	int ID;

	GLuint CurrentState;
	char *Name;
	std::vector<Animation> Animations;
	GLuint NumberofStates;

	float AnimationLength;

	float Timer;
	float AnimationTimer;

	bool Moving;     // Is it currently Animating
	bool Composite;  // Is it made up of multiple sprites
// _______________________________________________________________________________________________________________________
	void SetAnimationSpeed(float speed);
	void ResetFrames();

	void Add(Animation state);
	void Add(int statenum, Animation state);
	void Set_Scale(Vec3 scale) { Scale = scale; }
public:

	void  Bind() override;
	void  Unbind() override ;
	void  Update() override ;
	void  Render() override ;
	void  Render(Vec2 pos);


	static AssetManager<Sprite> Manager;
	static int Submit(char *name, Sprite *spr);

	static Sprite *MakeFromImage(Image *img);

private:
	float Speed;
};




