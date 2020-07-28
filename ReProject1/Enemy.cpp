#include "Enemy.h"
#include "common/ImageMng.h"
#include "common/_debug/_DeBugConOut.h"
#include "Scene/SceneMng.h"
#include "Scene/GameScene.h"
#include "DxLib.h"
#include "Obj.h"
#include "common/TimeCount.h"


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
void Enemy::Update(void)
{	
	if (isAlive())
	{
		if (_status[Status_ID::HP] <= 0)
		{
			SetAlive(false);
			//(*plObj)._experience[(*plObj)._level] -= _experience[0];

		}
	}	
	
	if (DestroyPrpc())
	{	

		return;
	}
	//IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });



	//auto HpRatio = 1.0f * static_cast<float>(_status[Status_ID::HP]) / static_cast<float>(_status[Status_ID::�ő�HP]);
	//Vector2Dbl HpPos = { _pos.x + _size.x / 2 - 30 ,_pos.y - 10 };

	//if (_status[Status_ID::HP] != _status[Status_ID::�ő�HP])
	//{ 
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�GHP_BAR")[0], {HpPos.x,HpPos.y},{0,0},{1.0f,0.5f},false,0,1,LAYER::CHAR });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�GHP")[0], {HpPos.x,HpPos.y},{0,0},{HpRatio,0.5f},false,0,2,LAYER::CHAR });
	//}

	
	_moveCtl.Update();
	
	switch (_dir)
	{
	case DIR_ID::DOWN:
		stateDir(STATE::NORMAL, DIR_ID::DOWN);
		break;
	case DIR_ID::LEFT:
		stateDir(STATE::NORMAL, DIR_ID::LEFT);
		break;
	case DIR_ID::RIGHT:
		stateDir(STATE::NORMAL, DIR_ID::RIGHT);
		break;
	case DIR_ID::UP:
		stateDir(STATE::NORMAL, DIR_ID::UP);
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
	for (auto dir : DIR_ID())
	{
		int dirCnt = static_cast<int>(dir) * 3;
		data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + dirCnt+0], 10);
		data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + dirCnt+1], 20);
		data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + dirCnt+2], 30);
		data.emplace_back(IMAGE_ID("�����X�^�[����")[(__int64)TYPE + dirCnt+1], 40);
		
		SetAnim(STATE::NORMAL, dir, data);
		
		for (int i = 0; i < 24; i++)
		{
			data.emplace_back(IMAGE_ID("blast")[i], i);
		}
		data.emplace_back(-1, 25);
		SetAnim(STATE::DETH, dir, data);

	}



	switch (_type)
	{
	case ENEMY_TYPE::�R�E����:
		_status.try_emplace(Status_ID::HP, 100);
		//_status.try_emplace(Status_ID::�ő�HP, 100);
		_experience.try_emplace(0, 30);
		break;
	case ENEMY_TYPE::�X���C��:
		break;
	case ENEMY_TYPE::�I�[�N:
		_status.try_emplace(Status_ID::HP, 100);
		//_status.try_emplace(Status_ID::�ő�HP, 100);
		_experience.try_emplace(0, 30);
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
