#include "Enemy.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "DxLib.h"
#include "Obj.h"

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(EnemyState& state)
{
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));
	_exrate = std::move(std::get<static_cast<int>(ENEMY_STATE::EXRATE)>(state));
	_moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state), true);
	_zorder = 1;
	Init();
}

// �X�V
void Enemy::Update(sharedObj plObj)
{	
	if (isAlive())
	{
		if (_status[STATUS::HP] <= 0)
		{
			SetAlive(false);
			(*plObj)._experience[(*plObj)._level] -= _experience[0];

		}
	}

	if (DestroyPrpc())
	{	


		return;
	}
	auto HpRatio = 1.0f * static_cast<float>(_status[STATUS::HP]) / static_cast<float>(_status[STATUS::�ő�HP]);
	Vector2Dbl HpPos = { _pos.x + _size.x / 2 - 30 ,_pos.y - 10 };

	if (_status[STATUS::HP] != _status[STATUS::�ő�HP])
	{ 
		IpSceneMng.AddDrawQue({ IMAGE_ID("�GHP_BAR")[0], {HpPos.x,HpPos.y},{0,0},{1.0f,0.5f},0,1,LAYER::CHAR });
		IpSceneMng.AddDrawQue({ IMAGE_ID("�GHP")[0], {HpPos.x,HpPos.y},{0,0},{HpRatio,0.5f},0,2,LAYER::CHAR });
	}

	
	_moveCtl.Update(plObj);
	
	//TRACE(" %d\n", movetype);

	switch (movetype)
	{
	case MOVE_TYPE::DOWN:
		state(STATE::DOWN);

		_pos.y++;
		break;
	case MOVE_TYPE::LEFT:
		state(STATE::LEFT);

		_pos.x--;
		break;
	case MOVE_TYPE::RIGHT:
		state(STATE::RIGHT);

		_pos.x++;

		break;
	case MOVE_TYPE::UP:
		state(STATE::UP);

		_pos.y--;
		break;
	default:
		break;
	}

}

Enemy::~Enemy()
{
}




bool Enemy::SetAlive(bool alive)
{
	if (!alive)
	{
		// ��ʗh�炵��QUE�𓊂���
		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
	}

	return Obj::SetAlive(alive);
}

// ������
void Enemy::Init(void)
{
	_alive = true;
	_dead = false;
	_unitID = UNIT_ID::ENEMY;
	
	int TYPE = 12 * static_cast<int>(_type);
	AnimVector data;
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 0], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 1], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 2], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 1], 40);
	SetAnim(STATE::DOWN, data);

	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 3], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 4], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 5], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 4], 40);
	SetAnim(STATE::LEFT, data);

	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 6], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 7], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 8], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 7], 40);
	SetAnim(STATE::RIGHT, data);

	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 9], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 10], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 11], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + 10], 40);
	SetAnim(STATE::UP, data);

	for (int i = 0; i < 24; i++)
	{
		data.emplace_back(IMAGE_ID("blast")[i], i);
	}
	data.emplace_back(-1, 35);
	SetAnim(STATE::DETH, data);

	switch (_type)
	{
	case ENEMY_TYPE::�R�E����:
		_status.try_emplace(STATUS::HP, 100);
		_status.try_emplace(STATUS::�ő�HP, 100);
		_experience.try_emplace(0, 30);
		break;
	case ENEMY_TYPE::�X���C��:
		break;
	case ENEMY_TYPE::�I�[�N:
		break;
	case ENEMY_TYPE::�~�m�^�E���X:
		break;
	case ENEMY_TYPE::������:
		break;
	case ENEMY_TYPE::�X�J���}��:
		break;
	case ENEMY_TYPE::�S�[�X�g:
		break;
	case ENEMY_TYPE::����:
		break;
	case ENEMY_TYPE::MAX:
		break;
	default:
		break;
	}


}
