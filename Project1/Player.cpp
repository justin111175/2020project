#include "Player.h"
#include <ImageMng.h>
#include <Dxlib.h>
#include <GameScene.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>
#include <SceneMng.h>
#include <Obj.h>
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
	_zorder = 0;
	Init();
}

// 更新
void Player::Update(sharedObj plObj)
{		
	if (DestroyPrpc())
	{
		return;
	}

	TRACE("%d\n", _statusUp[STATUS_UP::残るボーナスポイント]);
	

	//TRACE("E:%d\n", _level._statusUp[STATUS_UP::残るボーナスポイント]);
	if (_experience[_level] <= 0)
	{
		_level++;
		//_level._status[STATUS::HP] = 100 + (_level._status[STATUS::レベル] * 100)*3/10;
		_posOld = _pos;
		IpSceneMng.AddActQue({ ACT_QUE::LEVELUP , *this });
	}

	StatusUpdata();

	if (Bmax < 20)
	{
		if (IpSceneMng.frames() % 60==0)
		{
			Bmax++;
		}
	}


	if (!meanFlag)
	{
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
			StatusUpdate();
			if ((*_Input).state(INPUT_ID::ESC).first && !(*_Input).state(INPUT_ID::ESC).second)
			{
				MeanState = ME_ST::MEAN_OUT;

			}
		}




	}

}

// プレイヤー移動
void Player::PlayerMove(void)
{

	
	if ((*_Input).state(INPUT_ID::P).first && !(*_Input).state(INPUT_ID::P).second)
	{
		_experience[_level] -= 30;
	}

	if ((*_Input).state(INPUT_ID::BTN_2).first && !(*_Input).state(INPUT_ID::BTN_2).second)
	{
		if (Bmax > 0)
		{
			IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
			Bmax--;

		}
		//_level._statusUp[STATUS_UP::強化_回復]++;
	}

	if ((*_Input).state(INPUT_ID::BTN_3).first && !(*_Input).state(INPUT_ID::BTN_3).second)
	{
		_posOld = _pos;
		IpSceneMng.AddActQue({ ACT_QUE::SLASH , *this });
	}
	


	if (abs(_pos.x - _mapPos.x) > IpSceneMng.ScreenSize.x/2)
	{
		_mapPos.x-=speed.x;
	}
	if (abs(_pos.y - _mapPos.y) > IpSceneMng.ScreenSize.y/2)
	{
		_mapPos.y -= speed.y;

	}


	speed = { 0,0 };
	if (CheckHitKey(KEY_INPUT_UP))
	{
		state(STATE::UP);
		movetype = MOVE_TYPE::UP;
		speed.y = -4;
		_pos.y += speed.y;
		
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		state(STATE::DOWN);
		movetype = MOVE_TYPE::DOWN;

		speed.y = 4;
		_pos.y += speed.y;
	}


	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		state(STATE::LEFT);
		movetype = MOVE_TYPE::LEFT;

		speed.x = -4;
		_pos.x += speed.x;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		state(STATE::RIGHT);
		movetype = MOVE_TYPE::RIGHT;

		speed.x = 4;
		_pos.x += speed.x;


	}
	



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

	Bmax = 10;
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
	
	SetAnim(STATE::DETH, data);



	
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

