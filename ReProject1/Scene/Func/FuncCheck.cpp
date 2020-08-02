#include "FuncCheck.h"
#include "..\SceneMng.h"
#include "..\..\common\HitCheck.h"
#include "..\..\common\_debug\_DebugDispOut.h"

bool FuncCheck::operator()(ActQueT& actQue, void* scene)
{
	UNIT_ID unitID;


	switch (actQue.second._unitID)
	{
	case UNIT_ID::ENEMY:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{
				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					//actQue.second.RunFlag(false);
					return true;

				}
				//actQue.second.RunFlag(true);

				//Vector2 Long = { actQue.second.Pos().x - (*obj).Pos().x,  actQue.second.Pos().y - (*obj).Pos().y };
				//if (Long.x * Long.x + Long.y * Long.y < 40 * 40)
				//{
				//	actQue.second.enemyMode_ = EnemyMode::é~Ç‹ÇÈ;
				//	actQue.second._funcPos = (*obj).Pos();
				//	return true;
				//}

				//if (Long.x * Long.x + Long.y * Long.y < 100 * 100)
				//{
				//	actQue.second.enemyMode_ = EnemyMode::ÉvÉåÉCÉÑÅ[î≠å©;
				//	actQue.second._funcPos = (*obj).Pos();
				//	return true;
				//}
				//else
				//{
				//	actQue.second.enemyMode_ = EnemyMode::é©óRà⁄ìÆ;

				//}


			}
		}
		return false;
	case UNIT_ID::PLaB:
		unitID = UNIT_ID::ENEMY;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{	
				//IpSceneMng.mapPos
				_dbgDrawBox(-IpSceneMng.mapPos.x+actQue.second.Pos().x, -IpSceneMng.mapPos.y + actQue.second.Pos().y,
					-IpSceneMng.mapPos.x + actQue.second.Pos().x + actQue.second.sizeGet().x,
					-IpSceneMng.mapPos.y + actQue.second.Pos().y + actQue.second.sizeGet().y,
					0xFFFFFF, true);

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;

				}

			}
		}
		return false;
	case UNIT_ID::EyB:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{


				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
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

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					IpSceneMng._changeFlag = true;
					return true;

				}


			}
		}
		return false;

	case UNIT_ID::êŒ:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::ç∂è„))
				{

					actQue.second.DIR((*obj).DIR());
					actQue.second.RunFlag(true);
					(*obj).Pos((*obj).posOldGet());
					return true;

				}


			}
		}
		return false;
	default:
		break;
	}

	return false;

}
