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

// 更新
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
	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });



	//auto HpRatio = 1.0f * static_cast<float>(_status[Status_ID::HP]) / static_cast<float>(_status[Status_ID::最大HP]);
	//Vector2Dbl HpPos = { _pos.x + _size.x / 2 - 30 ,_pos.y - 10 };

	//if (_status[Status_ID::HP] != _status[Status_ID::最大HP])
	//{ 
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("敵HP_BAR")[0], {HpPos.x,HpPos.y},{0,0},{1.0f,0.5f},false,0,1,LAYER::CHAR });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("敵HP")[0], {HpPos.x,HpPos.y},{0,0},{HpRatio,0.5f},false,0,2,LAYER::CHAR });
	//}
	if (_type == ENEMY_TYPE::オーク)
	{
		if (rand() % 10==0)
		{
			IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });

		}

	}

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
		// 画面揺らしのQUEを投げる
		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
	}

	return Obj::SetAlive(alive);
}

// 初期化
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
		data.emplace_back(IMAGE_ID("モンスター歩く")[(__int64)TYPE + dirCnt+0], 10);
		data.emplace_back(IMAGE_ID("モンスター歩く")[(__int64)TYPE + dirCnt+1], 20);
		data.emplace_back(IMAGE_ID("モンスター歩く")[(__int64)TYPE + dirCnt+2], 30);
		data.emplace_back(IMAGE_ID("モンスター歩く")[(__int64)TYPE + dirCnt+1], 40);
		
		SetAnim(STATE::NORMAL, dir, data);
		
		for (int i = 0; i < 24; i++)
		{
			data.emplace_back(IMAGE_ID("blast")[i], i);
		}
		data.emplace_back(-1, 25);
		SetAnim(STATE::DETH, dir, data);

	}
	enemyMode_ = EnemyMode::自由移動;



	switch (_type)
	{
	case ENEMY_TYPE::コウモリ:
		_status.try_emplace(Status_ID::HP, 100);
		//_status.try_emplace(Status_ID::最大HP, 100);
		_experience.try_emplace(0, 30);
		break;
	case ENEMY_TYPE::スライム:
		break;
	case ENEMY_TYPE::オーク:
		_status.try_emplace(Status_ID::HP, 100);
		//_status.try_emplace(Status_ID::最大HP, 100);
		_experience.try_emplace(0, 30);
		break;
	case ENEMY_TYPE::ミノタウロス:
		break;
	case ENEMY_TYPE::小悪魔:
		break;
	case ENEMY_TYPE::スカルマン:
		break;
	case ENEMY_TYPE::ゴースト:
		break;
	case ENEMY_TYPE::魔族:
		break;
	case ENEMY_TYPE::MAX:
		break;
	default:
		break;
	}


}
