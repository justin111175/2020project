#include "Bullet.h"
#include <ImageMng.h>



#define PI 3.1415926f
#define DEG (PI/180.0)

Bullet::Bullet()
{

	Init();
}

Bullet::Bullet(UNIT_ID unitID, Vector2Dbl pos, MOVE_TYPE movetype)
{
	_unitID = unitID;
	_pos = pos;
	_size = { 43,11 };

	switch (movetype)
	{
	case MOVE_TYPE::UP:
		_rad = 270 * DEG;
		break;
	case MOVE_TYPE::DOWN:
		_rad = 90 * DEG;
		break;
	case MOVE_TYPE::LEFT:
		_rad = 180 * DEG;
		break;
	case MOVE_TYPE::RIGHT:
		_rad = 0 * DEG;
		break;
	default:
		break;
	}
	
	Init();

}


Bullet::~Bullet()
{
}




void Bullet::Update(sharedObj plObj)
{

	_pos.x += cos(_rad)*BulletSpeed;
	_pos.y += sin(_rad)*BulletSpeed;

	//IpSceneMng.AddActQue({ ACT_QUE::CHECK_HIT, *this });
	DestroyPrpc();
}



void Bullet::Init(void)
{
	_alive = true;
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("’e")[0], 30);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}



bool Bullet::DestroyPrpc(void)
{
	//if (_pos.y < IpSceneMng.GameScreenOffset.y - _size.y ||
	//	_pos.y>IpSceneMng.GameScreenOffset.y + IpSceneMng.ScreenCenter.y)
	//{

	//	_alive = false;
	//	state(STATE::DETH);

	//}
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
