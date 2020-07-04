#include "FuncMove.h"
#include <GameScene.h>
#include "HitCheck.h"

bool FuncMove::operator()(ActQueT& actQue, void* scene)
{
	
	UNIT_ID unitID;

	switch (actQue.second._unitID)
	{
	case UNIT_ID::PLAYER:
		unitID = UNIT_ID::FLOOR;
		break;
	default:
		break;
	}
	



	for (auto obj : ((GameScene*)scene)->_objList)
	{
		if ((obj->_unitID == unitID) && (*obj).isAlive())
		{
			switch (actQue.second.dirGet())
			{
			case DIR_ID::UP:
				if (CheckBox({ actQue.second.posGet().x ,actQue.second.posGet() .y+ actQue.second.speed.y}, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second._dirFlag[DIR_ID::UP] = false;
					return true;
				}
				else
				{
					actQue.second._dirFlag[DIR_ID::UP] = true;

				}

				break;
			case DIR_ID::DOWN:
				if (CheckBox({ actQue.second.posGet().x ,actQue.second.posGet().y + actQue.second.speed.y }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second._dirFlag[DIR_ID::DOWN] = false;
					return true;
				}
				else
				{
					actQue.second._dirFlag[DIR_ID::DOWN] = true;
				}

				break;
			case DIR_ID::LEFT:
				if (CheckBox({ actQue.second.posGet().x + actQue.second.speed.x ,actQue.second.posGet().y  }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second._dirFlag[DIR_ID::LEFT] = false;
					return true;
				}
				else
				{
					actQue.second._dirFlag[DIR_ID::LEFT] = true;
				}


				break;
			case DIR_ID::RIGHT:
				if (CheckBox({ actQue.second.posGet().x + actQue.second.speed.x ,actQue.second.posGet().y }, actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second._dirFlag[DIR_ID::RIGHT] = false;
					return true;
				}
				else
				{
					actQue.second._dirFlag[DIR_ID::RIGHT] = true;
				}
				break;

			default:
				break;
			}
			//if (CheckBox(actQue.second.posGet(), actQue.second.sizeGet(), actQue.second.speed,(*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
			//{
			//	
			//	actQue.second._dirFlag[DIR_ID::UP] = false;
			//	return true;
			//}
			//else
			//{
			//	actQue.second._dirFlag[DIR_ID::UP] = true;;
			//}
			
		
		}
	}
	return true;
	//for (auto dir : DIR_ID())
	//{
	//	actQue.second._dirFlag[dir] = true;
	//}

}
