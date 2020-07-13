#include "Player.h"
#include <Dxlib.h>
#include "common/Input/KeyInput.h"
#include "common/ImageMng.h"
#include "Scene/SceneMng.h"

Player::Player()
{
	Init();
}

Player::Player(Vector2Dbl&& pos, Vector2Dbl&& size, Vector2Dbl&& exrate)
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
	for (auto data : controller->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)])
		{
			SetDir(data.first);
		}

	}


	Move();
	(*controller)();
	
	Camera();

}


void Player::SetDir(InputID id)
{	

	auto dir = [&](DIR_ID dir,InputID _id) {
		if(_id==id)
		{

			if (_dirFlag[_dir])
			{
				stateDir(STATE::NORMAL, dir);
				_runFlag = true;
			}
				IpSceneMng.AddActQue({ ACT_QUE::MOVE , *this });

		}
	};
	if (!_runFlag)
	{

		dir(DIR_ID::UP, InputID::Up);
		dir(DIR_ID::DOWN, InputID::Down);
		dir(DIR_ID::RIGHT, InputID::Right);
		dir(DIR_ID::LEFT, InputID::Left);

	}
	
}

void Player::Move(void)
{

	auto move = [&](DIR_ID dir, Vector2Dbl speed) {
		if (_dir == dir)
		{
			if (_dirFlag[dir])
			{
				_posOld = _pos;
				_pos += speed;
			}
			else
			{
				_pos=_posOld;

			}
			
		}


	};

	if (_runFlag)
	{

		move(DIR_ID::UP, { 0,-4 });
		move(DIR_ID::DOWN, { 0,4 });
		move(DIR_ID::RIGHT, { 4,0 });
		move(DIR_ID::LEFT, { -4,0 });

		
		if ((static_cast<int>(_pos.x) % 32) == 0 &&
			(static_cast<int>(_pos.y) % 32) == 0)
		{
			_runFlag = false;
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

	if (_pos.x - tmp.x > 1280 / 2)
	{
		if (tmp.x < 2400 - 1280)
		{
			IpSceneMng.mapPos.x += 4;
		}
		else
		{

			IpSceneMng.mapPos.x = 75 * 32 - 1280;
		}
	}
	if (_pos.x - tmp.x < 1280 / 2)
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

	if (_pos.y - IpSceneMng.mapPos.y > 800 / 2)
	{
		if (tmp.y < 2400 - 800)
		{
			IpSceneMng.mapPos.y += 4;
		}
		else
		{

			IpSceneMng.mapPos.y = 75 * 32 - 800;
		}
	}
	if (_pos.y - tmp.y < 800 / 2)
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
