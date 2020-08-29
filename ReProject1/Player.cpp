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

Player::Player(Vector2&& pos, Vector2&& size, Vector2Dbl&& exrate)
{
	_pos = std::move(pos);
	_size = std::move(size);
	_exrate = std::move(exrate);
	_zorder = 1;

	Init();
}

Player::~Player()
{
}

void Player::Update(void)
{	
	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });
	_dbgDrawFormatString(0, 50, 0xFFFFFF, "プレイヤーの座標 X:%d,Y:%d", _pos.x, _pos.y);
	_dbgDrawFormatString(0, 100, 0xFFFFFF, "Mapの座標 X:%f,Y:%f", IpSceneMng.mapPos.x, IpSceneMng.mapPos.y);
	_status[Status_ID::HP] = 100 + _status[Status_ID::体力] * 1.7+ _status[Status_ID::筋力]*0.7;
	_status[Status_ID::スタミナ] = 100 + _status[Status_ID::持久力] * 1.7;
	_status[Status_ID::攻撃力] = 10 + _status[Status_ID::筋力] * 1.7 + _status[Status_ID::敏捷] * 0.7;
	_status[Status_ID::防御力] = 10 + _status[Status_ID::持久力] * 1.7 + _status[Status_ID::筋力] * 0.7;



	if (IpSceneMng._chipNo.first == CHIP_TYPE::地図5)
	{
		//if (_pos.y > 640)
		//{
		//	stateDir(STATE::NORMAL, DIR_ID::UP);



		//	//_runFlag = false;

		//	

		//}

	}


	//auto test = [&](int no) {
	//	if (IpSceneMng._chipNo.first == CHIP_TYPE::地図3)
	//	{
	//		Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };

	//			if (IpSceneMng._data[Pos.y][Pos.x] == no)
	//			{
	//				return true;
	//			}
	//			else
	//			{
	//				return false;
	//			}
	//		
	//	}
	//
	//
	//};
	//
		Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };

	if (DestroyPrpc())
	{
		IpSceneMng._data[Pos.y][Pos.x] = -1;
		return;
	}
	if (IpSceneMng._chipNo.first == CHIP_TYPE::地図3)
	{
		if (IpSceneMng._data[Pos.y][Pos.x] == 5 || IpSceneMng._data[Pos.y][Pos.x] == 6 || IpSceneMng._data[Pos.y][Pos.x] == 7 || IpSceneMng._data[Pos.y][Pos.x] == 8)
		{
			//_runFlag = false;
			modeState_ = ModeState::強制移動;
		}
		else
		{
			modeState_ = ModeState::普通;

		}
	}

	//if (CheckHitKey(KEY_INPUT_Z))
	//{
	//	IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });

	//}



	ModeInit_[modeState_]();



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
			_speed = { 0,-4 };
			_posOld = _pos;

			_runFlag = true;

		}
		break;
	case InputID::Down:
		stateDir(STATE::NORMAL, DIR_ID::DOWN);

		if (_pData._bit.DOWN)
		{
			_posOld = _pos;
			_speed = { 0,4 };

			_runFlag = true;

		}

		break;
	case InputID::Left:
			stateDir(STATE::NORMAL, DIR_ID::LEFT);

		if (_pData._bit.LEFT)
		{
			_posOld = _pos;
			_speed = { -4,0 };

			_runFlag = true;

		}
		break;
	case InputID::Right:
		stateDir(STATE::NORMAL, DIR_ID::RIGHT);

		if (_pData._bit.RIGHT)
		{
			_posOld = _pos;
			_speed = { 4,0 };

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
				_statusOld = _status;
				_experience[-1] = _experience[0];
				status_ = Status_ID::体力;
			}
			break;
		case InputID::Esc:

			if (meanState_ == MeanState::外)
			{
				modeState_ = ModeState::普通;
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
				status_ = Status_ID::MAX;
			}

			break;
		case InputID::Down:
			if (status_ < Status_ID::MAX)
			{
				status_ = (Status_ID)(static_cast<int>(status_) + 1);

			}
			else
			{
				status_ = Status_ID::体力;
			}

			break;
		case InputID::Left:
			if (status_!=Status_ID::MAX)
			{
				if (_status[status_]> _statusOld[status_])
				{
					_status[status_] -= 1;
					_status[Status_ID::レベル] -= 1;
					_experience[0] += _experience[_status[Status_ID::レベル]+1];

				}
			}

			break;
		case InputID::Right:
			if (status_ != Status_ID::MAX)
			{
				if (_experience[0] > _experience[_status[Status_ID::レベル]])
				{
					_status[status_] += 1;
					_status[Status_ID::レベル] += 1;
					_experience[0] -= _experience[_status[Status_ID::レベル]];
				}
			}


			break;
		case InputID::Z:
			if (status_ == Status_ID::MAX)
			{
				meanState_ = MeanState::外;
			}

			break;
		case InputID::Esc:
			if (meanState_ == MeanState::中)
			{
				_status = _statusOld;
				_experience[0] = _experience[-1];
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

			if (IpSceneMng._data[_posOld.y / 32][_posOld.x / 32] == 0)
			{
				IpSceneMng._data[_posOld.y / 32][_posOld.x / 32] = -1;
			}
			_runFlag = false;

		}
	}

	auto CheckUP = [&](int no) {
		Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y - 4) / 32) };
		if (IpSceneMng._data[Pos.y - 1][Pos.x] == no)
		{
			_pData._bit.UP = 0;


			return true;

		}
		return false;

	};
	auto CheckRight = [&](int no) {

		Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
		if (IpSceneMng._data[Pos.y][Pos.x + 1] == no)
		{
			_pData._bit.RIGHT = 0;

			return true;

		}
		return false;

	};
	auto CheckLeft = [&](int no) {

		Vector2	Pos = { static_cast<int>((_pos.x + _size.x - 4) / 32),static_cast<int>(_pos.y / 32) };

		if (IpSceneMng._data[Pos.y][Pos.x - 1] == no)
		{
			_pData._bit.LEFT = 0;

			return true;

		}
		return false;

	};
	auto CheckDown = [&](int no) {
		Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };

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
			int list[] = { 1,3,4 };
			for (int i = 0; i < 3; i++)
			{
				CheckUP(list[i]);
				CheckRight(list[i]);
				CheckLeft(list[i]);
				CheckDown(list[i]);
			}
			
			if(CheckUP(3)||CheckRight(3)||CheckLeft(3)||CheckDown(3))
			{
				if (data.first==InputID::Z)
				{
					if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
					{

						modeState_ = ModeState::メニュー;
					}
				}

			}
			else
			{
				if (data.first == InputID::Z)
				{
					if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
					{

						IpSceneMng.AddActQue({ ACT_QUE::SHOT , *this });
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

				_pos += _speed;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 0;
				}
			}
			break;
		case DIR_ID::LEFT:

			if (_pData._bit.LEFT)
			{
				_pos += _speed;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 0;
				}
			}
			break;
		case DIR_ID::RIGHT:

			if (_pData._bit.RIGHT)
			{
				_pos += _speed;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 0;
				}
			}
			break;
		case DIR_ID::UP:

			if (_pData._bit.UP)
			{
				_pos += _speed;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 0;
				}
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
	modeState_ = ModeState::普通;


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
		

		for (int i = 0; i < 24; i++)
		{
			data.emplace_back(IMAGE_ID("blast")[i], i);
		}
		data.emplace_back(-1, 25);
		SetAnim(STATE::DETH, dir, data);
		//_dirFlag.try_emplace(dir, true);

	}
	
	//if (meanType.size() == 0)
	//{
	//	meanType.emplace_back("ステータス");
	//	meanType.emplace_back("保存");
	//	meanType.emplace_back("終了");

	//}
	StateInit();
	ModeInit();
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
		/*_status.try_emplace(Status_ID::HP, 0);
		_status.try_emplace(Status_ID::最大HP, 0);*/
		//_status.try_emplace(Status_ID::MP, 0);
		//_status.try_emplace(Status_ID::最大MP, 0);
		
		_status.try_emplace(Status_ID::レベル, 1);
		
		_status.try_emplace(Status_ID::HP, 1);
		_status.try_emplace(Status_ID::スタミナ, 1);
		_status.try_emplace(Status_ID::攻撃力, 1);
		_status.try_emplace(Status_ID::防御力, 1);




		_status.try_emplace(Status_ID::体力, 1);
		_status.try_emplace(Status_ID::持久力,2);
		_status.try_emplace(Status_ID::筋力, 3);
		_status.try_emplace(Status_ID::敏捷, 4);
		_status.try_emplace(Status_ID::回復, 5);


		_statusOld.try_emplace(Status_ID::レベル, 1);

		_statusOld.try_emplace(Status_ID::HP, 1);
		_statusOld.try_emplace(Status_ID::スタミナ, 1);
		_statusOld.try_emplace(Status_ID::攻撃力, 1);
		_statusOld.try_emplace(Status_ID::防御力, 1);


		_statusOld.try_emplace(Status_ID::体力, 1);
		_statusOld.try_emplace(Status_ID::持久力, 2);
		_statusOld.try_emplace(Status_ID::筋力, 3);
		_statusOld.try_emplace(Status_ID::敏捷, 4);
		_statusOld.try_emplace(Status_ID::回復, 5);


	}
	


	for (int x = -1; x < 99; x++)
	{
		_experience.try_emplace(x, 100 * x);

	}
	_experience[0] = 9999;
	_experience[-1] = 0;
	

}
void Player::ModeInit(void)
{
	ModeInit_.try_emplace(ModeState::普通, [&]() {
		Move();
	
	
	});
	ModeInit_.try_emplace(ModeState::強制移動, [&]() {

		if (static_cast<int>(_pos.x % 32) == 0)
		{
			if (static_cast<int>(_pos.y % 32) == 0)
			{


				_runFlag = false;

			}
		}
			Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
			if (!_runFlag)
			{					
				Vector2 Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y -8) / 32) };

				if (IpSceneMng._data[Pos.y][Pos.x] == 5)
				{

					stateDir(STATE::STAY, DIR_ID::UP);
					_speed = { 0,-8 };
					_runFlag = true;

				}

				Pos = { static_cast<int>((_pos.x + _size.x -8) / 32),static_cast<int>(_pos.y / 32) };

				if (IpSceneMng._data[Pos.y][Pos.x] == 7)
				{
					stateDir(STATE::STAY, DIR_ID::LEFT);
					//_pos.x -= 4;
					_speed = { -8,0 };

					_runFlag = true;

				}


				
				Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };

				if (IpSceneMng._data[Pos.y][Pos.x] == 8)
				{
					stateDir(STATE::STAY, DIR_ID::RIGHT);
					//_pos.x += 4;
					_speed = { 8,0 };

					_runFlag = true;

				}
				if (IpSceneMng._data[Pos.y][Pos.x] == 6)
				{
					stateDir(STATE::STAY, DIR_ID::DOWN);
					//_pos.y += 4;
					_speed = { 0,8 };

					_runFlag = true;

				}
			}
			
			if (_runFlag)
			{

				switch (_dir)
				{
				case DIR_ID::DOWN:

					//if (_pData._bit.DOWN)
					{

						_pos += _speed;
						if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
						{
							IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 10;
						}
					}
					break;
				case DIR_ID::LEFT:

					//if (_pData._bit.LEFT)
					{
						_pos += _speed;
						if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
						{
							IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 10;
						}
					}
					break;
				case DIR_ID::RIGHT:

					//if (_pData._bit.RIGHT)
					{
						_pos += _speed;
						if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
						{
							IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 10;
						}
					}
					break;
				case DIR_ID::UP:

					//if (_pData._bit.UP)
					{
						_pos += _speed;
						if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
						{
							IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 10;
						}
					}
					break;

				default:
					break;
				}
			}




	});


	ModeInit_.try_emplace(ModeState::メニュー, [&]() {

		auto size = { 0.5f,0.5f };

		auto Pos = [&](MeanID id) {

			return Vector2(50, 120 + mean_size_Y * static_cast<int>(id));
		};

		IpSceneMng.AddDrawQue({ "ステータス",Pos(MeanID::ステータス), {1.0f,1.0f },20,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "保存",Pos(MeanID::保存), {1.0f,1.0f },20,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "ゲーム終了",Pos(MeanID::終了),{ 1.0f,1.0f },20,0,LAYER::UI });




		IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {20,100}, { 0,0 }, {0.5f,0.5f }, false, 0, 0, LAYER::UI });


		if (meanState_ == MeanState::外)
		{


			IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {30,120 + 40 * static_cast<int>(meanID_)}, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });

		}

		if (meanState_ == MeanState::中)
		{
			auto Pos = [&](Vector2 pos) {

				return Vector2(200 + pos.x, 140 + 30 * pos.y);
			};

			auto color = [&](Vector2 pos, Status_ID id) {
				int tmp = 0;
				_status[id] == _statusOld[id] ? tmp = 0 : tmp = 1;

				number.Draw(pos, { 0.2f,0.2f }, _status[id], tmp);

			};

			switch (meanID_)
			{
			case MeanID::ステータス:
				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {170,100}, { 0,0 }, {1.0f,1.4f}, false, 0, 0, LAYER::UI });
				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {470,100}, { 0,0 }, {1.0f,0.8f}, false, 0, 0, LAYER::UI });

				IpSceneMng.AddDrawQue({ "レベル　 　   -> ",{200,155},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "経験値　 　   -> ",{200,185},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "必要量",{200,215},{1.0f,1.0f},20,0,LAYER::UI });



				IpSceneMng.AddDrawQue({ "体力",{220,265},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "持久力",{220,295},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "筋力",{220,325},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "敏捷",{220,355},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "回復",{220,385},{1.0f,1.0f },20,0,LAYER::UI });

				IpSceneMng.AddDrawQue({ "HP           ->",{490,155},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "スタミナ      ->",{490,185},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "攻撃力        ->",{490,215},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "防御力        ->",{490,245},{1.0f,1.0f },20,0,LAYER::UI });

				IpSceneMng.AddDrawQue({ "決定",{270,450},{1.0f,1.0f },20,0,LAYER::UI });


				number.Draw({ 330, 155 }, { 0.2f,0.2f }, _statusOld[Status_ID::レベル], 0);

				number.Draw({ 620,155 }, { 0.2f,0.2f }, _statusOld[Status_ID::HP], 0);
				number.Draw({ 620,185 }, { 0.2f,0.2f }, _statusOld[Status_ID::スタミナ], 0);
				number.Draw({ 620,215 }, { 0.2f,0.2f }, _statusOld[Status_ID::攻撃力], 0);
				number.Draw({ 620,245 }, { 0.2f,0.2f }, _statusOld[Status_ID::防御力], 0);

				color({ 730,155 }, Status_ID::HP);
				color({ 730,185 }, Status_ID::スタミナ);
				color({ 730,215 }, Status_ID::攻撃力);
				color({ 730,245 }, Status_ID::防御力);

				number.Draw({ 330, 185 }, { 0.2f,0.2f }, _experience[-1], 0);
				_experience[-1] == _experience[0] ? number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 0) : number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 1);
				//number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 0);
				number.Draw({ 430, 215 }, { 0.2f,0.2f }, _experience[_status[Status_ID::レベル]], 0);



				color({ 430, 155 }, Status_ID::レベル);
				color({ 430, 265 }, Status_ID::体力);
				color({ 430, 295 }, Status_ID::持久力);
				color({ 430, 325 }, Status_ID::筋力);
				color({ 430, 355 }, Status_ID::敏捷);
				color({ 430, 385 }, Status_ID::回復);

				status_ != Status_ID::MAX ? IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {200,265 + 30 * (static_cast<int>(status_) - (static_cast<int>(Status_ID::体力))) }, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI }) :
					IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {250,450}, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });




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
			if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
			{

				MeanCtl(data.first);
			}
		}

	});


}