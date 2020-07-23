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
	_pData._bit = { 1,1,1,1 };
	//_runFlag = false;

	if (static_cast<int>(_pos.x % 32) == 0)
	{
		if (static_cast<int>(_pos.y % 32) == 0)
		{
			_runFlag = false;

		}
	}
	
	_dbgDrawFormatString(0, 50, 0xFFFFFF, "プレイヤーの座標 X:%d,Y:%d", _pos.x, _pos.y);
	_dbgDrawFormatString(0, 100, 0xFFFFFF, "Mapの座標 X:%f,Y:%f", IpSceneMng.mapPos.x, IpSceneMng.mapPos.y);

	for (auto data : controller->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)])
		{
			Vector2	Pos = { static_cast<int>((_pos.x + _size.x-4) / 32),static_cast<int>(_pos.y / 32) };

			if (IpSceneMng._data[Pos.y][Pos.x - 1] ==1)
			{
				_pData._bit.LEFT = 0;
			}

			Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y-4) / 32) };
			if (IpSceneMng._data[Pos.y - 1][Pos.x] == 1)
			{
				_pData._bit.UP = 0;

			}

			Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
			if (IpSceneMng._data[Pos.y][Pos.x + 1] ==1)
			{
				_pData._bit.RIGHT = 0;

			}
			if (IpSceneMng._data[Pos.y + 1][Pos.x] == 1)
			{
				_pData._bit.DOWN = 0;
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
				_pos.y -=4;
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

void Player::Move(void)
{
	//for (auto dir : DIR_ID())
	//{
	//	_dirFlag[dir] = true;

	//}





	//auto move = [&](DIR_ID dir, Vector2Dbl speed,Vector2 pos) {
	//	_speed = speed;
	//	if (_dir == dir)
	//	{
	//		if (_dirFlag[dir])
	//		{
	//			//if (IpSceneMng._data[pos.y][pos.x]==0)
	//			//{
	//			//	_dirFlag[dir] = false;

	//			//}
	//			//else
	//			//{
	//				//_pos += _speed;

	//			//}
	//		}
	//	}
	//};

	//if (_runFlag)
	//{
	//	Vector2 Pos = { static_cast<int>(_pos.x / 32),static_cast<int>(_pos.y / 32) };

	//	move(DIR_ID::UP, { 0,-4 }, { Pos.x,Pos.y-1});
	//	move(DIR_ID::DOWN, { 0,4 }, { Pos.x,Pos.y +1 });
	//	move(DIR_ID::RIGHT, { 4,0 }, { Pos.x+1,Pos.y  });
	//	move(DIR_ID::LEFT, { -4,0 }, { Pos.x-1,Pos.y  });
	//	




	//	
	//	if ((static_cast<int>(_pos.x) % 32) == 0 &&
	//		(static_cast<int>(_pos.y) % 32) == 0)
	//	{
	//		//_posOld = _pos;
	//		//_pos = { Pos.x * 32.0f,Pos.y * 32.0f };
	//		_runFlag = false;
	//	}

	//}
	//else
	//{
	//	switch (_dir)
	//	{
	//	case DIR_ID::UP:
	//		stateDir(STATE::STAY, DIR_ID::UP);


	//		break;
	//	case DIR_ID::DOWN:
	//		stateDir(STATE::STAY, DIR_ID::DOWN);

	//		break;
	//	case DIR_ID::RIGHT:
	//		stateDir(STATE::STAY, DIR_ID::RIGHT);

	//		break;
	//	case DIR_ID::LEFT:
	//		stateDir(STATE::STAY, DIR_ID::LEFT);

	//		break;
	//	default:
	//		break;
	//	}

	//}



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
