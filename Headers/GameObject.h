#pragma once

#include"Window.h"
#include"Common.h"
/*

GameObject
=========

Children:
---- Physics              // TODO: All of this class
----~---- RigidBody
----~---- SoftBody
----~---- Material
----~----~---- Fluid
----~----~---- Cloth
----~----~---- Spring
----~----~---- Rope
---- Camera               // COMMENT: Currently there is only a single Camera with different Projection matrix however it might be wise to Subclass for the two types as various optimizations could be performed
----~---- Perspective
----~---- Orthographic
---- Light


---- Objects // TODO: NEW NAME Since we changed componenet to GameObject???
----~---- TileMap         // TODO: Implement
----~---- Mesh
----~----~---- Cube
----~----~---- Sphere
----~----~---- Block
----~----~---- Plane
----~----~---- Torus      // Errors
----~----~---- Diamond
----~---- Sprite   
----~---- Terrain         //  TODO: Create and have various Terrain Generators and types such as Noise, Perlin Noise, SinWave etc...
---- Effect               //  TODO: All of these Effects
----~---- Particle System
----~---- Lens Flair
----~---- Trail Render
----~---- Halo
----~---- Water
*/


// NOTE:: MIGHT VERY WELL ELIMINATE THIS IN FAVOR OF THE OBJECT CLASS
class GameObject
{
public:
	GameObject::GameObject();

	void Set_Scale(Vec3 scale) { Scale = scale; }
	void Set_Rotation(Vec3 rot) { Rotation = rot; }
	void Set_Position(Vec3 pos) { Position = pos; }
	void Set_Transform(Matrix mat) { Transform = mat; }

	void Set_Transform(Vec3 pos, Vec3 rotation, Vec3 scale);
 
	Vec3 Get_Position() { return Position; }
	Vec3 Get_Rotation() { return Rotation; }
	Vec3 Get_Scale() { return Scale; }

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	int Get_Instance() { return ID; }
	char *Get_Name() { return Name; }
protected:

	char *Name;
	int ID;

	bool Visible;

	//    TODO: I FEEL ALL OF THIS DATA SHOULD BE STRUCTURED INTO SOMETHING CALLED TRANSFORM OR SOMETHING
	Vec3 Position = Vec3(1.0f); 
	Vec3 Rotation = Vec3(1.0f);
	Vec3 Scale    = Vec3(1.0f);   
	Matrix Transform;          
};










/* NEVER USED... SHOULD IT BE?

class Transformable
{
public:
Transformable();
Transformable(Vec3 pos, Vec3 rot, Vec3 scale)
{

}

Vec3 Position;
Vec3 Rotation;
Vec3 Scale;
Matrix Transform;
};


*/