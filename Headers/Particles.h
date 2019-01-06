#pragma once


#include"Effects.h"

// TODO: So much to do here. Basically need to fully implement a particle system. Something I have done 100 times before.


/*=======================================================================================================================================================================================================

                                                        PARTICLE SYSTEM

=========================================================================================================================================================================================================

API: We have our Particle System, This can do multiple things, perhaps have some static elements. Child of that we have ourselves the Emitter.
The Emitter is the main base class which our various rendering and managing classes derive from. If we wish to have a typical Particle system we will prob
set the color however if we wish to have images we chose the Billboard class etc etc....


Object
---- Effect
----~---- Particle System
----~----~---- Emitter
----~----~----~---- BillBoard
----~----~----~---- FlowField
----~----~----~---- TwoDEmitter
----~----~----~---- ThreeDEmitter


=========================================================================================================================================================================================================

=======================================================================================================================================================================================================*/


//TODO:  When A Particle Dies place it directly behind the Camera in Vec3(0,0,-1) in Camera Space or possibly place them in Max Distance.

#include"Renderer.h"
class ParticleSystem : public Effect
{
public:
	ParticleSystem::ParticleSystem();
 
	virtual void Bind();     // Virtual shit for implimentation in the Children
	virtual void Unbind();	 // Virtual shit for implimentation in the Children
	virtual void Update();	 // Virtual shit for implimentation in the Children
	virtual void Render();	 // Virtual shit for implimentation in the Children
					
	GLuint ID;                  // Buffer ID for containing the Vertices for the Buffer.
	std::vector<Vec3> System;  // The Positions of Each Particle in the form of Vec3. 

	int size() { return NumberOfParticles; } // Get the Current Amount of Particles in the system
	
	void SetCount(int count) { NumberOfParticles = count; }
	float Angle;
protected:
 
	VertexArrayObject *VAO;
	VertexBufferObject<Vec3> *Points;
	int NumberOfParticles = 0;
};


class Emitter : public ParticleSystem
{
public:
	Emitter::Emitter();
	Emitter::Emitter(Vec3 position, int count);
	void Bind();
	void Unbind();
	void Update();
	void Render();

};

class FlowFieldParticleSystem : public Emitter
{
public:
	FlowFieldParticleSystem();

	void Bind();
	void Unbind();
	void Update();
	void Render();

};


class BillboardParticleSystem : public Emitter
{
public:
	BillboardParticleSystem();

	void Bind();
	void Unbind();
	void Update();
	void Render();

};
