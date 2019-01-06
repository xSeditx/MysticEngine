#pragma once
// INCOMPLETE
#include"GameObject.h"



class Script : public GameObject
{
public:
	Script();

	std::string ScriptString;
	std::vector<int> Commands;
};