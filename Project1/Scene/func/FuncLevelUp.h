#pragma once
#include "BaseScene.h"





#include <map>

// �e�Ǘ��p-�֐��I�u�W�F�N�g
struct FuncLevelUp
{
	bool operator()(ActQueT &actQue, void* scene);

private:
	static std::map<UNIT_ID, int> _MaxCount;

};