#pragma once
#include "BaseScene.h"





#include <map>

// 弾管理用-関数オブジェクト
struct FuncLevelUp
{
	bool operator()(ActQueT &actQue, void* scene);

private:
	static std::map<UNIT_ID, int> _MaxCount;

};