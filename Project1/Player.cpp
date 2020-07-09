#include "Player.h"
#include <ImageMng.h>
#include <Dxlib.h>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include "_DebugDispOut.h"
#include "SceneMng.h"
#include "KeyState.h"
#include <math.h>
Player::Player()
{
	Init();
}

Player::Player(Vector2Dbl&& pos, Vector2Dbl&& size,Vector2Dbl&& exrate)
{
	_exrate = std::move(exrate);
	_pos = std::move(pos);
	_size = std::move(size);
	_zorder = 0;
	Init();
}

// �X�V
void Player::Update(void)
{		
	if (DestroyPrpc())
	{
		return;
	}
	Repel(_repelFlag);
	
	CameraUpdata();
	
	
	_dbgDrawFormatString(0, 150, 0xFFFFFF, "�v���C���[�̍��W X:%.0f,Y:%.0f", _pos.x,_pos.y);
	_dbgDrawFormatString(0, 200, 0xFFFFFF, "Map�̍��W X:%.0f,Y:%.0f", IpSceneMng.mapPos.x, IpSceneMng.mapPos.y);
	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });




	if (_experience[_level] <= 0)
	{
		_level++;
		//_level._status[STATUS::HP] = 100 + (_level._status[STATUS::���x��] * 100)*3/10;
		_posOld = _pos;
		_statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g] += 5;
		IpSceneMng.AddActQue({ ACT_QUE::LEVELUP , *this });
	}


	StatusData();

	PlayerState();

}

