#include "FuncCheck.h"
#include <SceneMng.h>
#include <GameScene.h>

bool FuncCheck::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID;

	if (actQue.second._unitID == UNIT_ID::PLAYER)
	{
		unitID = UNIT_ID::ENEMY;
	}

	for (auto obj : ((GameScene*)scene)->_objList)
	{
		if ((obj->_unitID == unitID) && actQue.second.isAlive())
		{


			if (actQue.second._pos.x+actQue.second._size.x>(*obj)._pos.x&&
				actQue.second._pos.x< (*obj)._pos.x+ (*obj)._size.x&&
				actQue.second._pos.y<(*obj)._pos.y+(*obj)._size.y&&
				actQue.second._pos.y+ actQue.second._size.y>(*obj)._pos.y)
			{
				actQue.second._level._sutetasu[sutetasu::HP] -= 20;
				return true;
			}
			//else
			//{
			//	IpSceneMng._endFlag = false;
			//}
		}
	}
	return false;

}
