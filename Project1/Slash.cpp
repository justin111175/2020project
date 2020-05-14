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
	//_pos = pos;
	_size = { 43,11 };

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
		//_pos.x = pos.x-size.x/2;
		//_pos.y = pos.y + size.y/2-_size.y/2;
		_pos.x = pos.x+size.x/2;
		_pos.y = pos.y+size.y/2;

		_rad = 270 * DEG;
		//_rad = 180 * DEG;
		break;
	case MOVE_TYPE::RIGHT:
		//_pos.x = pos.x + size.x ;
		//_pos.y = pos.y + size.y / 2 - _size.y / 2;

		_pos.x = pos.x + size.x / 2;
		_pos.y = pos.y + size.y / 2;

		_rad = 90 * DEG;

		//_rad = 0 * DEG;
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
	if (IpSceneMng.frames()%10)
	{
		cnt += 1;
		_rad -= cnt * DEG;
		//if (_rad > 90 * DEG)
		//{
		//	_rad -= cnt * DEG;
		//}
		//else
		//{
		//	_rad += cnt * DEG;
		//}

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
	data.emplace_back(IMAGE_ID("ŽaŒ‚1")[0], 0);
	SetAnim(STATE::NORMAL, data);

	//data.emplace_back(IMAGE_ID("weapons")[0], 10);
	//data.emplace_back(IMAGE_ID("weapons")[1], 20);
	//data.emplace_back(IMAGE_ID("weapons")[2], 30);
	SetAnim(STATE::NORMAL, data);


	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}



bool Slash::DestroyPrpc(void)
{
	if (cnt>20||cnt<-20)
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
