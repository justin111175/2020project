#include "FuncSlash.h"
#include <algorithm>
#include <GameScene.h>
#include <Slash.h>

std::map<UNIT_ID, int>FuncSlash::_MaxCount{ {UNIT_ID::PLaS,20}/*,{UNIT_ID::EM_BULLET,2} */ };

//actQue‚Æ_objListˆø”‚Æ‚µ‚ÄƒRƒs[‚µ‚©‚È‚¢
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
		((GameScene*)scene)->_objList.emplace_back(new Slash(unitID, actQue.second._pos, actQue.second._size, actQue.second.movetype));
		return true;
	}

	return false;



}