void Player::PlayerState(void)
{
	if (!meanFlag)
	{
		UIDraw();
		if (!LetterFlag)
		{

			PlayerMove();

			if ((*_Input).state(INPUT_ID::ESC).first && !(*_Input).state(INPUT_ID::ESC).second)
			{
				meanFlag = true;

			}
			if ((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second)
			{
				LetterFlag = true;

			}

		}
		else
		{
			if ((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second)
			{
				LetterFlag = false;

			}
			letter.LetterDraw();
		}

	}
	else
	{
		MeanDraw();

		if (MeanState == ME_ST::MEAN_OUT)
		{
			_select.Updata(IpSceneMng._input, INPUT_ID::RIGHT, SceneSel::Mean, 4, 1);
			_select.Updata(IpSceneMng._input, INPUT_ID::LEFT, SceneSel::Mean, 4, -1);



			if ((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second)
			{

				if (_select.s_id.Mean == 4)
				{
					DxLib_End();
				}
				else
				{
					MeanState = ME_ST::MEAN_IN;
				}

			}

			if ((*_Input).state(INPUT_ID::ESC).first && !(*_Input).state(INPUT_ID::ESC).second)
			{
				//MeanState = MEAN_OUT;
				meanFlag = false;

			}
		}
		else
		{
			StatusUpData();
			if ((*_Input).state(INPUT_ID::ESC).first && !(*_Input).state(INPUT_ID::ESC).second)
			{
				MeanState = ME_ST::MEAN_OUT;

			}
		}

	}
}

void Player::CameraUpdata(void)
{

	if (_pos.x + _mapPos.x != IpSceneMng.ScreenSize.x / 2)
	{
		if (_pos.x + _mapPos.x > IpSceneMng.ScreenSize.x / 2)
		{
			if (_mapPos.x >= -IpSceneMng.mapSize.x + IpSceneMng.ScreenSize.x)
			{
				_mapPos.x -= 4;

			}

		}
		if (_pos.x + _mapPos.x < IpSceneMng.ScreenSize.x / 2)
		{
			if (_mapPos.x <= 0)
			{
				_mapPos.x += 4;
			}
		}
	}
	
	if (_pos.y + _mapPos.y != IpSceneMng.ScreenSize.y / 2)
	{
		if (_pos.y + _mapPos.y > IpSceneMng.ScreenSize.y / 2)
		{
			if (_mapPos.y >= (-IpSceneMng.mapSize.y+ IpSceneMng.ScreenSize.y))
			{
				_mapPos.y -= 4;

			}

		}
		
		if(_pos.y + _mapPos.y < IpSceneMng.ScreenSize.y / 2)
		{
			if (_mapPos.y <= 0)
			{
				_mapPos.y += 4;
			}
		}
	}

}

// �v���C���[�ړ�
void Player::PlayerMove(void)
{
	//TRACE("%\n", HpRatio);
	



	if ((*_Input).state(INPUT_ID::P).first && !(*_Input).state(INPUT_ID::P).second)
	{
		if (_status[Status_ID::HP] < _status[Status_ID::�ő�HP])
		{
			_status[Status_ID::HP]+=10;

		}
	}



	if (!_timeCount.GetFlag("�e"))
	{
		if ((*_Input).state(INPUT_ID::BTN_2).first && !(*_Input).state(INPUT_ID::BTN_2).second)
		{

			if (_status[Status_ID::MP] >= BulletCost)
			{			

				if (IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this }))
				{
					_status[Status_ID::MP] -= BulletCost;

					_timeCount.Set("�e",true, 0.5);
				}
			}
		}
	}

	if (!_timeCount.GetFlag("�a��"))
	{
		if ((*_Input).state(INPUT_ID::BTN_3).first && !(*_Input).state(INPUT_ID::BTN_3).second)
		{
			_posOld = _pos;

			if (IpSceneMng.AddActQue({ ACT_QUE::SLASH , *this }))
			{
				_timeCount.Set("�a��", true, 0.5);
			}
		}
	}


	speed = { 0,0 };
	int chipNumber = (_pos.y / 32) * 50 + (static_cast<int>(_pos.x) % 32);
	
	auto movePos = [&](INPUT_ID input,DIR_ID dir,Vector2Dbl speed) {


		if ((*_Input).state(input).first /*&& !(*_Input).state(input).second*/)
		{							
			Player::speed = speed;

			
			if (_dir == dir)
			{
				if (_dirFlag[dir])
				{

					_pos += speed;
				}
			}
			stateDir(STATE::NORMAL, dir);
			IpSceneMng.AddActQue({ ACT_QUE::MOVE , *this });

		}


	};


	movePos(INPUT_ID::UP, DIR_ID::UP, { 0,-4 });
			

	movePos(INPUT_ID::RIGHT, DIR_ID::RIGHT, { 4,0 });

			


	movePos(INPUT_ID::DOWN, DIR_ID::DOWN, { 0,4 });

	movePos(INPUT_ID::LEFT, DIR_ID::LEFT, { -4,0 });
			
	




	
	if (speed.x==0)
	{
		if (speed.y == 0)
		{
			switch (_dir)
			{
			case DIR_ID::DOWN:
				stateDir(STATE::STAY, DIR_ID::DOWN);

				break;
			case DIR_ID::LEFT:
				stateDir(STATE::STAY, DIR_ID::LEFT);

				break;
			case DIR_ID::RIGHT:
				stateDir(STATE::STAY, DIR_ID::RIGHT);

				break;
			case DIR_ID::UP:
				stateDir(STATE::STAY, DIR_ID::UP);

				break;

			default:
				break;
			}
		}

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

	for (auto dir : DIR_ID())
	{
		int dirCnt = static_cast<int>(dir) * 3;
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt+0], 10);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt+1], 20);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt+2], 30);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt+1], 40);
		SetAnim(STATE::NORMAL,dir, data);

		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 0], 10);
		SetAnim(STATE::STAY, dir, data);
		
		_dirFlag.try_emplace(dir, true);

	}


	//data.emplace_back(IMAGE_ID("�v���C���[����")[0], 10);
	//data.emplace_back(IMAGE_ID("�v���C���[����")[1], 20);
	//data.emplace_back(IMAGE_ID("�v���C���[����")[2], 30);
	////SetAnim(STATE::DETH, data);
	//SetAnim(STATE::NORMAL, data);

	number.Init();
	
	switch (_select.s_id.Title)
	{
	case 0:
		StatusInit();
		break;
	case 1:
		Read();

		break;
	default:
		break;
	}
	//state(STATE::UP);
	meanFlag = false;
	LetterFlag = false;
}

