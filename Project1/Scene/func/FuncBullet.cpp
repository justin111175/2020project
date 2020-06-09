#include "FuncBullet.h"

#include "Bullet.h"
#include <algorithm>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>

std::map<UNIT_ID, int>FuncBullet::_MaxCount{ {UNIT_ID::PLaB,20}/*,{UNIT_ID::EM_BULLET,2} */};

//actQue‚Æ_objListˆø”‚Æ‚µ‚ÄƒRƒs[‚µ‚©‚È‚¢
bool FuncBullet::operator()(ActQueT &actQue, void* scene)
{
	UNIT_ID unitID;
	if (actQue.second._unitID == UNIT_ID::PLAYER)
	{
		unitID = UNIT_ID::PLaB;
	}
	//else
	//{
	//	unitID = UNIT_ID::EM_BULLET;
	//}


	if (std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj)._unitID == unitID; }) < _MaxCount[unitID])
	{
		//TRACE("%d\n", _MaxCount[unitID]);



		((GameScene*)scene)->_objList.emplace_back(new Bullet(unitID, actQue.second.posGet(), actQue.second.movetype, actQue.second.sizeGet()));
		return true;
	}

	return false;



}