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
	if (!_runFlag)
	{
		switch (id)
		{
		case InputID::Up:
			_dir = DIR_ID::UP;
			stateDir(STATE::NORMAL, DIR_ID::UP);

			_runFlag = true;
			break;
		case InputID::Down:
			_dir = DIR_ID::DOWN;
			stateDir(STATE::NORMAL, DIR_ID::DOWN);

			_runFlag = true;

			break;
		case InputID::Left:
			_dir = DIR_ID::LEFT;
			stateDir(STATE::NORMAL, DIR_ID::LEFT);

			_runFlag = true;

			break;
		case InputID::Right:
			_dir = DIR_ID::RIGHT;
			stateDir(STATE::NORMAL, DIR_ID::RIGHT);

			_runFlag = true;
			break;

		default:
			break;
		}
	}
	
}

void Player::Move(void)
{
	if (_runFlag)
	{
		switch (_dir)
		{
		case DIR_ID::UP:
			_pos.y -= 4;

			break;
		case DIR_ID::DOWN:
			_pos.y += 4;

			break;
		case DIR_ID::RIGHT:
			_pos.x += 4;

			break;
		case DIR_ID::LEFT:
			_pos.x -= 4;

			break;
		default:
			break;
		}

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

	_alive = true;
	_dead = false;
	_runFlag = false;

	_unitID = UNIT_ID::PLAYER;

	AnimVector data;

	for (auto dir : DIR_ID())
	{
		int dirCnt = static_cast<int>(dir) * 3;
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 0], 10);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 1], 20);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 2], 30);
		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 1], 40);
		SetAnim(STATE::NORMAL, dir, data);

		data.emplace_back(IMAGE_ID("�v���C���[����")[(__int64)dirCnt + 0], 10);
		SetAnim(STATE::STAY, dir, data);

		//_dirFlag.try_emplace(dir, true);

	}


	//data.emplace_back(IMAGE_ID("�v���C���[����")[0], 10);
	//data.emplace_back(IMAGE_ID("�v���C���[����")[1], 20);
	//data.emplace_back(IMAGE_ID("�v���C���[����")[2], 30);
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
