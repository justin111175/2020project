#include "FuncBullet.h"
#include "Bullet.h"
#include <algorithm>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>

std::map<UNIT_ID, int>FuncBullet::_MaxCount{ {UNIT_ID::PLaB,20}/*,{UNIT_ID::EM_BULLET,2} */};

//actQue��_objList�����Ƃ��ăR�s�[�����Ȃ�
bool FuncBullet::operator()(ActQueT &actQue, void* scene)
{
	UNIT_ID unitID;
	if (actQue.second._unitID == UNIT_ID::PLAYER)
	{
		unitID = UNIT_ID::PLaB;
	}



	if (std::count_if(((GameScene*)scene)->_objList.begin(), ((GameScene*)scene)->_objList.end(), [&](sharedObj obj) {return (*obj)._unitID == unitID; }) < _MaxCount[unitID])
	{


		((GameScene*)scene)->_objList.emplace_back(new Bullet(unitID, actQue.second.posGet(), actQue.second.dirGet(), actQue.second.sizeGet()));
		return true;
	}

	return false;



}