#include "Slash.h"
#include <ImageMng.h>



#define PI 3.1415926f
#define DEG (PI/180.0)

Slash::Slash()
{

	Init();
}

Slash::Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size, MOVE_TYPE movetype)
{
	_unitID = unitID;
	_exrate = { 1.0f,1.0f };
	_size = { 43,11 };
	//_size = { 380,384 };
	//_pos.x = pos.x-_size.x/2;
	//_pos.y = pos.y - _size.y / 2;
	switch (movetype)
	{
	case MOVE_TYPE::UP:
		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y+size.y/2;
		_rad = 0 * DEG;

		break;
	case MOVE_TYPE::DOWN:
		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y+size.y*2/3;

		_rad = 180 * DEG;
		break;
	case MOVE_TYPE::LEFT:

		_pos.x = pos.x+size.x/2;
		_pos.y = pos.y+size.y/2;

		_rad = 270 * DEG;
		//_rad = 180 * DEG;
		break;
	case MOVE_TYPE::RIGHT:


		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y + size.y / 2;

		_rad = 90 * DEG;
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




void Slash::Update(sharedObj plObj)
{
	DestroyPrpc();


	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	if ((*plObj).posGet()!= (*plObj).posOldGet())
	{
		_pos = (*plObj).posGet() - (*plObj).posOldGet() + _posOld;

	}


	if (IpSceneMng.frames()%60)
	{
		cnt += 3;
		_rad -= cnt * DEG;
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


	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
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
