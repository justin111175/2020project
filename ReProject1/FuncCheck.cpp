#include "FuncCheck.h"
#include "Scene/GameScene.h"
#include "common/HitCheck.h"
#include "Scene/SceneMng.h"


bool FuncCheck::operator()(ActQueT& actQue, void* scene)
{
	UNIT_ID unitID;


	switch (actQue.second._unitID)
	{

	case UNIT_ID::PLAYER:

		unitID = UNIT_ID::ì`ëó;
		for (auto obj : ((GameScene*)scene)->_objList)
		{
			if ((obj->_unitID == unitID) && (*obj).isAlive())
			{

				if (CheckBox(actQue.second.posGet(), actQue.second.sizeGet(), (*obj).posGet(), (*obj).sizeGet(), TYPE::ç∂è„))
				{
					IpSceneMng._changeFlag = true;
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
