#include "FuncCheck.h"
#include "..\SceneMng.h"
#include "..\..\common\HitCheck.h"
#include "..\..\common\_debug\_DebugDispOut.h"

bool FuncCheck::operator()(ActQueT& actQue, void* scene)
{
	UNIT_ID unitID;

	auto ChangePos = [](Vector2 pos,Vector2 size) {
	
		return Vector2{ pos.x + size.x / 2,pos.y + size.y / 2 };
	
	};
	switch (actQue.second._unitID)
	{
	case UNIT_ID::ENEMY:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{
				//if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::左上))
				//{
				//	//actQue.second.RunFlag(false);
				//	return true;

				//}
				//actQue.second.RunFlag(true);

				//Vector2 Long = { actQue.second.Pos().x - (*obj).Pos().x,  actQue.second.Pos().y - (*obj).Pos().y };
				//if (Long.x * Long.x + Long.y * Long.y < 40 * 40)
				//{
				//	actQue.second.enemyMode_ = EnemyMode::止まる;
				//	actQue.second._funcPos = (*obj).Pos();
				//	return true;
				//}

				//if (Long.x * Long.x + Long.y * Long.y < 100 * 100)
				//{
				//	actQue.second.enemyMode_ = EnemyMode::プレイヤー発見;
				//	actQue.second._funcPos = (*obj).Pos();
				//	return true;
				//}
				//else
				//{
				//	actQue.second.enemyMode_ = EnemyMode::自由移動;

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

				_dbgDrawCircle(-IpSceneMng.mapPos.x + actQue.second.Pos().x, -IpSceneMng.mapPos.y + actQue.second.Pos().y, 5, 0xFFFFFF, true);
				_dbgDrawCircle(-IpSceneMng.mapPos.x+ChangePos((*obj).Pos(), (*obj).sizeGet()).x, -IpSceneMng.mapPos.y+ChangePos((*obj).Pos(), (*obj).sizeGet()).y, (*obj).sizeGet().x / 2, 0xFFFFFF, true);
		

				if (CheckCircle(actQue.second.Pos(), 5, ChangePos((*obj).Pos(), (*obj).sizeGet()), (*obj).sizeGet().x / 2))
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

				_dbgDrawCircle(-IpSceneMng.mapPos.x + actQue.second.Pos().x, -IpSceneMng.mapPos.y + actQue.second.Pos().y, 5, 0xFFFFFF, true);
				_dbgDrawCircle(-IpSceneMng.mapPos.x + ChangePos((*obj).Pos(), (*obj).sizeGet()).x, -IpSceneMng.mapPos.y + ChangePos((*obj).Pos(), (*obj).sizeGet()).y, (*obj).sizeGet().x / 2, 0xFFFFFF, true);

				if (CheckCircle(actQue.second.Pos(), 5, ChangePos((*obj).Pos(), (*obj).sizeGet()), (*obj).sizeGet().x / 2))
				{
					actQue.second.SetAlive(false);
					(*obj).SetAlive(false);
					return true;

				}

			}
		}
		return false;

	case UNIT_ID::PLAYER:

		unitID = UNIT_ID::伝送;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::左上))
				{
					IpSceneMng._changeFlag = true;
					return true;

				}


			}
		}
		return false;

	case UNIT_ID::石:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::左上))
				{

					actQue.second.DIR((*obj).DIR());
					actQue.second.RunFlag(true);
					(*obj).Pos((*obj).posOldGet());
					return true;

				}


			}
		}
		return false;
	case UNIT_ID::スウィッチ:
		unitID = UNIT_ID::石;
		//if ((unitID == UNIT_ID::PLAYER) || (unitID == UNIT_ID::石))
		{
			for (auto obj : ((GameScene*)scene)->_objList)
			{
				if ((obj->_unitID == unitID) && (*obj).isAlive())
				{

					if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::左上))
					{

						//actQue.second.DIR((*obj).DIR());
						actQue.second.stateDir(STATE::DETH);
						//(*obj).Pos((*obj).posOldGet());
						return true;

					}
					else
					{
						actQue.second.stateDir(STATE::NORMAL);

					}


				}
			}
		}

		return false;
	case UNIT_ID::ドラゴン床:
		unitID = UNIT_ID::PLAYER;
		//if ((unitID == UNIT_ID::PLAYER) || (unitID == UNIT_ID::石))
		{
			for (auto obj : ((GameScene*)scene)->_objList)
			{
				if ((obj->_unitID == unitID) && actQue.second.GetState()==STATE::DETH)
				{

					if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::左上))
					{
						IpSceneMng.mingameFlag_ = true;
						return true;

					}



				}
			}
		}

		return false;
	default:
		break;
	}

	return false;

}
