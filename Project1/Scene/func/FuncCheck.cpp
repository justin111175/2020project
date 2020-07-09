#include "FuncCheck.h"
#include <SceneMng.h>
#include <GameScene.h>
#include "HitCheck.h"
#include "_DebugDispOut.h"

bool FuncCheck::operator()(ActQueT & actQue, void * scene)
{
	UNIT_ID unitID;

	auto S_pos = [](Vector2Dbl pos,Vector2Dbl size) {
	
		return Vector2Dbl(pos.x - size.x / 2, pos.y - size.y / 2);
	};


	switch (actQue.second._unitID)
	{
	case UNIT_ID::ENEMY:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive()&&!(*obj).repelFlagGet())
			{
				if (CheckBox(actQue.second.posGet(), actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					
					(*obj).funcPos(actQue.second.posGet());
					(*obj).SetRepel(true);
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

				switch (actQue.second.dirGet())
				{
				case DIR_ID::UP:
					
					if (CheckBox({ S_pos(actQue.second.posGet(), actQue.second.sizeGet()).x,S_pos(actQue.second.posGet(), actQue.second.sizeGet()).y- actQue.second.sizeGet().y/2 }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
					{
						(*obj)._status[Status_ID::HP] -= 100;
						return true;
					}
					break;
				case DIR_ID::DOWN:
					if (CheckBox({ S_pos(actQue.second.posGet(), actQue.second.sizeGet()).x,S_pos(actQue.second.posGet(), actQue.second.sizeGet()).y + actQue.second.sizeGet().y / 2 }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
					{
						(*obj)._status[Status_ID::HP] -= 100;
						return true;
					}

					break;
				case DIR_ID::LEFT:

					if (CheckBox({ S_pos(actQue.second.posGet(), actQue.second.sizeGet()).x - actQue.second.sizeGet().x / 2,S_pos(actQue.second.posGet(), actQue.second.sizeGet()).y  }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
					{
						(*obj)._status[Status_ID::HP] -= 100;
						return true;
					}

					break;
				case DIR_ID::RIGHT:
					if (CheckBox({ S_pos(actQue.second.posGet(), actQue.second.sizeGet()).x + actQue.second.sizeGet().x / 2,S_pos(actQue.second.posGet(), actQue.second.sizeGet()).y }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
					{
						(*obj)._status[Status_ID::HP] -= 100;
						return true;
					}

					break;
				default:
					break;
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

				if (CheckBox(actQue.second.posGet(), actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(),TYPE::ç∂è„))
				{
					//actQue.second._level._status[STATUS::HP] -= 20;
					actQue.second.SetAlive(false);
					(*obj)._status[Status_ID::HP] -= 50;
					//(*obj).SetAlive(false);
					return true;
				}

			}
		}
		return false;


		case UNIT_ID::PLAYER:

		unitID = UNIT_ID::ì`ëó;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.posGet(), actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					
					actQue.second._testFlag = true;
					return true;

				}
				else
				{
					actQue.second._testFlag = false;
				}

			}
		}
		return false;

	default:
		break;
	}
	
	return false;

}
