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

Player::Player(Vector2Dbl pos, Vector2Dbl size,Vector2Dbl exrate)
{
	_exrate = exrate;
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


	//DrawFormatString(0, 0, GetColor(255, 255, 255), "GameCounter = %d", gameCounter);
	//DrawFormatString(0, 32, GetColor(255, 255, 255), "map : %d,  %d", _pos.x, _pos.y);
	//_dbgDrawFormatString(0, 32, GetColor(255, 255, 255), "map : %d,  %d", _pos.x, _pos.y);
	//_dbgDrawString(0, 0, "map:", GetColor(0, 0, 0));

	//_dbgDrawString(0, 0);
	//	int x, int y, char* String, unsigned int Color
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
		MeanDraw();

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

			}
		}




	}

}

// �v���C���[�ړ�
void Player::PlayerMove(void)
{
	//IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });


	if ((*_input).state(INPUT_ID::BTN_4).first && !(*_input).state(INPUT_ID::BTN_4).second)
	{
		_level.experience[_level.level] -= 30;
		if (_level.experience[_level.level] <= 0)
		{
			_level.level++;
			//_level._status[STATUS::HP] = 100 + (_level._status[STATUS::���x��] * 100)*3/10;


		}

	}




	if ((*_input).state(INPUT_ID::BTN_2).first && !(*_input).state(INPUT_ID::BTN_2).second)
	{
		IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
		_level._statusUp[STATUS_UP::����_��]++;
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

	for (int x = 1; x <= LevelMax; x++)
	{
		_level.experience[x] = 100 * x;
	}


	//FILE* fp = NULL;
	//if (fopen_s(&fp, "Dat/status.dat", "rb") != 0)
	//{	
	//	_level.Init();

	//	////for (int i = 0; i < STATUS::MAX; i++)
	//	////{
	//	//	fread(&_level._status[0], sizeof(&_level._status[0])*7, 1, fp);

	//	////}
	//	//fclose(fp);
	//}
	//else
	//{		
	//	for (int i = 0; i < STATUS::MAX; i++)
	//	{
	//		fread(&_level._status[0], sizeof(&_level._status[0])*i, 1, fp);

	//	}
	//	fclose(fp);
	//}

	//FILE* fp1 = NULL;

	//if (fopen_s(&fp1, "Dat/statusUp.dat", "rb") != 0)
	//{
	//	_level.Init();

	//}
	//else
	//{
	//	for (int i = 0; i < STATUS_UP::����_MAX; i++)
	//	{
	//		fread(&_level._statusUp[0], sizeof(&_level._statusUp[0])*i, 1, fp1);

	//	}
	//	fclose(fp1);
	//}



	


	number.Init();
	FILE* fp = NULL;
	
	switch (_TitleId)
	{
	case TITLE_ID::�V�����Q�[��:
		_level.Init();
		break;
	case TITLE_ID::�f�[�^�ǂݍ���:
		if (fopen_s(&fp, "Dat/player.dat", "rb") != 0)
		{
			_level.Init();
		}
		else
		{

			fread(&_level._statusUp, sizeof(&_level._statusUp), 3, fp);
			fread(&_level._status, sizeof(&_level._status), 7, fp);
			fread(&_level.level, sizeof(&_level.level), 3, fp);




			fclose(fp);

		}
		break;
	default:
		break;
	}



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
		IpSceneMng.AddDrawQue({ IMAGE_ID("���j���[")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::UI });
		
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 300 ,250,0,0,0.7f,0.7f,0,2,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], 400 ,265,0,0,0.7f,0.7f,0,1,LAYER::UI });
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 350 ,300,0,0,0.7f,0.7f,0,2,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], 450 ,315,0,0,0.7f,0.7f,0,1,LAYER::UI });

		IpSceneMng.AddDrawQue({ IMAGE_ID("���b�Z�[�W")[0], 115+255*meanId ,385+sin(IpSceneMng.frames()/5)*10.0,0,0,1.0f,1.0f,0,1,LAYER::UI });
		
		number.Draw({ 260, 80 }, { 0.4f, 0.3f }, _level.level);
		number.Draw({ 700, 80 }, { 0.4f, 0.3f }, _level._status[STATUS::����]);
		
		
		number.Draw({ 1150, 280 }, {1.0f, 1.0f }, _level.experience[_level.level]);

		break;
	case MEAN_IN:
		switch (meanId)
		{
		case �X�e�[�^�X:
			IpSceneMng.AddDrawQue({ IMAGE_ID("�X�e�[�^�X")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::UI });
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], 1010 ,205+ statusupId *53,0,0,1.0f,1.0f,0,1,LAYER::UI });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 200 ,150,0,0,0.7f,0.7f,0,2,LAYER::UI });
			IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], 300 ,165,0,0,0.7f,0.7f,0,1,LAYER::UI });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 250 ,200,0,0,0.7f,0.7f,0,2,LAYER::UI });
			IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], 350 ,215,0,0,0.7f,0.7f,0,1,LAYER::UI });



			IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], 750+sin(IpSceneMng.frames() / 5)*10.0 ,205 + statusupId * 53,0,0,1.0f,1.0f,0,1,LAYER::UI });


			number.Draw({ 240,300 }, {0.4f,0.4f},_level._status[STATUS::�U����]);
			number.Draw({ 240, 370 }, { 0.4f,0.4f }, _level._status[STATUS::�h���]);
			number.Draw({ 570, 300 }, { 0.4f,0.4f }, _level._status[STATUS::�q��]);
			number.Draw({ 570, 370 }, { 0.4f,0.4f }, _level._status[STATUS::��]);
			
			number.Draw({ 1100, 210 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::����_�U����]);
			number.Draw({ 1100, 265 }, { 0.4f,0.4f },_level._statusUp[STATUS_UP::����_�h���]);
			number.Draw({ 1100, 320 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::����_�q��]);
			number.Draw({ 1100, 370 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::����_��]);
			number.Draw({ 1100, 425 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::����_�ő�HP]);
			number.Draw({ 1100, 480 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::����_�ő�MP]);
			if (_level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g] >= 10)
			{
				number.Draw({ 1190, 555 }, { 0.5f, 0.5f }, _level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g]);
			}
			else
			{
				number.Draw({ 1175, 555 }, { 0.5f, 0.5f }, _level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g]);
			}

			break;
		case ����:
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::UI });

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

	_level.Updata();

	auto UpDown = [](std::weak_ptr<InputState> keyData, const INPUT_ID id,Level& _level, const STATUS_UP status_up, const int num) {
	
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
			{
				if (_level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g] > 0||num<0)
				{
					if (_level._statusUp[status_up] > 0 || num>0)
					{
						_level._statusUp[status_up] += num;
						_level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g]-=num;

					}
				}

			}
		}
	};

	//FILE* fp = NULL;
	FILE* fp = NULL;

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
			UpDown(_input, INPUT_ID::LEFT, _level,����_�U����, -1);
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


		if (fopen_s(&fp, "Dat/player.dat", "wb") == 0)
		{

			fwrite(&_level._statusUp, sizeof(&_level._statusUp), 3, fp);
			fwrite(&_level._status, sizeof(&_level._status), 7, fp);
			fwrite(&_level.level, sizeof(&_level.level), 3, fp);

			
			
			fclose(fp);
		}

		break;
	case �I�v�V����:
		break;
	case �Q�[���I��:
		DxLib_End();
		break;
	default:
		break;
	}

}

