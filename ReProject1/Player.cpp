#include "Player.h"
#include <Dxlib.h>
#include "common/Input/KeyInput.h"
#include "common/ImageMng.h"
#include "Scene/SceneMng.h"
#include "common/_debug/_DebugDispOut.h"

Player::Player()
{
	Init();
}

Player::Player(Vector2&& pos, Vector2Dbl&& size, Vector2Dbl&& exrate)
{
	_pos = std::move(pos);
	_size = std::move(size);
	_exrate = std::move(exrate);

	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{	
	//_dbgDrawFormatString(0, 50, 0xFFFFFF, "プレイヤーの座標 X:%d,Y:%d", _pos.x, _pos.y);
	//_dbgDrawFormatString(0, 100, 0xFFFFFF, "Mapの座標 X:%f,Y:%f", IpSceneMng.mapPos.x, IpSceneMng.mapPos.y);

	if (!_meanFlag)
	{
		Move();

	}
	else
	{
		auto size = { 0.5f,0.5f };
		
		auto Pos = [&](MeanID id) {

			return Vector2(50, 120 + mean_size_Y * static_cast<int>(id));
		};

		IpSceneMng.AddDrawQue({ "ステータス",Pos(MeanID::ステータス), { 0.5f,0.5f },0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "保存",Pos(MeanID::保存), { 0.5f,0.5f },0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "終了",Pos(MeanID::終了),{ 0.5f,0.5f },0,LAYER::UI });


	

		IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {20,100}, { 0,0 }, {0.5f,0.5f }, false, 0, 0, LAYER::UI });
		
		
		if (meanState_ == MeanState::外)
		{		


			IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {30,120 + 40*static_cast<int>(meanID_)}, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });

		}
		
		if (meanState_ == MeanState::中)
		{
			auto Pos = [&](Vector2 pos) {

				return Vector2(200 + pos.x, 140 + 30 * pos.y);
			};

			switch (meanID_)
			{
			case MeanID::ステータス:
				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {170,100}, { 0,0 }, {1.0f,1.4f}, false, 0, 0, LAYER::UI });
				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {470,100}, { 0,0 }, {1.0f,0.8f}, false, 0, 0, LAYER::UI });
				
				IpSceneMng.AddDrawQue({ "レベル　 　   -> ",{200,155},{0.5,0.5},0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "経験値　 　   -> ",{200,185},{0.5,0.5},0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "必要量",{200,215},{0.5,0.5},0,LAYER::UI });

				//IpSceneMng.AddDrawQue({ "HP:     / ",{200,180},{0.5,0.5 },0,LAYER::UI });
				//IpSceneMng.AddDrawQue({ "MP:     / ",{200,200},{0.5,0.5 },0,LAYER::UI });
				
				
				IpSceneMng.AddDrawQue({ "体力",{220,265},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "持久力",{220,295},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "筋力",{220,325},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "敏捷",{220,355},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "回復",{220,385},{0.5,0.5 },0,LAYER::UI });
				
				IpSceneMng.AddDrawQue({ "HP           ->",{490,155},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "スタミナ      ->",{490,185},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "攻撃力        ->",{490,215},{0.5,0.5 },0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "防御力        ->",{490,245},{0.5,0.5 },0,LAYER::UI });
				
				
				number.Draw({ 330, 155 }, { 0.2f,0.2f }, _level,0);
				number.Draw({ 430, 155 }, { 0.2f,0.2f }, _level, 0);
				number.Draw({ 330, 185 }, { 0.2f,0.2f }, _experience[0], 0);
				number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 0);
				number.Draw({ 430, 215 }, { 0.2f,0.2f }, _experience[_level], 0);
				
				number.Draw({ 430, 265 }, { 0.2f,0.2f }, _status[Status_ID::体力], 0);
				number.Draw({ 430, 295 }, { 0.2f,0.2f }, _status[Status_ID::持久力], 0);
				number.Draw({ 430, 325 }, { 0.2f,0.2f }, _status[Status_ID::筋力], 0);
				number.Draw({ 430, 355 }, { 0.2f,0.2f }, _status[Status_ID::敏捷], 0);
				number.Draw({ 430, 385 }, { 0.2f,0.2f }, _status[Status_ID::回復], 1);


				IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {200,265+30* (static_cast<int>(status_)-4) }, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });


				break;
			case MeanID::保存:
				break;
			case MeanID::終了:
				DxLib_End();
				break;

			default:
				break;
			}

		}

		for (auto data : controller->GetCntData())
		{
			if (data.second[static_cast<int>(Trg::Now)]&&!data.second[static_cast<int>(Trg::Old)])
			{

				MeanCtl(data.first);
			}
		}

	}
	


	


	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	(*controller)();
	
	Camera();

}