void Player::UIDraw(void)
{
	IpSceneMng.AddDrawQue({ IMAGE_ID("UI�w�i")[0], {0 ,0},{0,0},{0.7f,0.25f},false,0,0,LAYER::UI });
	IpSceneMng.AddDrawQue({ IMAGE_ID("�v���C���[����")[0], {220 ,0},{0,0},{2.5f,2.4f},false,0,1,LAYER::UI });


	HpRatio =0.4f* static_cast<float>(_status[Status_ID::HP]) / static_cast<float>(_status[Status_ID::�ő�HP]);
	MpRatio = 0.4f * static_cast<float>(_status[Status_ID::MP]) / static_cast<float>(_status[Status_ID::�ő�MP]);

	IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {20 ,30},{0,0},{0.4f,0.4f},false,0,2,LAYER::UI });
	IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], {78 ,38},{0,0},{ HpRatio,0.3f},false,0,1,LAYER::UI});
	IpSceneMng.AddDrawQue({ "HP     /",{51,23}, {0.6f,0.6f},0,LAYER::UI });
	number.Draw({ 120, 28 }, {0.15f,0.15f }, _status[Status_ID::HP]);
	number.Draw({ 190, 28 }, { 0.15f,0.15f }, _status[Status_ID::�ő�HP]);


	IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {30 ,65},{0,0},{0.4f,0.4f},false,0,2,LAYER::UI });
	IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], {88 ,73},{0,0},{ MpRatio,0.3f},false,0,1,LAYER::UI });
	IpSceneMng.AddDrawQue({ "MP     /",{61,60}, {0.6f,0.6f},0,LAYER::UI});
	number.Draw({ 130, 63 }, { 0.15f,0.15f }, _status[Status_ID::MP]);
	number.Draw({ 200, 63 }, { 0.15f,0.15f }, _status[Status_ID::�ő�MP]);

	IpSceneMng.AddDrawQue({ "G : ",{71,90}, {0.6f,0.6f},0,LAYER::UI });

	number.Draw({ 210, 95 }, { 0.15f,0.15f }, _status[Status_ID::����]);

}	


