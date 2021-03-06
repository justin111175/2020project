#include "FuncSlash.h"
#include <algorithm>
#include <GameScene.h>
#include <Slash.h>

std::map<UNIT_ID, int>FuncSlash::_MaxCount{ {UNIT_ID::PLaS,20}/*,{UNIT_ID::EM_BULLET,2} */ };

//actQueと_objList引数としてコピーしかない
bool FuncSlash::operator()(ActQueT &actQue, void* scene)
{
	UNIT_ID unitID;
	if (actQue.second._unitID == UNIT_ID::PLAYER)
	{
		unitID = UNIT_ID::PLaS;
	}
	//else
	//{
	//	unitID = UNIT_ID::EM_BULLET;
	//}


	if (std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj)._unitID == unitID; }) < _MaxCount[unitID])
	{
		((GameScene*)scene)->_objList.emplace_back(new Slash(unitID, actQue.second.posGet(), actQue.second.sizeGet(), actQue.second.dirGet()));
		return true;
	}

	return false;



}