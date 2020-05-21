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

Player::Player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	Init();
}

// �X�V
void Player::Update(sharedObj plObj)
{		

	if (DestroyPrpc())
	{
		return;
	}
	TRACE("%d\n", _level.experience[1]);

	(*_input).Update();

	if (!meanFlag)
	{
		if (!LetterFlag)
		{
			PlayerMove();
			if ((*_input).state(INPUT_ID::ESC).first && !(*_input).state(INPUT_ID::ESC).second)
			{
				meanFlag = true;

			}
			if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
			{
				LetterFlag = true;

			}
		}
		else
		{
			if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
			{
				LetterFlag = false;

			}
			letter.LetterDraw();
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

				if (meanId == �Q�[���I��)
				{
					DxLib_End();
				}
				else
				{
					MeanState = MEAN_IN;
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
			StatusUpdate();
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
	//IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });


	if ((*_input).state(INPUT_ID::BTN_4).first && !(*_input).state(INPUT_ID::BTN_4).second)
	{
		_level.experience[_level._status[STATUS::���x��]] -= 30;
		if (_level.experience[_level._status[STATUS::���x��]] <= 0)
		{
			_level._status[STATUS::���x��]++;
			_level._status[STATUS::HP] = 100 + (_level._status[STATUS::���x��] * 100)*0.3;


		}

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
	
	SetAnim(STATE::DETH, data);

	_level.Init();


	number.Init();



	state(STATE::UP);
	_input = std::make_shared<KeyState>();
	meanFlag = false;
	LetterFlag = false;
}

void Player::MeanDraw(void)
{


	switch (MeanState)
	{
	case MEAN_OUT:
		IpSceneMng.AddDrawQue({ IMAGE_ID("���j���[")[0], 0 ,0,0,0,0,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("���b�Z�[�W")[0], 115+255*meanId ,385+sin(IpSceneMng.frames()/5)*10.0,0,0,0,0,LAYER::UI });
		number.Draw(270, 80, _level._status[STATUS::���x��], true);
		number.Draw(700, 80, _level._status[STATUS::����], true);
		
		
		//number.Draw(1150, 320,_level.experience[_level._status[STATUS::���x��]] ,false);

		break;
	case MEAN_IN:
		switch (meanId)
		{
		case �X�e�[�^�X:
			IpSceneMng.AddDrawQue({ IMAGE_ID("�X�e�[�^�X")[0], 0 ,0,0,0,0,0,LAYER::UI });
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], 1010 ,205+ statusupId *53,0,0,0,0,LAYER::UI });
			IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], 750+sin(IpSceneMng.frames() / 5)*10.0 ,205 + statusupId * 53,0,0,0,0,LAYER::UI });

			number.Draw(240, 300,_level._status[STATUS::�U����],true );
			number.Draw(240, 370,_level._status[STATUS::�h���], true);
			number.Draw(570, 300,_level._status[STATUS::�q��], true);
			number.Draw(570, 370,_level._status[STATUS::�q��], true);
			
			number.Draw(1100, 215,_level._statusUp[STATUS_UP::����_�U����], true);
			number.Draw(1100, 270,_level._statusUp[STATUS_UP::����_�h���], true);
			number.Draw(1100, 325,_level._statusUp[STATUS_UP::����_�q��], true);
			number.Draw(1100, 375,_level._statusUp[STATUS_UP::����_��], true);
			number.Draw(1100, 430,_level._statusUp[STATUS_UP::����_�ő�HP], true);
			number.Draw(1100, 480,_level._statusUp[STATUS_UP::����_�ő�MP], true);
			
			number.Draw(1200, 565, _level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g],true);

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


}

void Player::StatusUpdate(void)
{



	auto UpDown = [](std::weak_ptr<InputState> keyData, const INPUT_ID id,level& _level, const STATUS_UP status_up, const int num) {
	
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
			{
				_level._statusUp[status_up] += num;
				_level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g]-=num;
			}
		}
	};


	switch (meanId)
	{
	case �X�e�[�^�X:
		if ((*_input).state(INPUT_ID::UP).first && !(*_input).state(INPUT_ID::UP).second)
		{
			if (statusupId > ����_�U����)
			{
				statusupId = (STATUS_UP)(statusupId - 1);
			}
			else
			{
				statusupId = ����_�ő�MP;
			}
		}
		if ((*_input).state(INPUT_ID::DOWN).first && !(*_input).state(INPUT_ID::DOWN).second)
		{
			if (statusupId < ����_�ő�MP)
			{
				statusupId = (STATUS_UP)(statusupId + 1);
			}
			else
			{
				statusupId = ����_�U����;
			}
		}


		switch (statusupId)
		{
		case ����_�U����:
			UpDown(_input, INPUT_ID::LEFT,  _level,����_�U����, -1);
			UpDown(_input, INPUT_ID::RIGHT,_level, ����_�U����,  1);

			break;
		case ����_�h���:
			UpDown(_input, INPUT_ID::LEFT, _level, ����_�h���, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, ����_�h���, 1);
			break;
		case ����_�q��:
			UpDown(_input, INPUT_ID::LEFT, _level, ����_�q��, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, ����_�q��, 1);
			break;
		case ����_��:
			UpDown(_input, INPUT_ID::LEFT, _level, ����_��, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, ����_��, 1);
			break;
		case ����_�ő�HP:
			UpDown(_input, INPUT_ID::LEFT, _level, ����_�ő�HP, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, ����_�ő�HP, 1);
			break;
		case ����_�ő�MP:
			UpDown(_input, INPUT_ID::LEFT, _level, ����_�ő�MP, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, ����_�ő�MP, 1);
			break;
		case �c��{�[�i�X�|�C���g:
			break;
		default:
			break;
		}

		break;
	case ����:
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