void Player::MeanDraw(void)
{


	switch (MeanState)
	{
	case ME_ST::MEAN_OUT:
		IpSceneMng.AddDrawQue({ IMAGE_ID("メニュー")[0], {0 ,0},{0,0},{1.0f,1.0f},0,0,LAYER::MEAN });
		
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {300 ,250},{0,0},{0.7f,0.7f},0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], {400 ,265},{0,0},{0.7f,0.7f},0,1,LAYER::MEAN });
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {350 ,300},{0,0},{0.7f,0.7f},0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], {450 ,315},{0,0},{0.7f,0.7f},0,1,LAYER::MEAN });

		IpSceneMng.AddDrawQue({ IMAGE_ID("メッセージ")[0], {115.0 + 255 * IpSceneMng.select.s_id.Mean ,385 + sin(IpSceneMng.frames() / 5) * 10.0},{0,0},{1.0f,1.0f},0,1,LAYER::MEAN });
		
		number.Draw({ 260, 80 }, { 0.4f, 0.3f }, _level);
		number.Draw({ 700, 80 }, { 0.4f, 0.3f }, _status[STATUS::お金]);
		
		
		number.Draw({ 1150, 280 }, {1.0f, 1.0f }, _experience[_level]);
		break;
	case ME_ST::MEAN_IN:
		switch (_select.s_id.Mean)
		{
		case ステータス:
			IpSceneMng.AddDrawQue({ IMAGE_ID("ステータス")[0],{ 0 ,0},{0,0},{1.0f,1.0f},0,0,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("加減")[0], {1010.0 ,205 + statusupId * 53.0},{0,0},{1.0f,1.0f},0,1,LAYER::MEAN });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {200.0 ,150.0},{0,0},{0.7f,0.7f},0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], {300.0 ,165.0},{0,0},{0.7f,0.7f},0,1,LAYER::MEAN });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], {250.0 ,200.0},{0,0},{0.7f,0.7f},0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], {350.0 ,215.0},{0,0},{0.7f,0.7f},0,1,LAYER::MEAN });



			IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], {750 + sin(IpSceneMng.frames() / 5) * 10.0 ,205 + statusupId * 53.0},{0,0},{1.0f,1.0f},0,1,LAYER::MEAN });

			number.Draw({ 240,300 }, {0.4f,0.4f},_status[STATUS::攻撃力]);
			number.Draw({ 240, 370 }, { 0.4f,0.4f }, _status[STATUS::防御力]);
			number.Draw({ 570, 300 }, { 0.4f,0.4f }, _status[STATUS::敏捷]);
			number.Draw({ 570, 370 }, { 0.4f,0.4f }, _status[STATUS::回復]);
			
			number.Draw({ 1100, 210 }, { 0.4f,0.4f },_statusUp[STATUS_UP::強化_攻撃力]);
			number.Draw({ 1100, 265 }, { 0.4f,0.4f },_statusUp[STATUS_UP::強化_防御力]);
			number.Draw({ 1100, 320 }, { 0.4f,0.4f },_statusUp[STATUS_UP::強化_敏捷]);
			number.Draw({ 1100, 370 }, { 0.4f,0.4f },_statusUp[STATUS_UP::強化_回復]);
			number.Draw({ 1100, 425 }, { 0.4f,0.4f }, _statusUp[STATUS_UP::強化_最大HP]);
			number.Draw({ 1100, 480 }, { 0.4f,0.4f }, _statusUp[STATUS_UP::強化_最大MP]);
			if (_statusUp[STATUS_UP::残るボーナスポイント] >= 10)
			{
				number.Draw({ 1190, 555 }, { 0.5f, 0.5f },_statusUp[STATUS_UP::残るボーナスポイント]);
			}
			else
			{
				number.Draw({ 1175, 555 }, { 0.5f, 0.5f }, _statusUp[STATUS_UP::残るボーナスポイント]);
			}

			break;
		case 装備:
			IpSceneMng.AddDrawQue({ IMAGE_ID("装備")[0], {0 ,0},{0,0},{1.0f,1.0f},0,0,LAYER::MEAN });

			break;
		case 保存:

			break;
		case オプション:
			break;
		case ゲーム終了:
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


	auto UpDown = [](std::weak_ptr<InputState> keyData, const INPUT_ID id,Player& player, const STATUS_UP status_up, const int num) {
		
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
			{
				if (player._statusUp[残るボーナスポイント] > 0||num<0)
				{
					if (player._statusUp[status_up] > 0 || num>0)
					{
						player._statusUp[status_up] += num;
						player._statusUp[残るボーナスポイント]-=num;

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
			if (statusupId > 強化_攻撃力)
			{
				statusupId = (STATUS_UP)(statusupId - 1);
			}
			else
			{
				statusupId = 強化_最大MP;
			}
		}
		if ((*_Input).state(INPUT_ID::DOWN).first && !(*_Input).state(INPUT_ID::DOWN).second)
		{
			if (statusupId < 強化_最大MP)
			{
				statusupId = (STATUS_UP)(statusupId + 1);
			}
			else
			{
				statusupId = 強化_攻撃力;
			}
		}
		switch (statusupId)
		{
		case 強化_攻撃力:
			UpDown(_Input, INPUT_ID::LEFT, *this,強化_攻撃力, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_攻撃力,  1);

			break;
		case 強化_防御力:
			UpDown(_Input, INPUT_ID::LEFT, *this, 強化_防御力, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_防御力, 1);
			break;
		case 強化_敏捷:
			UpDown(_Input, INPUT_ID::LEFT, *this, 強化_敏捷, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_敏捷, 1);
			break;
		case 強化_回復:
			UpDown(_Input, INPUT_ID::LEFT, *this, 強化_回復, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_回復, 1);
			break;
		case 強化_最大HP:
			UpDown(_Input, INPUT_ID::LEFT, *this, 強化_最大HP, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_最大HP, 1);
			break;
		case 強化_最大MP:
			UpDown(_Input, INPUT_ID::LEFT, *this, 強化_最大MP, -1);
			UpDown(_Input, INPUT_ID::RIGHT, *this, 強化_最大MP, 1);
			break;
		case 残るボーナスポイント:
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

void Player::Save(void)
{


	FILE* fp = NULL;
	if (fopen_s(&fp, "player.dat", "wb") == 0)
	{

		for (auto i : _statusUp)
		{
			fwrite(&_statusUp[i.first], sizeof(&_statusUp[i.first]),1, fp);

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
			fread(&_level, sizeof(&_level), 1, fp);

		}
		//fread(&_statusUp[0], sizeof(&_statusUp[0]), _statusUp.size(), fp);


		//fread(&_level._status[0], sizeof(&_level._status[0]), 7, fp);
		//fread(&_level.level, sizeof(&_level.level), 1, fp);

		fclose(fp);
	}



}

void Player::StatusInit(void)
{
	_status.try_emplace(STATUS::HP, 0);
	_status.try_emplace(STATUS::最大HP, 0);
	_status.try_emplace(STATUS::MP, 0);
	_status.try_emplace(STATUS::最大MP, 0);
	_status.try_emplace(STATUS::お金, 0);
	_status.try_emplace(STATUS::攻撃力, 0);
	_status.try_emplace(STATUS::防御力, 0);
	_status.try_emplace(STATUS::敏捷, 0);
	_status.try_emplace(STATUS::回復, 0);

	
	_statusUp.try_emplace(STATUS_UP::強化_攻撃力, 0);
	_statusUp.try_emplace(STATUS_UP::強化_防御力, 0);
	_statusUp.try_emplace(STATUS_UP::強化_敏捷, 0);
	_statusUp.try_emplace(STATUS_UP::強化_回復, 0);
	_statusUp.try_emplace(STATUS_UP::強化_最大HP, 0);
	_statusUp.try_emplace(STATUS_UP::強化_最大MP, 0);
	_statusUp.try_emplace(STATUS_UP::残るボーナスポイント, 10);

	_level = 1;
	for (int x = 1; x < 99; x++)
	{
		_experience[x] = 100 * x;
	}
}

void Player::StatusUpdata(void)
{

	_status[STATUS::最大HP] = 100 + _statusUp[STATUS_UP::強化_最大HP] * 1.3;
	_status[STATUS::最大MP] = 100 + _statusUp[STATUS_UP::強化_最大MP] * 1.3;

}