void Player::SetDir(InputID id)
{	
	//_runFlag = true;
	switch (id)
	{
	case InputID::Up:
		stateDir(STATE::NORMAL, DIR_ID::UP);

		if (_pData._bit.UP)
		{
			_runFlag = true;

		}
		break;
	case InputID::Down:
		stateDir(STATE::NORMAL, DIR_ID::DOWN);

		if (_pData._bit.DOWN)
		{
			_runFlag = true;

		}

		break;
	case InputID::Left:
			stateDir(STATE::NORMAL, DIR_ID::LEFT);

		if (_pData._bit.LEFT)
		{
			_runFlag = true;

		}
		break;
	case InputID::Right:
					stateDir(STATE::NORMAL, DIR_ID::RIGHT);

		if (_pData._bit.RIGHT)
		{
			_runFlag = true;

		}
		break;

	default:
		break;
	}

	
}

void Player::MeanCtl(InputID id)
{
	if (meanState_ == MeanState::外)
	{
		switch (id)
		{
		case InputID::Up:

			if (meanID_ > MeanID::ステータス)
			{
				meanID_ = (MeanID)(static_cast<int>(meanID_) - 1);

			}
			else
			{
				meanID_ = MeanID::終了;
			}
			break;
		case InputID::Down:
			if (meanID_ < MeanID::終了)
			{
				meanID_ = (MeanID)(static_cast<int>(meanID_) + 1);

			}
			else
			{
				meanID_ = MeanID::ステータス;
			}
			break;
		case InputID::Left:
			break;
		case InputID::Right:
			break;
		case InputID::Z:
			if (meanState_ == MeanState::外)
			{
				meanState_ = MeanState::中;
			}
			break;
		case InputID::Esc:

			if (meanState_ == MeanState::外)
			{
				_meanFlag = false;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		switch (id)
		{
		case InputID::Up:
			if (status_ > Status_ID::体力)
			{
				status_ = (Status_ID)(static_cast<int>(status_) - 1);

			}
			else
			{
				status_ = Status_ID::回復;
			}

			break;
		case InputID::Down:
			if (status_ < Status_ID::回復)
			{
				status_ = (Status_ID)(static_cast<int>(status_) + 1);

			}
			else
			{
				status_ = Status_ID::体力;
			}

			break;
		case InputID::Left:
			_status[status_] -= 1;
			break;
		case InputID::Right:
			_status[status_] += 1;

			break;
		case InputID::Z:

			break;
		case InputID::Esc:
			if (meanState_ == MeanState::中)
			{
				meanState_ = MeanState::外;
			}

			break;
		default:
			break;
		}
	}

}

void Player::Move(void)
{
	
	_pData._bit = { 1,1,1,1 };
	//_runFlag = false;

	if (static_cast<int>(_pos.x % 32) == 0)
	{
		if (static_cast<int>(_pos.y % 32) == 0)
		{
			_runFlag = false;

		}
	}

	auto CheckMove = [&](int no) {
		Vector2	Pos = { static_cast<int>((_pos.x + _size.x - 4) / 32),static_cast<int>(_pos.y / 32) };

		if (IpSceneMng._data[Pos.y][Pos.x - 1] == no)
		{
			_pData._bit.LEFT = 0;
			return true;
		}

		Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y - 4) / 32) };
		if (IpSceneMng._data[Pos.y - 1][Pos.x] == no)
		{
			_pData._bit.UP = 0;
			return true;

		}

		Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
		if (IpSceneMng._data[Pos.y][Pos.x + 1] == no)
		{
			_pData._bit.RIGHT = 0;
			return true;

		}
		if (IpSceneMng._data[Pos.y + 1][Pos.x] == no)
		{
			_pData._bit.DOWN = 0;
			return true;
		}
		return false;

	};


	for (auto data : controller->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)])
		{
			CheckMove(1);
			
			if (CheckMove(3))
			{
				if (data.first==InputID::Z)
				{
					if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
					{

						_meanFlag = true;
					}
				}

			}



			if (static_cast<int>(_pos.x % 32) == 0)
			{
				if (static_cast<int>(_pos.y % 32) == 0)
				{
					SetDir(data.first);

				}
			}

		}
	}




	if (_runFlag)
	{
		switch (_dir)
		{
		case DIR_ID::DOWN:
			if (_pData._bit.DOWN)
			{
				_pos.y += 4;
			}
			break;
		case DIR_ID::LEFT:
			if (_pData._bit.LEFT)
			{
				_pos.x -= 4;
			}
			break;
		case DIR_ID::RIGHT:
			if (_pData._bit.RIGHT)
			{
				_pos.x += 4;
			}
			break;
		case DIR_ID::UP:
			if (_pData._bit.UP)
			{
				_pos.y -= 4;
			}
			break;

		default:
			break;
		}
	}
	else
	{
		switch (_dir)
		{
		case DIR_ID::UP:
			stateDir(STATE::STAY, DIR_ID::UP);


			break;
		case DIR_ID::DOWN:
			stateDir(STATE::STAY, DIR_ID::DOWN);

			break;
		case DIR_ID::RIGHT:
			stateDir(STATE::STAY, DIR_ID::RIGHT);

			break;
		case DIR_ID::LEFT:
			stateDir(STATE::STAY, DIR_ID::LEFT);

			break;
		default:
			break;
		}

	}


}






