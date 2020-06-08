#include "FuncLevelUp.h"
#include <algorithm>
#include <GameScene.h>
#include <LevelUp.h>


std::map<UNIT_ID, int>FuncLevelUp::_MaxCount{ {UNIT_ID::LevelUp,100}};

bool FuncLevelUp::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID;
	if (actQue.second._unitID == UNIT_ID::PLAYER)
	{
		unitID = UNIT_ID::LevelUp;
	}


	if (std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj)._unitID == unitID; }) < _MaxCount[unitID])
	{
		((GameScene*)scene)->_objList.emplace_back(new LevelUp(unitID, actQue.second.posGet(), actQue.second.sizeGet()));
		return true;
	}

	return false;
}