void Player::MeanDraw(void)
{


	switch (MeanState)
	{
	case ME_ST::MEAN_OUT:
		IpSceneMng.AddDrawQue({ IMAGE_ID("���j���[")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::MEAN });
		
		HpRatio = 0.7f * static_cast<float>(_status[Status_ID::HP]) / static_cast<float>(_status[Status_ID::�ő�HP]);
		MpRatio = 0.7f * static_cast<float>(_status[Status_ID::MP]) / static_cast<float>(_status[Status_ID::�ő�MP]);


		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {300 ,250},{0,0},{0.7f,0.7f},false,0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], {400 ,265},{0,0},{HpRatio,0.6f},false,0,1,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ "HP     /",{350,240}, {1.0f,1.0f},0,LAYER::UI });
		number.Draw({ 480, 240 }, { 0.3f,0.3f }, _status[Status_ID::HP]);
		number.Draw({ 590, 240 }, { 0.3f,0.3f }, _status[Status_ID::�ő�HP]);


		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {350 ,310},{0,0},{0.7f,0.7f},false,0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], {450 ,325},{0,0},{MpRatio,0.6f},false,0,1,LAYER::MEAN });

		IpSceneMng.AddDrawQue({ "MP     /",{400,300}, {1.0f,1.0f},0,LAYER::UI });
		number.Draw({ 530, 300 }, { 0.3f,0.3f }, _status[Status_ID::MP]);
		number.Draw({ 640, 300 }, { 0.3f,0.3f }, _status[Status_ID::�ő�MP]);

		IpSceneMng.AddDrawQue({ IMAGE_ID("���b�Z�[�W")[0], {115 + 255.0 * IpSceneMng.select.s_id.Mean ,385 + sin(IpSceneMng.frames() / 5) * 10.0},{0,0},{1.0f,1.0f},false,0,1,LAYER::MEAN });
		
		number.Draw({ 260, 80 }, { 0.4f, 0.3f }, _level);
		number.Draw({ 700, 80 }, { 0.4f, 0.3f }, _status[Status_ID::����]);
		
		
		number.Draw({ 1150, 280 }, {1.0f, 1.0f }, _experience[_level]);
		break;
	case ME_ST::MEAN_IN:
		switch (_select.s_id.Mean)
		{
		case �X�e�[�^�X:
			IpSceneMng.AddDrawQue({ IMAGE_ID("�X�e�[�^�X")[0],{ 0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], {1010.0 ,205 + static_cast<int>(statusupId) * 53.0},{0,0},{1.0f,1.0f},false,0,1,LAYER::MEAN });

			HpRatio = 0.7f * static_cast<float>(_status[Status_ID::HP]) / static_cast<float>(_status[Status_ID::�ő�HP]);
			MpRatio = 0.7f * static_cast<float>(_status[Status_ID::MP]) / static_cast<float>(_status[Status_ID::�ő�MP]);

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {200 ,150},{0,0},{0.7f,0.7f},false,0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], {300 ,165},{0,0},{HpRatio,0.7f},false,0,1,LAYER::MEAN });
			
			IpSceneMng.AddDrawQue({ "HP     /",{250,145}, {1.0f,1.0f},0,LAYER::UI });
			number.Draw({ 380, 145 }, { 0.3f,0.3f }, _status[Status_ID::HP]);
			number.Draw({ 490, 145 }, { 0.3f,0.3f }, _status[Status_ID::�ő�HP]);



			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {250 ,200},{0,0},{0.7f,0.7f},false,0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], {350 ,215},{0,0},{MpRatio,0.7f},false,0,1,LAYER::MEAN });
			
			IpSceneMng.AddDrawQue({ "MP     /",{300,195}, {1.0f,1.0f},0,LAYER::UI });
			number.Draw({ 430, 195 }, { 0.3f,0.3f }, _status[Status_ID::MP]);
			number.Draw({ 540, 195 }, { 0.3f,0.3f }, _status[Status_ID::�ő�MP]);


			IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], {750 + sin(IpSceneMng.frames() / 5) * 10.0 ,205 + static_cast<int>(statusupId) * 53.0},{0,0},{1.0f,1.0f},false,0,1,LAYER::MEAN });

			number.Draw({ 240,300 }, {0.4f,0.4f},_status[Status_ID::�U����]);
			number.Draw({ 240, 370 }, { 0.4f,0.4f }, _status[Status_ID::�h���]);
			number.Draw({ 570, 300 }, { 0.4f,0.4f }, _status[Status_ID::�q��]);
			number.Draw({ 570, 370 }, { 0.4f,0.4f }, _status[Status_ID::��]);
			
			number.Draw({ 1100, 210 }, { 0.4f,0.4f },_statusUp[Status_Up_ID::�U����]);
			number.Draw({ 1100, 265 }, { 0.4f,0.4f },_statusUp[Status_Up_ID::�h���]);
			number.Draw({ 1100, 320 }, { 0.4f,0.4f },_statusUp[Status_Up_ID::�q��]);
			number.Draw({ 1100, 370 }, { 0.4f,0.4f },_statusUp[Status_Up_ID::��]);
			number.Draw({ 1100, 425 }, { 0.4f,0.4f }, _statusUp[Status_Up_ID::�ő�HP]);
			number.Draw({ 1100, 480 }, { 0.4f,0.4f }, _statusUp[Status_Up_ID::�ő�MP]);
			if (_statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g] >= 10)
			{
				number.Draw({ 1190, 555 }, { 0.5f, 0.5f },_statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g]);
			}
			else
			{
				number.Draw({ 1175, 555 }, { 0.5f, 0.5f }, _statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g]);
			}

			break;
		case ����:
			IpSceneMng.AddDrawQue({ IMAGE_ID("����")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::MEAN });

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

