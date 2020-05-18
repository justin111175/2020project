#include "Player.h"
#include <ImageMng.h>
#include <Dxlib.h>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>
#include <SceneMng.h>
#include <Obj.h>
#include <algorithm>
#include <KeyState.h>
#include <level.h>

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
void Player::Update(sharedObj plObj)
{		

	TRACE("�ő�HP  %d\n", _level._status[STATUS::HP]);

	(*_input).Update();

	if (!meanFlag)
	{

		PlayerMove();
		if ((*_input).state(INPUT_ID::ESC).first && !(*_input).state(INPUT_ID::ESC).second)
		{
			meanFlag = true;

		}
	}
	else
	{

		if (MeanState == MEAN_OUT)
		{
			if ((*_input).state(INPUT_ID::LEFT).first && !(*_input).state(INPUT_ID::LEFT).second)
			{
				if (meanId > �X�e�[�^�X)
				{
					meanId = (MEAN_ID)(meanId - 1);
				}
				else
				{
					meanId = �Q�[���I��;
				}
			}
			if ((*_input).state(INPUT_ID::RIGHT).first && !(*_input).state(INPUT_ID::RIGHT).second)
			{
				if (meanId < �Q�[���I��)
				{
					meanId = (MEAN_ID)(meanId + 1);
				}
				else
				{
					meanId = �X�e�[�^�X;
				}
			}

			if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
			{
				switch (meanId)
				{
				case �X�e�[�^�X:

					MeanState = MEAN_IN;

					break;
				case ����:
					MeanState = MEAN_IN;

					break;
				case �ۑ�:
					break;
				case �I�v�V����:
					break;
				case �Q�[���I��:
					break;
				default:
					break;
				}
			}

			if ((*_input).state(INPUT_ID::ESC).first && !(*_input).state(INPUT_ID::ESC).second)
			{
				//MeanState = MEAN_OUT;
				meanFlag = false;

			}
		}
		else
		{
			if ((*_input).state(INPUT_ID::ESC).first && !(*_input).state(INPUT_ID::ESC).second)
			{
				MeanState = MEAN_OUT;
				//meanFlag = false;

			}
		}



		MeanDraw();

	}

}

// �v���C���[�ړ�
void Player::PlayerMove(void)
{
	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });


	if ((*_input).state(INPUT_ID::BTN_4).first && !(*_input).state(INPUT_ID::BTN_4).second)
	{
		_level.experience[_level.levelCnt] -= 30;
		if (_level.experience[_level.levelCnt] <= 0)
		{
			_level.levelCnt++;
			_level._status[STATUS::HP] = 100 + (_level.levelCnt * 100)*0.3;


		}

	}

	if (CheckHitKey(KEY_INPUT_Z))
	{
		state(STATE::DETH);

	}

	if ((*_input).state(INPUT_ID::BTN_2).first && !(*_input).state(INPUT_ID::BTN_2).second)
	{
		IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
	}

	if ((*_input).state(INPUT_ID::BTN_3).first && !(*_input).state(INPUT_ID::BTN_3).second)
	{
		_posOld = _pos;
		IpSceneMng.AddActQue({ ACT_QUE::SLASH , *this });
	}

	if (CheckHitKey(KEY_INPUT_UP))
	{
		state(STATE::UP);
		movetype = MOVE_TYPE::UP;
		_pos.y -= 5;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		state(STATE::DOWN);
		movetype = MOVE_TYPE::DOWN;

		_pos.y += 5;
	}


	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		state(STATE::LEFT);
		movetype = MOVE_TYPE::LEFT;

		_pos.x -= 5;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		state(STATE::RIGHT);
		movetype = MOVE_TYPE::RIGHT;

		_pos.x += 5;
	}


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


	data.emplace_back(IMAGE_ID("�v���C���[����")[0], 10);
	data.emplace_back(IMAGE_ID("�v���C���[����")[1], 20);
	data.emplace_back(IMAGE_ID("�v���C���[����")[2], 30);
	data.emplace_back(IMAGE_ID("�v���C���[����")[1], 40);
	SetAnim(STATE::DOWN, data);	


	data.emplace_back(IMAGE_ID("�v���C���[����")[3], 10);
	data.emplace_back(IMAGE_ID("�v���C���[����")[4], 20);
	data.emplace_back(IMAGE_ID("�v���C���[����")[5], 30);
	data.emplace_back(IMAGE_ID("�v���C���[����")[4], 40);
	SetAnim(STATE::LEFT, data);

	data.emplace_back(IMAGE_ID("�v���C���[����")[6], 10);
	data.emplace_back(IMAGE_ID("�v���C���[����")[7], 20);
	data.emplace_back(IMAGE_ID("�v���C���[����")[8], 30);
	data.emplace_back(IMAGE_ID("�v���C���[����")[7], 40);
	SetAnim(STATE::RIGHT, data);

	data.emplace_back(IMAGE_ID("�v���C���[����")[9], 10);
	data.emplace_back(IMAGE_ID("�v���C���[����")[10], 20);
	data.emplace_back(IMAGE_ID("�v���C���[����")[11], 30);
	data.emplace_back(IMAGE_ID("�v���C���[����")[10], 40);
	SetAnim(STATE::UP, data);

	data.emplace_back(IMAGE_ID("�v���C���[����")[0], 10);
	data.emplace_back(IMAGE_ID("�v���C���[����")[1], 20);
	data.emplace_back(IMAGE_ID("�v���C���[����")[2], 30);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	_level.Init();

	state(STATE::UP);
	_input = std::make_shared<KeyState>();
	meanFlag = false;

}

void Player::MeanDraw(void)
{


	switch (MeanState)
	{
	case MEAN_OUT:
		IpSceneMng.AddDrawQue({ IMAGE_ID("���j���[")[0], 0 ,0,0,0,0,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("���b�Z�[�W")[0], 60+161*meanId ,350+sin(IpSceneMng.frames()/5)*10.0,0,0,0,0,LAYER::UI });
		break;
	case MEAN_IN:
		switch (meanId)
		{
		case �X�e�[�^�X:
			IpSceneMng.AddDrawQue({ IMAGE_ID("�X�e�[�^�X")[0], 0 ,0,0,0,0,0,LAYER::UI });
			break;
		case ����:
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], 0 ,0,0,0,0,0,LAYER::UI });

			break;
		case �ۑ�:
			break;
		case �I�v�V����:
			break;
		case �Q�[���I��:
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
	if (MeanState==MEAN_IN)
	{

	}



}

