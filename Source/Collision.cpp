#include "Collision.h"
#include "Camera.h"

#include<algorithm>

std::vector<Collider*> Collider::CollisionList;
int Collider::NumberOfObjects = 0;





//=========================================================================================================================
//__________________________________    Collider Base Class   _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------


bool Collider::IsCollision(const Collider *other) const
{
	return false;
}
bool Collider::IsCollision(const AABB *other) const
{
	return false;
}
bool Collider::IsCollision(const CollisionSphere *other) const
{
	return false;
}
void Collider::Update()
{
	Print("Wrong One");
}
void Collider::Render()
{
}



//=========================================================================================================================
//___________________________    BoundingSphere Collision Detector    _____________________________________________________
//-------------------------------------------------------------------------------------------------------------------------
CollisionSphere::CollisionSphere(Vec3 position, float radius)
	:
	Radius(radius)

{
	Object = nullptr;

	Position = position;

	Body = Mass(radius, position);

	ID = NumberOfObjects++;

	Type = ColliderCOLLISIONSPHERE;

	CollisionList.push_back(this);
}
CollisionSphere::CollisionSphere(Mesh *parent, float radius)
	:
	Radius(radius)
{
	ID = NumberOfObjects++;
	Object = parent;
	Position = parent->Get_Position();
	Body = Mass(radius, parent->Get_Position());
	Type = ColliderCOLLISIONSPHERE;
	CollisionList.push_back(this);
}

//CollisionSphere::CollisionSphere(const CollisionSphere &other)
//{
//     std::memcpy(this, &other, sizeof(other));
//}
//

bool CollisionSphere::IsCollision(const CollisionSphere *other) const  // Use to return a float, might go back to doing that
{
	if (other->ID != this->ID)
	{
		return  GetDistance(Body.Position, other->Body.Position) < (Radius + other->Radius);
	}
	return false;
}
bool CollisionSphere::IsCollision(const AABB *other) const
{
	if (other->ID != this->ID)
	{
		return GetDistance(Vec3(
			std::max(other->MinPoint.x, std::min(Position.x, other->MaxPoint.x)),
			std::max(other->MinPoint.y, std::min(Position.y, other->MaxPoint.y)),
			std::max(other->MinPoint.z, std::min(Position.z, other->MaxPoint.z))
		), Position) < Radius;
	}
	return false;
}
bool CollisionSphere::IsCollision(const Collider *other)  const
{
	if (other->ID != this->ID)
	{
		return other->IsCollision(this);
	}
	return false;
}
bool CollisionSphere::PointInsideSphere(Vec3 point)
{
	float Distance = sqrt((point.x - Position.x) * (point.x - Position.x) +
		(point.y - Position.y) * (point.y - Position.y) +
		(point.z - Position.z) * (point.z - Position.z));
	return Distance < Radius;
}

void CollisionSphere::Update()
{
	Body.Velocity = Body.Velocity * .95f;

	Vec3  Last_Acceleration = Body.Acceleration;
	Body.Position += Body.Velocity *  Mass::Get_Timestep() + (Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()));
	Body.Acceleration = Body.Force / Body.Kg;

	Body.Force = Vec3(0.0f);

	Vec3  Avg_Acceleration = (Last_Acceleration + Body.Acceleration) / 2.0f;
	Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();
	if (Object)Object->Get_Position() = Body.Position;
	Position = Body.Position;
	Render();
	TestAllCollisions();  // Horrible naming just Temp until I have everything in place. 
}
void CollisionSphere::Render()
{
	glBegin(GL_LINES);
	glVertex3f(Position.x, Position.y, Position.z);
	glVertex3f(Position.x + Radius,
		Position.y + Radius,
		Position.z + Radius);
	glEnd();
}

void CollisionSphere::TestAllCollisions()
{
	std::vector<Collider*> results; // Checks the area around the object in the Quadtree and returns andthing in the same Sector
//	results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z), Vec2(10, 10));
// TODO: MAKE SOMETHING TO NARROW DOWN THE COLLISION TEST> DONE WITH QUAD TREE IN THE PAST. DESIGN SOME BROAD PHASE
	for (Collider *List : results)
	{
		if (List != this) // This is quite possible my Object->ID check, I think I am checking twice on accident.
		{
			if (IsCollision(List))
			{
				Print("Sphere Collision:");// React to that Collision in some way by writing a Physics Module. 
			}
		}
	}
}


//=========================================================================================================================
//___________________________      AABB Collision Detector    _____________________________________________________________
//-------------------------------------------------------------------------------------------------------------------------

AABB::AABB(Vec3 min, Vec3 max)
{
	Position = (min + max) * 0.5f;

	Body = Mass(10, Position);

	ID = NumberOfObjects++;

	MaxPoint = max;
	MinPoint = min;

	x1 = min.x; y1 = min.y; z1 = min.z;
	x2 = min.x; y2 = min.y; z2 = min.z;

	Type = ColliderAABB;

	CollisionList.push_back(this);
}

