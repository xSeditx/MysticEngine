#pragma once
//                                                                                                                                           
//                                           OPENGL 2.0 Abstraction API
//                                                January 24 2018
//                                               -----------------                                                                           
//                                                                                                                                           
//                                        COLLISION AND SIMPLE PHYSICS LIB                                                                    
// 
//
// EFFICIENT DISTANCE COMPUTATION:  https://arxiv.org/ftp/arxiv/papers/1410/1410.4603.pdf
//==========================================================================================================================

/*~~~~~~~~~~~~~~~~~~ NOTES ~~~~~~~~~~~~~~~~~~~~*/

//  Young's modulus E = Stress / Strain
//                  k = E * (Area / Length)
// angle_deg = RADIANS(acos(Vec3::DotProduct(VectorA.Normalize(), VectorB.Normalize() ))
// Force =  Axis Displacement   * Spring Factor - Damping Factor


#pragma once

#include<vector>
//#include"Window.h"
#include"Core.h"
#include"Physics.h"
#include"Common.h"
//#include"QuadTree.h"

//class QT; class Node;


enum ColliderType
{
	ColliderUNKNOWN = 0,
	ColliderAABB,
	ColliderCOLLISIONSPHERE,
	ColliderPVP
};


class AABB;
class CollisionSphere;


class Collider
{
public:
	Collider() {}

	int ID;

	Vec3 Position;

	Mesh *Object;

	Mass Body;

	ColliderType Type;

	virtual bool IsCollision(const Collider        *other) const;
	virtual bool IsCollision(const AABB            *other) const;
	virtual bool IsCollision(const CollisionSphere *other) const;

	virtual void Update();
	virtual void Render();

	// Static Methods and Variables
	static std::vector<Collider*> CollisionList;
	static int NumberOfObjects;
};

class CollisionSphere : public Collider
{
public:
	CollisionSphere(Mesh  *object, float radius);
	CollisionSphere(Vec3 Position, float radius);

	float Radius;

	bool IsCollision(const CollisionSphere *other) const override;
	bool IsCollision(const AABB            *other) const override;
	bool IsCollision(const Collider        *other) const override;


	bool PointInsideSphere(Vec3 point);

	void Update();
	void Render();
	void TestAllCollisions();
};

class AABB : public Collider
{
public:
	AABB() { Type = ColliderAABB; }
	AABB::AABB(Vec3 min, Vec3 max);

	Vec3 MinPoint,
		MaxPoint;

	float x1, x2,
		y1, y2,
		z1, z2;

	bool IsCollision(const AABB            *other) const override;
	bool IsCollision(const CollisionSphere *other) const override;
	bool IsCollision(const Collider        *other) const override;


	bool PointInsideAABB(Vec3 point);
	bool Intersect(AABB a, AABB b);


	void Update();
	void Render();
	void TestAllCollisions();
};