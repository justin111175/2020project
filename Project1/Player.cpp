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
	_zorder = 0;
	Init();
}

// 更新
void Player::Update(sharedObj plObj)
{		
	TRACE("%d\n", Bmax);
	if (DestroyPrpc())
	{
		return;
	}
	if (Bmax < 20)
	{
		if (IpSceneMng.frames() % 60==0)
		{
			Bmax++;
		}
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
			if ((*_input).state(INPUT_ID::P).first && !(*_input).state(INPUT_ID::P).second)
			{
				_posOld = _pos;
				IpSceneMng.AddActQue({ ACT_QUE::LEVELUP , *this });

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
			_select.Updata(IpSceneMng._input, INPUT_ID::RIGHT, SceneSel::Mean, 4, 1);
			_select.Updata(IpSceneMng._input, INPUT_ID::LEFT, SceneSel::Mean, 4, -1);



			if ((*_input).state(INPUT_ID::BTN_1).first && !(*_input).state(INPUT_ID::BTN_1).second)
			{

				if (_select.s_id.Mean == 4)
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

// プレイヤー移動
void Player::PlayerMove(void)
{
	//IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });


	if ((*_input).state(INPUT_ID::BTN_4).first && !(*_input).state(INPUT_ID::BTN_4).second)
	{
		_level.experience[_level.level] -= 30;
		if (_level.experience[_level.level] <= 0)
		{
			_level.level++;
			//_level._status[STATUS::HP] = 100 + (_level._status[STATUS::レベル] * 100)*3/10;


		}

	}

	if ((*_input).state(INPUT_ID::BTN_2).first && !(*_input).state(INPUT_ID::BTN_2).second)
	{
		if (Bmax > 0)
		{
			IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
			Bmax--;

		}
		//_level._statusUp[STATUS_UP::強化_回復]++;
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
		IpSceneMng.mapPos.y++;
	}

	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		state(STATE::DOWN);
		movetype = MOVE_TYPE::DOWN;

		_pos.y += 5;
		IpSceneMng.mapPos.y--;
	}


	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		state(STATE::LEFT);
		movetype = MOVE_TYPE::LEFT;

		_pos.x -= 5;
		IpSceneMng.mapPos.x++;
	}

	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		state(STATE::RIGHT);
		movetype = MOVE_TYPE::RIGHT;

		_pos.x += 5;
		IpSceneMng.mapPos.x--;

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

	for (int x = 1; x <= LevelMax; x++)
	{
		_level.experience[x] = 100 * x;
	}


	number.Init();
	FILE* fp = NULL;
	
	switch (_select.s_id.Title)
	{
	case 0:
		_level.Init();
		break;
	case 1:
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
		IpSceneMng.AddDrawQue({ IMAGE_ID("メニュー")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::MEAN });
		
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 300 ,250,0,0,0.7f,0.7f,0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], 400 ,265,0,0,0.7f,0.7f,0,1,LAYER::MEAN });
		
		IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 350 ,300,0,0,0.7f,0.7f,0,2,LAYER::MEAN });
		IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], 450 ,315,0,0,0.7f,0.7f,0,1,LAYER::MEAN });

		IpSceneMng.AddDrawQue({ IMAGE_ID("メッセージ")[0], 115+255* IpSceneMng.select.s_id.Mean ,385+sin(IpSceneMng.frames()/5)*10.0,0,0,1.0f,1.0f,0,1,LAYER::MEAN });
		
		number.Draw({ 260, 80 }, { 0.4f, 0.3f }, _level.level);
		number.Draw({ 700, 80 }, { 0.4f, 0.3f }, _level._status[STATUS::お金]);
		
		
		number.Draw({ 1150, 280 }, {1.0f, 1.0f }, _level.experience[_level.level]);
		break;
	case MEAN_IN:
		switch (_select.s_id.Mean)
		{
		case ステータス:
			IpSceneMng.AddDrawQue({ IMAGE_ID("ステータス")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("加減")[0], 1010 ,205+ statusupId *53,0,0,1.0f,1.0f,0,1,LAYER::MEAN });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 200 ,150,0,0,0.7f,0.7f,0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("HP")[0], 300 ,165,0,0,0.7f,0.7f,0,1,LAYER::MEAN });

			IpSceneMng.AddDrawQue({ IMAGE_ID("Bar")[0], 250 ,200,0,0,0.7f,0.7f,0,2,LAYER::MEAN });
			IpSceneMng.AddDrawQue({ IMAGE_ID("MP")[0], 350 ,215,0,0,0.7f,0.7f,0,1,LAYER::MEAN });



			IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], 750+sin(IpSceneMng.frames() / 5)*10.0 ,205 + statusupId * 53,0,0,1.0f,1.0f,0,1,LAYER::MEAN });


			number.Draw({ 240,300 }, {0.4f,0.4f},_level._status[STATUS::攻撃力]);
			number.Draw({ 240, 370 }, { 0.4f,0.4f }, _level._status[STATUS::防御力]);
			number.Draw({ 570, 300 }, { 0.4f,0.4f }, _level._status[STATUS::敏捷]);
			number.Draw({ 570, 370 }, { 0.4f,0.4f }, _level._status[STATUS::回復]);
			
			number.Draw({ 1100, 210 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::強化_攻撃力]);
			number.Draw({ 1100, 265 }, { 0.4f,0.4f },_level._statusUp[STATUS_UP::強化_防御力]);
			number.Draw({ 1100, 320 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::強化_敏捷]);
			number.Draw({ 1100, 370 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::強化_回復]);
			number.Draw({ 1100, 425 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::強化_最大HP]);
			number.Draw({ 1100, 480 }, { 0.4f,0.4f }, _level._statusUp[STATUS_UP::強化_最大MP]);
			if (_level._statusUp[STATUS_UP::残るボーナスポイント] >= 10)
			{
				number.Draw({ 1190, 555 }, { 0.5f, 0.5f }, _level._statusUp[STATUS_UP::残るボーナスポイント]);
			}
			else
			{
				number.Draw({ 1175, 555 }, { 0.5f, 0.5f }, _level._statusUp[STATUS_UP::残るボーナスポイント]);
			}

			break;
		case 装備:
			IpSceneMng.AddDrawQue({ IMAGE_ID("装備")[0], 0 ,0,0,0,1.0f,1.0f,0,0,LAYER::MEAN });

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

	_level.Updata();

	auto UpDown = [](std::weak_ptr<InputState> keyData, const INPUT_ID id,Level& _level, const STATUS_UP status_up, const int num) {
	
		if (!keyData.expired())
		{
			if ((*keyData.lock()).state(id).first && !(*keyData.lock()).state(id).second)
			{
				if (_level._statusUp[STATUS_UP::残るボーナスポイント] > 0||num<0)
				{
					if (_level._statusUp[status_up] > 0 || num>0)
					{
						_level._statusUp[status_up] += num;
						_level._statusUp[STATUS_UP::残るボーナスポイント]-=num;

					}
				}

			}
		}
	};

	//FILE* fp = NULL;
	FILE* fp = NULL;

	switch (IpSceneMng.select.s_id.Mean)
	{
	case 0:
		if ((*_input).state(INPUT_ID::UP).first && !(*_input).state(INPUT_ID::UP).second)
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
		if ((*_input).state(INPUT_ID::DOWN).first && !(*_input).state(INPUT_ID::DOWN).second)
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
			UpDown(_input, INPUT_ID::LEFT, _level,強化_攻撃力, -1);
			UpDown(_input, INPUT_ID::RIGHT,_level, 強化_攻撃力,  1);

			break;
		case 強化_防御力:
			UpDown(_input, INPUT_ID::LEFT, _level, 強化_防御力, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, 強化_防御力, 1);
			break;
		case 強化_敏捷:
			UpDown(_input, INPUT_ID::LEFT, _level, 強化_敏捷, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, 強化_敏捷, 1);
			break;
		case 強化_回復:
			UpDown(_input, INPUT_ID::LEFT, _level, 強化_回復, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, 強化_回復, 1);
			break;
		case 強化_最大HP:
			UpDown(_input, INPUT_ID::LEFT, _level, 強化_最大HP, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, 強化_最大HP, 1);
			break;
		case 強化_最大MP:
			UpDown(_input, INPUT_ID::LEFT, _level, 強化_最大MP, -1);
			UpDown(_input, INPUT_ID::RIGHT, _level, 強化_最大MP, 1);
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


		if (fopen_s(&fp, "Dat/player.dat", "wb") == 0)
		{

			fwrite(&_level._statusUp, sizeof(&_level._statusUp), 3, fp);
			fwrite(&_level._status, sizeof(&_level._status), 7, fp);
			fwrite(&_level.level, sizeof(&_level.level), 3, fp);

			
			
			fclose(fp);
		}
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

