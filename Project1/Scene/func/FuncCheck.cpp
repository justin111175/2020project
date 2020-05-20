#include "FuncCheck.h"
#include <SceneMng.h>
#include <GameScene.h>

bool FuncCheck::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID;

	//if (actQue.second._unitID == UNIT_ID::PLAYER)
	//{
	//	unitID = UNIT_ID::ENEMY;
	//}

	switch (actQue.second._unitID)
	{
	case UNIT_ID::ENEMY:
		unitID = UNIT_ID::PLAYER;
		unitID = UNIT_ID::ENEMY;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (actQue.second._pos.x + actQue.second._size.x > (*obj)._pos.x&&
					actQue.second._pos.x < (*obj)._pos.x + (*obj)._size.x&&
					actQue.second._pos.y<(*obj)._pos.y + (*obj)._size.y&&
					actQue.second._pos.y + actQue.second._size.y>(*obj)._pos.y)
				{
					//actQue.second._level._status[STATUS::HP] -= 20;
					//actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;
				}
			}
		}
		return false;

	case UNIT_ID::PLaS:

		unitID = UNIT_ID::ENEMY;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (actQue.second._pos.x + actQue.second._size.x > (*obj)._pos.x&&
					actQue.second._pos.x < (*obj)._pos.x + (*obj)._size.x&&
					actQue.second._pos.y<(*obj)._pos.y + (*obj)._size.y&&
					actQue.second._pos.y + actQue.second._size.y>(*obj)._pos.y)
				{
					//actQue.second._level._status[STATUS::HP] -= 20;
					//actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;
				}
			}
		}
		return false;

	case UNIT_ID::PLaB:

		unitID = UNIT_ID::ENEMY;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) &&(*obj).isAlive())
			{

				if (actQue.second._pos.x + actQue.second._size.x > (*obj)._pos.x&&
					actQue.second._pos.x < (*obj)._pos.x + (*obj)._size.x&&
					actQue.second._pos.y<(*obj)._pos.y + (*obj)._size.y&&
					actQue.second._pos.y + actQue.second._size.y>(*obj)._pos.y)
				{
					//actQue.second._level._status[STATUS::HP] -= 20;
					actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;
				}
				//else
				//{
				//	return false;
				//}
			}
		}
		return false;

	default:
		break;
	}


}
