#pragma once

#include "Scene/BaseScene.h"
#include <map>


struct FuncCheck
{

	bool operator()(ActQueT& actQue, void* scene);
	//std::map<>
private:
	static std::map<UNIT_ID, int> _MaxCount;

};