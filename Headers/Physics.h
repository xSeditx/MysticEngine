#pragma once
#include"Common.h"


class Mass
{
public:
	Mass() {}
	Mass(float weight, Vec3 pos)
		:
		Force(0, 0, 0),
		Acceleration(0, 0, 0),
		Velocity(0, 0, 0),
		Kg(weight)
	{
		Position = pos;
	}


	Mass(float weight, float x, float y, float z)
	{
		Mass(weight, Vec3(x, y, z));
	}
	~Mass() {}


	Vec3
		Velocity,
		Position,
		Acceleration,
		Angular,
		Force;

	float  Kg;

	void Apply_Gravity();
	void Apply_Physics();
	void Set_Force(float x, float y);
	void Set_Position(float x, float y);

	Vec3 Get_Position();

	inline float Get_X() { return Position.x; }
	inline float Get_Y() { return Position.y; }
	inline float Get_Z() { return Position.z; }

	struct convert
	{
		inline float Pounds_to_Kg(float lb) { return lb * .453; }
		inline float Newtons_to_Kg(float N) { return N / 9.8; }
		inline float Kg_to_Newtons(float Kg) { return Kg * 9.8; }
	}Convert;

	struct volume
	{
		inline float ofBox(Vec3 min, Vec3 max) { return (max.x - min.x) * (max.y - min.y) * (max.z - min.z); }
		//inline float ofBox(AABB &box){return (box.MaxPoint.x - box.MinPoint.x) * (box.MaxPoint.y - box.MinPoint.y) * (box.MaxPoint.z - box.MinPoint.x);}
		inline float ofSphere(float radius) { return (4 / 3)*(M_PI * (radius*radius*radius)); }
	}Volume;


	static void  Set_Timestep(float time) { Current_Timestep = time; }
	static void  Set_Gravity(float g) { Gravity = g; }

	static float Get_Timestep() { return Current_Timestep; }
	static float Get_Gravity() { return Gravity; }


private:

	static float Current_Timestep;
	static float Gravity;
};
