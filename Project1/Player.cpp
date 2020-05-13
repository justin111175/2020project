#include "Player.h"
#include <ImageMng.h>
#include <Dxlib.h>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>
#include <SceneMng.h>
#include <Obj.h>
#include <algorithm>
Player::Player()
{
	Init();
}

Player::Player(Vector2Dbl pos, Vector2 size)
{
	_pos = pos;
	_size = size;
	Init();
}

// 更新
void Player::Update()
{		
	if (CheckHitKey(KEY_INPUT_Z))
	{
		state(STATE::DETH);

	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		state(STATE::UP);
		_pos.y-=5;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		state(STATE::DOWN);
		_pos.y+=5;
	}
	

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		state(STATE::LEFT);
		_pos.x-=5;
	}
	
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		state(STATE::RIGHT);
		_pos.x+=5;
	}


}

// プレイヤー移動
void Player::PlayerMove(void)
{
}

Player::~Player()
{
}


bool Player::SetAlive(bool alive)
{
	return Obj::SetAlive(alive);
}

// 初期化
void Player::Init(void)
{
	_alive = true;
	_dead = false;

	_unitID = UNIT_ID::PLAYER;

	AnimVector data;


	data.emplace_back(IMAGE_ID("プレイヤー歩く")[0], 10);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[1], 20);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[2], 30);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[1], 40);
	SetAnim(STATE::DOWN, data);	


	data.emplace_back(IMAGE_ID("プレイヤー歩く")[3], 10);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[4], 20);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[5], 30);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[4], 40);
	SetAnim(STATE::LEFT, data);

	data.emplace_back(IMAGE_ID("プレイヤー歩く")[6], 10);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[7], 20);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[8], 30);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[7], 40);
	SetAnim(STATE::RIGHT, data);

	data.emplace_back(IMAGE_ID("プレイヤー歩く")[9], 10);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[10], 20);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[11], 30);
	data.emplace_back(IMAGE_ID("プレイヤー歩く")[10], 40);
	SetAnim(STATE::UP, data);

	data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[0], 10);
	data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[1], 20);
	data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[2], 30);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);


	state(STATE::UP);

}

