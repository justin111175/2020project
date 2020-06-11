#include "Bullet.h"
#include <ImageMng.h>



#define PI 3.1415926f
#define DEG (PI/180.0)

Bullet::Bullet()
{

	Init();
}

Bullet::Bullet(UNIT_ID unitID, Vector2Dbl pos, MOVE_TYPE movetype, Vector2Dbl size)
{
	_unitID = unitID;
	_size = { 43,11 };
	_exrate = { 1.0f,1.0f };



	Init();

	switch (movetype)
	{
	case MOVE_TYPE::UP:
		_rad = 270 * DEG;
		_pos.x = pos.x + size.x / 2 - _size.y / 2;
		_pos.y = pos.y;
		break;
	case MOVE_TYPE::DOWN:

		_rad = 90 * DEG;
		_pos.x = pos.x + size.x / 2+ _size.y / 2;
		_pos.y = pos.y;
		break;
	case MOVE_TYPE::LEFT:

		_rad = 180 * DEG;
		_pos.x = pos.x + size.x / 2 ;
		_pos.y = pos.y + size.y / 2 + _size.y / 2;
		break;
	case MOVE_TYPE::RIGHT:
		_rad = 0 * DEG;
		_pos.x = pos.x + size.x / 2 - _size.y / 2;
		_pos.y = pos.y + size.y / 2 ;
		break;
	default:
		break;
	}
	
	_posOld = _pos;


}


Bullet::~Bullet()
{
}




void Bullet::Update(sharedObj plObj)
{
	
	_pos.x += cos(_rad)*BulletSpeed;
	_pos.y += sin(_rad)*BulletSpeed;

	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });
	
	if ((((_posOld.y-_pos.y)* (_posOld.y - _pos.y))+ ((_posOld.x - _pos.x) * (_posOld.x - _pos.x)))>200.0*200.0)
	{
		SetAlive(false);
	}


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

	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
