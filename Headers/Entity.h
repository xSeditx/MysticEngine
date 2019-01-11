#pragma once

#include"GameObject.h"
//#include"Object.h"


class Entity : public GameObject
{
public:
	Entity();

	void Update();
	void Render();
	void Bind();
	void Unbind();

	std::vector<GameObject> Parts;
};