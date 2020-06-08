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

				if (actQue.second.posGet().x + actQue.second.sizeGet().x > (*obj).posGet().x&&
					actQue.second.posGet().x < (*obj).posGet().x + (*obj).sizeGet().x&&
					actQue.second.posGet().y<(*obj).posGet().y + (*obj).sizeGet().y&&
					actQue.second.posGet().y + actQue.second.sizeGet().y>(*obj).posGet().y)
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

				if (actQue.second.posGet().x + actQue.second.sizeGet().x > (*obj).posGet().x &&
					actQue.second.posGet().x < (*obj).posGet().x + (*obj).sizeGet().x &&
					actQue.second.posGet().y<(*obj).posGet().y + (*obj).sizeGet().y &&
					actQue.second.posGet().y + actQue.second.sizeGet().y>(*obj).posGet().y)
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

				if (actQue.second.posGet().x + actQue.second.sizeGet().x > (*obj).posGet().x &&
					actQue.second.posGet().x < (*obj).posGet().x + (*obj).sizeGet().x &&
					actQue.second.posGet().y<(*obj).posGet().y + (*obj).sizeGet().y &&
					actQue.second.posGet().y + actQue.second.sizeGet().y>(*obj).posGet().y)
				{
					//actQue.second._level._status[STATUS::HP] -= 20;
					actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;
				}

			}
		}
		return false;

	default:
		break;
	}


}
