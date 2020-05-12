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

// �X�V
void Player::Update()
{		
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

// �v���C���[�ړ�
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

// ������
void Player::Init(void)
{
	_alive = true;
	_dead = false;

	_unitID = UNIT_ID::PLAYER;

	AnimVector data;
	data.emplace_back(IMAGE_ID("�v���C���[")[0], 10);
	data.emplace_back(IMAGE_ID("�v���C���[")[1], 20);
	data.emplace_back(IMAGE_ID("�v���C���[")[2], 30);
	SetAnim(STATE::DOWN, data);	


	data.emplace_back(IMAGE_ID("�v���C���[")[3], 10);
	data.emplace_back(IMAGE_ID("�v���C���[")[4], 20);
	data.emplace_back(IMAGE_ID("�v���C���[")[5], 30);
	SetAnim(STATE::LEFT, data);

	data.emplace_back(IMAGE_ID("�v���C���[")[6], 10);
	data.emplace_back(IMAGE_ID("�v���C���[")[7], 20);
	data.emplace_back(IMAGE_ID("�v���C���[")[8], 30);
	SetAnim(STATE::RIGHT, data);

	data.emplace_back(IMAGE_ID("�v���C���[")[9], 10);
	data.emplace_back(IMAGE_ID("�v���C���[")[10], 20);
	data.emplace_back(IMAGE_ID("�v���C���[")[11], 30);
	SetAnim(STATE::UP, data);


	state(STATE::UP);

}

