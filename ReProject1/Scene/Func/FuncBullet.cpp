#include "FuncBullet.h"
#include "..\..\Bullet.h"
#include <algorithm>
#include "..\GameScene.h"

std::map<UNIT_ID, int>FuncBullet::_MaxCount{ {UNIT_ID::EyB,30},{UNIT_ID::PLaB,20}, };

//actQue‚Æ_objListˆø”‚Æ‚µ‚ÄƒRƒs[‚µ‚©‚È‚¢
bool FuncBullet::operator()(ActQueT &actQue, void* scene)
{
	UNIT_ID unitID;

	switch (actQue.second._unitID)
	{
	case UNIT_ID::ENEMY:
		unitID = UNIT_ID::EyB;
		break;
	case UNIT_ID::PLAYER:
		unitID = UNIT_ID::PLaB;
		break;
	}

	if (std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj)._unitID == unitID; }) < _MaxCount[unitID])
	{


		((GameScene*)scene)->_objList.emplace_back(new Bullet(unitID, actQue.second.Pos(), actQue.second.DIR(), actQue.second.sizeGet()));
		return true;
	}

	return false;



}