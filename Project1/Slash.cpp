#include "Slash.h"
#include <ImageMng.h>




Slash::Slash()
{

	Init();
}

Slash::Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size, DIR_ID movetype)
{
	_unitID = unitID;
	_exrate = { 1.0f,1.0f };
	_size = { 48,49 };
	_dir = movetype;

	switch (_dir)
	{
	case DIR_ID::UP:
		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y+size.y/2;
		_rad = 0 * DEG;

		break;
	case DIR_ID::DOWN:
		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y+size.y*2/3;

		_rad = 180 * DEG;
		break;
	case DIR_ID::LEFT:

		_pos.x = pos.x+size.x/2;
		_pos.y = pos.y+size.y/2;

		_rad = 270 * DEG;

		break;
	case DIR_ID::RIGHT:


		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y + size.y / 2;

		_rad = 180 * DEG;

		break;
	default:
		break;
	}
	_posOld = _pos;
	Init();

}


Slash::~Slash()
{
}




void Slash::Update(void)
{
	DestroyPrpc();


	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	//if ((*plObj).posGet()!= (*plObj).posOldGet())
	//{
	//	_pos = (*plObj).posGet() - (*plObj).posOldGet() + _posOld;

	//}


	if (IpSceneMng.frames()%60)
	{
		switch (_dir)
		{

		case DIR_ID::RIGHT:
			cnt += 3;
			_rad += cnt * DEG;
			break;

		default:
			cnt += 3;
			_rad -= cnt * DEG;
			break;
		}

	}




}

bool Slash::SetAlive(bool alive)
{
	if (!alive)
	{
		// ‰æ–Ê—h‚ç‚µ‚ÌQUE‚ð“Š‚°‚é
		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
	}

	return Obj::SetAlive(alive);
}



void Slash::Init(void)
{
	_alive = true;
	Cntbool = false;

	_unitID = UNIT_ID::PLaS;

	cnt = 0;
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("ŽaŒ‚2")[0], 0);
	SetAnim(STATE::NORMAL, DIR_ID::LEFT,data);
	
	data.emplace_back(IMAGE_ID("ŽaŒ‚2")[0], 0);
	SetAnim(STATE::NORMAL, DIR_ID::UP, data);
	data.emplace_back(IMAGE_ID("ŽaŒ‚1")[0], 0);
	SetAnim(STATE::NORMAL, DIR_ID::DOWN, data);
	data.emplace_back(IMAGE_ID("ŽaŒ‚1")[0], 0);

	SetAnim(STATE::NORMAL, DIR_ID::RIGHT, data);
	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	stateDir(STATE::NORMAL);
}

bool Slash::DestroyPrpc(void)
{
	if (cnt > 30 || cnt < -30)
	{
		SetAlive(false);
	}
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