void Player::StatusUpData(void)
{


	auto UpDown = [&](std::weak_ptr<InputState> keyData, const INPUT_ID id, const Status_Up_ID status_up, const int num) {
		
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
			{
				if (_statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g] > 0||num<0)
				{
					if (_statusUp[status_up] > 0 || num>0)
					{
						_statusUp[status_up] += num;
						_statusUp[Status_Up_ID::�c��{�[�i�X�|�C���g]-=num;

					}
				}

			}
		}
	};
	

	switch (IpSceneMng.select.s_id.Mean)
	{
	case 0:
		if ((*_Input).state(INPUT_ID::UP).first && !(*_Input).state(INPUT_ID::UP).second)
		{
			if (statusupId > Status_Up_ID::�U����)
			{
				statusupId = (Status_Up_ID)(static_cast<int>(statusupId) - 1);
			}
			else
			{
				statusupId = Status_Up_ID::�ő�MP;
			}
		}
		if ((*_Input).state(INPUT_ID::DOWN).first && !(*_Input).state(INPUT_ID::DOWN).second)
		{
			if (statusupId < Status_Up_ID::�ő�MP)
			{
				statusupId = (Status_Up_ID)(static_cast<int>(statusupId) + 1);
			}
			else
			{
				statusupId = Status_Up_ID::�U����;
			}
		}
		switch (statusupId)
		{
		case Status_Up_ID::�U����:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::�U����, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::�U����,  1);

			break;
		case Status_Up_ID::�h���:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::�h���, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::�h���, 1);
			break;
		case Status_Up_ID:: �q��:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::�q��, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::�q��, 1);
			break;
		case Status_Up_ID::��:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::��, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::��, 1);
			break;
		case Status_Up_ID::�ő�HP:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::�ő�HP, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::�ő�HP, 1);
			break;
		case Status_Up_ID::�ő�MP:
			UpDown(_Input, INPUT_ID::LEFT, Status_Up_ID::�ő�MP, -1);
			UpDown(_Input, INPUT_ID::RIGHT, Status_Up_ID::�ő�MP, 1);
			break;
		case Status_Up_ID::�c��{�[�i�X�|�C���g:
			break;
		default:
			break;
		}
		break;
	case 1:
		break;
	case 2:

		Save();

		MeanState = ME_ST::MEAN_OUT;
		meanFlag = false;
		break;
	case 3:
		break;
	case 4:
		DxLib_End();
		break;
	default:
		break;
	}




}

void Player::Repel(bool& repel)
{
	if (repel)
	{

		Vector2Dbl test = (_funcPos - _pos);
		_pos += (-test);
		//switch (_funcDir)
		//{
		//case DIR_ID::DOWN:
		//	_pos.y-=50;
		//	break;
		//case DIR_ID::LEFT:
		//	_pos.x+=50;
		//	break;
		//case DIR_ID::RIGHT:
		//	_pos.x-=50;
		//	break;
		//case DIR_ID::UP:
		//	_pos.y+=50;
		//	break;

		//default:
		//	break;
		//}

		repel = false;


	}

	



	
	//for (int t = 0; t < 50; t++)
	//{

	//	_pos.x += (3 * cos(90) * t)/100;
	//	_pos.y += (3 * sin(90) * t - (1 / 2) * 3 * t * t)/100;

	//}
}

