#include "Slash.h"
#include <ImageMng.h>



#define PI 3.1415926f
#define DEG (PI/180.0)

Slash::Slash()
{

	Init();
}

Slash::Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size, DIR_ID movetype)
{
	_unitID = unitID;
	_exrate = { 1.0f,1.0f };
	_size = { 43,11 };
	//_size = { 380,384 };
	//_pos.x = pos.x-_size.x/2;
	//_pos.y = pos.y - _size.y / 2;
	switch (movetype)
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
		//_rad = 180 * DEG;
		break;
	case DIR_ID::RIGHT:


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
		// ��ʗh�炵��QUE�𓊂���
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
	data.emplace_back(IMAGE_ID("�a��2")[0], 0);


	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	stateDir(STATE::NORMAL,DIR_ID::DOWN);
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
