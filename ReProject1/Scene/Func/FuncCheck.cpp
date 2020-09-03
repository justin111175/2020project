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
	//case UNIT_ID::ENEMY:
	//	unitID = UNIT_ID::PLAYER;
	//	for (auto obj : ((GameScene*)scene)->_objList)
	//	{
	//		if ((obj->_unitID == unitID) && (*obj).isAlive())
	//		{
	//			if (CheckCircle(actQue.second.Pos(), 5, ChangePos((*obj).Pos(), (*obj).sizeGet()), (*obj).sizeGet().x / 2))
	//			{
	//

	//			}


	//		}
	//	}
	//	return false;
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
					(*obj)._status[Status_ID::HP] -= actQue.second._status[Status_ID::�U����];
					actQue.second.SetAlive(false);

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
					if ((*obj).tateFlag_)
					{
						if ((*obj)._status[Status_ID::�X�^�~�i] > actQue.second._status[Status_ID::�U����])
						{
							(*obj)._status[Status_ID::�X�^�~�i] -= actQue.second._status[Status_ID::�U����];
							(*obj)._cnt = 10;

							(*obj).gekitaiFlag_ = true;
						}
						else
						{
							(*obj)._status[Status_ID::HP] -= actQue.second._status[Status_ID::�U����];

							(*obj)._status[Status_ID::�X�^�~�i] = 0;
							(*obj).tateFlag_ = false;
							(*obj)._cnt = 60;
							(*obj).gekitaiFlag_ = true;

						}
					}
					else
					{
						if (!(*obj).gekitaiFlag_)
						{
							(*obj)._status[Status_ID::HP] -= actQue.second._status[Status_ID::�U����];
							(*obj)._cnt = 60;
							(*obj).gekitaiFlag_ = true;

						}
					}


					return true;

				}

			}
		}
		return false;

	case UNIT_ID::PLAYER:

		unitID = UNIT_ID::�`��;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::����))
				{
					IpSceneMng._changeFlag = true;
					return true;

				}


			}
		}
		return false;

	case UNIT_ID::��:
		unitID = UNIT_ID::PLAYER;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::����))
				{

					actQue.second.DIR((*obj).DIR());
					actQue.second.RunFlag(true);
					(*obj).Pos((*obj).posOldGet());
					return true;

				}


			}
		}
		return false;
	case UNIT_ID::�X�E�B�b�`:
		unitID = UNIT_ID::��;
		//if ((unitID == UNIT_ID::PLAYER) || (unitID == UNIT_ID::��))
		{
			for (auto obj : ((GameScene*)scene)->_objList)
			{
				if ((obj->_unitID == unitID) && (*obj).isAlive())
				{

					if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::����))
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
	case UNIT_ID::�h���S����:
		unitID = UNIT_ID::PLAYER;
		//if ((unitID == UNIT_ID::PLAYER) || (unitID == UNIT_ID::��))
		{
			for (auto obj : ((GameScene*)scene)->_objList)
			{
				if ((obj->_unitID == unitID) && actQue.second.GetState()==STATE::DETH)
				{

					if (CheckBox(actQue.second.Pos(), actQue.second.sizeGet(), (*obj).Pos(), (*obj).sizeGet(), TYPE::����))
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