void Player::Save(void)
{


	FILE* fp = NULL;
	if (fopen_s(&fp, "player.dat", "wb") == 0)
	{

		for (auto i : _statusUp)
		{
			fwrite(&_statusUp[i.first], sizeof(&_statusUp[i.first]),1, fp);

		}
		for (auto i : _status)
		{
			fwrite(&_status[i.first], sizeof(&_status[i.first]), 1, fp);
		}
		fwrite(&_level, sizeof(&_level), 1, fp);

		//fwrite(&_level._status[0], sizeof(&_level._status[0])*7, 1, fp);
		//fwrite(&_level.level, sizeof(&_level.level), 1, fp);
		fclose(fp);


	}
}

void Player::Read(void)
{
	StatusInit();

	FILE* fp = NULL;
	if (fopen_s(&fp, "player.dat", "rb") == 0)
	{

		for (auto i : _statusUp)
		{
			fread(&_statusUp[i.first], sizeof(&_statusUp[i.first]), 1, fp);

		}
		for (auto i : _status)
		{
			fread(&_status[i.first], sizeof(&_status[i.first]), 1, fp);
		}
		fread(&_level, sizeof(&_level), 1, fp);


		fclose(fp);
	}



}

void Player::StatusData(void)
{
	_status[Status_ID::�ő�HP] = static_cast<int>(100 + _statusUp[Status_Up_ID::�ő�HP] * 1.3);
	_status[Status_ID::�ő�MP] = static_cast<int>(100 + _statusUp[Status_Up_ID::�ő�MP] * 1.3);
	_status[Status_ID::��] = static_cast<int>(5 + _statusUp[Status_Up_ID::��] * 1.3);

	if (IpSceneMng.frames() % 60==1)
	{
		if (_status[Status_ID::MP]+ _status[Status_ID::��] < _status[Status_ID::�ő�MP])
		{
			_status[Status_ID::MP] += _status[Status_ID::��];

		}
		else
		{
			_status[Status_ID::MP] = _status[Status_ID::�ő�MP];
		}

	}

}

void Player::StatusInit(void)
{
	_status.try_emplace(Status_ID::HP, 0);
	_status.try_emplace(Status_ID::�ő�HP, 0);
	_status.try_emplace(Status_ID::MP, 0);
	_status.try_emplace(Status_ID::�ő�MP, 0);
	_status.try_emplace(Status_ID::����, 99999);
	_status.try_emplace(Status_ID::�U����, 0);
	_status.try_emplace(Status_ID::�h���, 0);
	_status.try_emplace(Status_ID::�q��, 0);
	_status.try_emplace(Status_ID::��, 0);

	
	_statusUp.try_emplace(Status_Up_ID::�U����, 0);
	_statusUp.try_emplace(Status_Up_ID::�h���, 0);
	_statusUp.try_emplace(Status_Up_ID::�q��, 0);
	_statusUp.try_emplace(Status_Up_ID::��, 0);
	_statusUp.try_emplace(Status_Up_ID::�ő�HP, 0);
	_statusUp.try_emplace(Status_Up_ID::�ő�MP, 0);
	_statusUp.try_emplace(Status_Up_ID::�c��{�[�i�X�|�C���g, 10);
	
	for (int x = 1; x < 99; x++)
	{	
		_experience.try_emplace(x, 100 * x);

	}

	_level = 1;
	
	_status[Status_ID::�ő�HP] = static_cast<int>(100 + _statusUp[Status_Up_ID::�ő�HP] * 1.3);

	_status[Status_ID::�ő�MP] = static_cast<int>(100 + _statusUp[Status_Up_ID::�ő�MP] * 1.3);
	_status[Status_ID::��] = static_cast<int>(5 + _statusUp[Status_Up_ID::��] * 1.3);

	_status[Status_ID::HP] = _status[Status_ID::�ő�HP];
	_status[Status_ID::MP] = _status[Status_ID::�ő�MP];
}



