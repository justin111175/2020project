#include "Bullet.h"
#include "common/ImageMng.h"



#define PI 3.1415926f
#define DEG (PI/180.0)

Bullet::Bullet()
{

	Init();
}

Bullet::Bullet(UNIT_ID unitID, Vector2 pos, DIR_ID movetype, Vector2 size)
{
	_unitID = unitID;
	_size = { 20,10 };
	_exrate = { 1.0f,1.0f };



	Init();

	//�e���˂̊p�x�Ə������W
	switch (movetype)
	{
	case DIR_ID::UP:
		_rad = 270 * DEG;
		_pos.x = pos.x + size.x / 2 - _size.y / 2;
		_pos.y = pos.y;
		break;
	case DIR_ID::DOWN:

		_rad = 90 * DEG;

		_pos.x = pos.x + size.x / 2+ _size.y / 2;
		_pos.y = pos.y;
		break;
	case DIR_ID::LEFT:
		_rad = 180 * DEG;

		_pos.x = pos.x + size.x / 2 ;
		_pos.y = pos.y + size.y / 2 + _size.y / 2;
		break;
	case DIR_ID::RIGHT:
		_rad = 0 * DEG;

		_pos.x = pos.x + size.x / 2 - _size.y / 2;
		_pos.y = pos.y + size.y / 2 ;
		break;
	default:
		break;
	}
	
	_posOld = _pos;


}

Bullet::Bullet(UNIT_ID unitID, Vector2 pos, double rad)
{

	_unitID = unitID;
	_size = { 20,10 };
	_exrate = { 1.0f,1.0f };



	Init();

	//�e���˂̊p�x�Ə������W
	
	_pos = pos;
	_posOld = _pos;
}


Bullet::~Bullet()
{
}




void Bullet::Update(sharedObj& plObj)
{
	
	//�e�ړ�
	_pos.x += static_cast<int>(cos(_rad)*BulletSpeed);
	_pos.y += static_cast<int>(sin(_rad)*BulletSpeed);

	//�e�̓����蔻��
	



	//�v���C���[����̋���200�Ȍ����

	if (_unitID == UNIT_ID::PLaB)
	{
		_status[Status_ID::�U����] = plObj->_status[Status_ID::�U����];
		if ((((_posOld.y-_pos.y)* (_posOld.y - _pos.y))+ ((_posOld.x - _pos.x) * (_posOld.x - _pos.x)))>200.0*200.0)
		{
			SetAlive(false);
		}
		IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	}
	else
	{
		_status[Status_ID::�U����] = 20;

		if ((((_posOld.y - _pos.y) * (_posOld.y - _pos.y)) + ((_posOld.x - _pos.x) * (_posOld.x - _pos.x))) > 400 * 400)
		{
			SetAlive(false);
		}
		IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	}




	DestroyPrpc();
}



void Bullet::Init(void)
{
	_alive = true;


	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("�e")[0], 30);
	SetAnim(STATE::NORMAL,data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);


	_status.try_emplace(Status_ID::�U����, 1);


	stateDir(STATE::NORMAL,DIR_ID::DOWN);
}



bool Bullet::DestroyPrpc(void)
{

	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
