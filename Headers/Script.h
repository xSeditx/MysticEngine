#pragma once
// INCOMPLETE
#include"Component.h"



class Script : public Component
{
public:
	Script();

	std::string ScriptString;
	std::vector<int> Commands;
};