void Player::Init(void)
{

	controller = std::make_unique<KeyInput>();
	controller->SetUp();
	for (auto dir : DIR_ID())
	{
		_dirFlag[dir] = true;

	}
	_alive = true;
	_dead = false;
	_runFlag = false;
	_meanFlag = false;
	
	meanState_ = MeanState::外;
	status_ = Status_ID::体力;

	number.Init();

	_unitID = UNIT_ID::PLAYER;



	AnimVector data;

	for (auto dir : DIR_ID())
	{
		int dirCnt = static_cast<int>(dir) * 3;
		data.emplace_back(IMAGE_ID("プレイヤー歩く")[(__int64)dirCnt + 0], 10);
		data.emplace_back(IMAGE_ID("プレイヤー歩く")[(__int64)dirCnt + 1], 20);
		data.emplace_back(IMAGE_ID("プレイヤー歩く")[(__int64)dirCnt + 2], 30);
		data.emplace_back(IMAGE_ID("プレイヤー歩く")[(__int64)dirCnt + 1], 40);
		SetAnim(STATE::NORMAL, dir, data);

		data.emplace_back(IMAGE_ID("プレイヤー歩く")[(__int64)dirCnt + 0], 10);
		SetAnim(STATE::STAY, dir, data);

		//_dirFlag.try_emplace(dir, true);

	}
	
	//if (meanType.size() == 0)
	//{
	//	meanType.emplace_back("ステータス");
	//	meanType.emplace_back("保存");
	//	meanType.emplace_back("終了");

	//}
	StateInit();

	//data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[0], 10);
	//data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[1], 20);
	//data.emplace_back(IMAGE_ID("プレイヤー死ぬ")[2], 30);
	////SetAnim(STATE::DETH, data);
	SetAnim(STATE::NORMAL, DIR_ID::DOWN,data);




}

void Player::Camera(void)
{
	Vector2Dbl tmp = IpSceneMng.mapPos;

	if (_pos.x - tmp.x > IpSceneMng.ScreenSize.x / 2)
	{
		if (tmp.x < IpSceneMng.mapSize.x - IpSceneMng.ScreenSize.x)
		{
			IpSceneMng.mapPos.x += 4;
		}
		else
		{

			IpSceneMng.mapPos.x = IpSceneMng.mapSize.x - IpSceneMng.ScreenSize.x;
		}
	}
	if (_pos.x - tmp.x < IpSceneMng.ScreenSize.x / 2)
	{
		if (tmp.x > 0)
		{
			IpSceneMng.mapPos.x -= 4;
		}
		else
		{
			IpSceneMng.mapPos.x = 0;
		}
	}

	if (_pos.y - IpSceneMng.mapPos.y > IpSceneMng.ScreenSize.y / 2)
	{
		if (tmp.y < IpSceneMng.mapSize.y - IpSceneMng.ScreenSize.y)
		{
			IpSceneMng.mapPos.y += 4;
		}
		else
		{

			IpSceneMng.mapPos.y = IpSceneMng.mapSize.y - IpSceneMng.ScreenSize.y;
		}
	}

	if (_pos.y - tmp.y < IpSceneMng.ScreenSize.y / 2)
	{
		if (tmp.y > 0)
		{
			IpSceneMng.mapPos.y -= 4;
		}
		else
		{
			IpSceneMng.mapPos.y = 0;
		}
	}
}

void Player::StateInit(void)
{
	if (_status.size()==0)
	{
		_status.try_emplace(Status_ID::HP, 0);
		_status.try_emplace(Status_ID::最大HP, 0);
		_status.try_emplace(Status_ID::MP, 0);
		_status.try_emplace(Status_ID::最大MP, 0);
		
		_status.try_emplace(Status_ID::体力, 1);
		_status.try_emplace(Status_ID::持久力,2);
		_status.try_emplace(Status_ID::筋力, 3);
		_status.try_emplace(Status_ID::敏捷, 4);
		_status.try_emplace(Status_ID::回復, 5);



	}
	

	for (int x = 0; x < 99; x++)
	{
		_experience.try_emplace(x, 100 * x);

	}
	
	_level = 1;

}
