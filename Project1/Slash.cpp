#include "Slash.h"
#include <ImageMng.h>



#define PI 3.1415926f
#define DEG (PI/180.0)

Slash::Slash()
{

	Init();
}

Slash::Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2 size, MOVE_TYPE movetype)
{
	_unitID = unitID;
	_size = { 43,11 };

	switch (movetype)
	{
	case MOVE_TYPE::UP:
		_pos.x = pos.x+size.x/2-_size.x/2;
		_pos.y = pos.y-_size.y/2;

		_rad = 270 * DEG;
		break;
	case MOVE_TYPE::DOWN:
		_pos.x = pos.x + size.x / 2 - _size.x / 2;
		_pos.y = pos.y+size.y;

		_rad = 90 * DEG;
		break;
	case MOVE_TYPE::LEFT:
		_pos.x = pos.x-size.x/2;
		_pos.y = pos.y + size.y/2-_size.y/2;

		_rad = 180 * DEG;
		break;
	case MOVE_TYPE::RIGHT:
		_pos.x = pos.x + size.x ;
		_pos.y = pos.y + size.y / 2 - _size.y / 2;


		_rad = 0 * DEG;
		break;
	default:
		break;
	}

	Init();

}


Slash::~Slash()
{
}




void Slash::Update()
{
	Cntbool = true;
	if (Cntbool)
	{
		cnt+=1;
		_rad -= cnt * DEG;
	}


	DestroyPrpc();
	//_pos.x += cos(_rad);
	//_pos.y += sin(_rad)*BulletSpeed;

	//IpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT, *this });

}



void Slash::Init(void)
{
	_alive = true;
	Cntbool = false;
	cnt = 0;
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("ŽaŒ‚")[0], 0);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}



bool Slash::DestroyPrpc(void)
{
	if (cnt>12)
	{

		_alive = false;
		state(STATE::DETH);
	}
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
