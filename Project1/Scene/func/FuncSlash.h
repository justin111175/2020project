#pragma once


#include <BaseScene.h>
#include <map>


struct FuncSlash
{
	bool operator()(ActQueT &actQue, void* scene);

private:
	static std::map<UNIT_ID, int> _MaxCount;

};

