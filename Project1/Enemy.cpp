#include "Enemy.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"
#include "SceneMng.h"
#include "GameScene.h"
#include "DxLib.h"
#include "Player.h"
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
	_moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state), true);
	Init();
}

// �X�V
void Enemy::Update(sharedObj plObj)
{
	if (DestroyPrpc())
	{
		return;
	}

	//IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });


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

	AnimVector data;

	data.emplace_back(IMAGE_ID("�����X�^�[����")[12 * static_cast<int>(_type) + 0], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 1], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 2], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 1], 40);
	SetAnim(STATE::DOWN, data);

	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 3], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 4], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 5], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 4], 40);
	SetAnim(STATE::LEFT, data);

	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 6], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 7], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 8], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 7], 40);
	SetAnim(STATE::RIGHT, data);


	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 9], 10);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 10], 20);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 11], 30);
	data.emplace_back(IMAGE_ID("�����X�^�[����")[12* static_cast<int>(_type) + 10], 40);
	SetAnim(STATE::UP, data);

	for (int i = 0; i < 24; i++)
	{
		data.emplace_back(IMAGE_ID("blast")[i], i);
	}
	data.emplace_back(-1, 35);
	SetAnim(STATE::DETH, data);


	//switch (_type)
	//{
	//case ENEMY_TYPE::�R�E����:
	//	data.emplace_back(IMAGE_ID("�����X�^�[����")[0], 10);
	//	data.emplace_back(IMAGE_ID("�����X�^�[����")[1], 20);
	//	data.emplace_back(IMAGE_ID("�����X�^�[����")[2], 30);
	//	data.emplace_back(IMAGE_ID("�����X�^�[����")[1], 40);
	//	data.emplace_back(IMAGE_ID("�����X�^�[����")[0], 50);
	//	SetAnim(STATE::DOWN, data);

	//	break;
	//case ENEMY_TYPE::��ԃX���C��:

	//	data.emplace_back(IMAGE_ID("��ԃX���C��")[2], 30);
	//	data.emplace_back(IMAGE_ID("��ԃX���C��")[1], 60);
	//	SetAnim(STATE::MOVE, data);

	//	data.emplace_back(IMAGE_ID("��ԃX���C��")[0], 5);
	//	data.emplace_back(-1, 10);
	//	SetAnim(STATE::DETH, data);
	//	break;
	//default:
	//	// ���Ȃ��͂�
	//	AST();
	//	break;
	//}


	//state(STATE::MOVE);
}