bool AABB::IsCollision(const Collider *other) const
{
	if (other->ID != this->ID)
	{
		return other->IsCollision(this);
	}
	return false;
}
bool AABB::IsCollision(const AABB *other)  const
{
	if (other->ID != this->ID)
	{
		return
			(std::min(x1, x2) <= std::max(other->x1, other->x2) && std::max(x1, x2) >= std::min(other->x1, other->x2)) &&
			(std::min(y1, y2) <= std::max(other->y1, other->y2) && std::max(y1, y2) >= std::min(other->y1, other->y2)) &&
			(std::min(z1, z2) <= std::max(other->z1, other->z2) && std::max(z1, z2) >= std::min(other->z1, other->z2));                   //Intersect(*this, *other);
	}
	return false;
}
bool AABB::IsCollision(const CollisionSphere *other)  const
{
	if (other->ID != this->ID)
	{
		return other->IsCollision(this);
	}
	return false;
}
bool AABB::PointInsideAABB(Vec3 point)
{
	return
		(point.x >= std::min(x1, x2) && point.x <= std::max(x1, x2)) &&
		(point.y >= std::min(y1, y2) && point.y <= std::max(y1, y2)) &&
		(point.z >= std::min(z1, z2) && point.z <= std::max(z1, z2));
}

bool AABB::Intersect(AABB a, AABB b)
{
	return
		(
		(std::min(a.x1, a.x2) <= std::max(b.x1, b.x2) && std::max(a.x1, a.x2) >= std::min(b.x1, b.x2)) &&
		(std::min(a.y1, a.y2) <= std::max(b.y1, b.y2) && std::max(a.y1, a.y2) >= std::min(b.y1, b.y2)) &&
		(std::min(a.z1, a.z2) <= std::max(b.z1, b.z2) && std::max(a.z1, a.z2) >= std::min(b.z1, b.z2))
		);
}

void AABB::Update()
{
	MaxPoint = Vec3(std::max(x1, x2), std::max(y1, y2), std::max(z1, z2));
	MinPoint = Vec3(std::min(x1, x2), std::min(y1, y2), std::min(z1, z2));
	Position = (MinPoint + MaxPoint) / 2.0f;
	// Perform Physics Calculations and than do a broadphase collisionSweep of all other Colliders in the System
	Body.Velocity = Body.Velocity * .95f;

	Vec3  Last_Acceleration = Body.Acceleration;
	Body.Position += Body.Velocity *  Mass::Get_Timestep() + (Last_Acceleration * 0.5f * Squared(Mass::Get_Timestep()));
	Body.Acceleration = Body.Force / Body.Kg;

	Body.Force = Vec3(0.0f);

	Vec3  Avg_Acceleration = (Last_Acceleration + Body.Acceleration) / 2.0f;
	Body.Velocity += Avg_Acceleration * Mass::Get_Timestep();

}
void AABB::Render()
{
	glBegin(GL_LINES);
	glVertex3f(MinPoint.x, MinPoint.y, MinPoint.z);
	glVertex3f(MaxPoint.x, MaxPoint.y, MaxPoint.z);
	glEnd();
}

void AABB::TestAllCollisions() // Just temp function its goal is to run through all possible Collisions in the system by testing the QuadTree and all Collider objects will test again the given object
{
	std::vector<Collider*> results;
//	results = Tree->RootNode->QueryRange(Vec2(Body.Position.x, Body.Position.z), Vec2(10, 10));
// TODO: AGAIN MAKE A BROAD PHASE COLLISION TEST TO NARROW DOWN THE TEST
	for (Collider *List : results)
	{
		if (List != this)
		{
			if (IsCollision(List))
			{
				Print("AABB Collision");// React to that Collision in some way by writing a Physics Module. 
			}
		}
	}
}






// ATTENTION: MOUSE PICKER NEEDS TO BE FIXED HERE TO WORK WITH MATRICES

//   CollisionSphere* MousePicker(Camera cam, int *distance)
//   {
//     Vec3  EndPosition, 
//           StartPosition = cam.Position;
//   
//           for_loop(dist, 200)
//           {
//               EndPosition = Vec3::RayCast(StartPosition, cam.Rotation, dist);
//               for_loop(i, CollisionSphere::Collision_ObjectCount)
//               {
//                       if(Collider[i]->Body.Position.x < EndPosition.x +  Collider[i]->Radius && Collider[i]->Body.Position.x > EndPosition.x - Collider[i]->Radius &&
//                          Collider[i]->Body.Position.y < EndPosition.y +  Collider[i]->Radius && Collider[i]->Body.Position.y > EndPosition.y - Collider[i]->Radius &&
//                          Collider[i]->Body.Position.z < EndPosition.z +  Collider[i]->Radius && Collider[i]->Body.Position.z > EndPosition.z - Collider[i]->Radius)
//                       {
//                          *distance = dist;
//                          return Collider[i];
//                       }
//                       
//               }
//   
//           }
//   return false;
//   }


//  Acceleration = Force / Mass;
//  Velocity += Acceleration;
//  Position += Velocity;
//  Force = 0.0;


//if(dist  < (Radius + other->Radius))
//{
//    return true; //return dist; // Consider going back to returning Dist so that it returns useful information about the collision;
//}
