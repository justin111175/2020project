#include "Player.h"
#include <Dxlib.h>
#include "common/Input/KeyInput.h"
#include "GameScene.h"

Player::Player(Vector2&& pos)
{
	_pos = std::move(pos);
	//_size = { 48,48 };
	Init();
	_runFlag = false;
}

Player::~Player()
{
}

int Player::GetScreenId(void)
{
	return screenID;
}

void Player::Draw(void)
{

	//SetDrawScreen(screenID);

	//ClsDrawScreen();

	DrawCircle(_pos.x+24, _pos.y + 24, 24, 0xFFFFFF, true);

}

void Player::Run(void)
{
	for (auto data : controller->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)])
		{
			Move(data.first);
		}
	}


	if (_runFlag)
	{
		switch (_dir)
		{
		case Dir::Up:
			_pos.y -= 4;

			break;
		case Dir::Down:
			_pos.y += 4;

			break;
		case Dir::Right:
			_pos.x += 4;

			break;
		case Dir::Left:
			_pos.x -= 4;

			break;
		default:
			break;
		}

		if ((_pos.x % 32) == 0 &&
			(_pos.y % 32) == 0)
		{
			_runFlag = false;
		}
	}

	(*controller)();

}

void Player::Move(InputID id)
{	
	if (!_runFlag)
	{
		switch (id)
		{
		case InputID::Up:
			_dir = Dir::Up;
			_runFlag = true;
			break;
		case InputID::Down:
			_dir = Dir::Down;
			_runFlag = true;

			break;
		case InputID::Left:
			_dir = Dir::Left;
			_runFlag = true;

			break;
		case InputID::Right:
			_dir = Dir::Right;
			_runFlag = true;
			break;

		default:
			break;
		}
	}


	

	//if ((_pos.x % 32) != 0 &&
	//	(_pos.y % 32) != 0)
	//{

	//}

		//switch (id)
		//{
		//case InputID::Up:
		//	_pos.y -= 4;
		//	break;
		//case InputID::Down:
		//	_pos.y += 4;

		//	break;
		//case InputID::Left:
		//	_pos.x -= 4;
		//	break;
		//case InputID::Right:
		//	_pos.x += 4;

		//	break;

		//default:
		//	break;
		//}
	//}


}

void Player::Init(void)
{
	screenID = MakeScreen(1280, 800, true);

	controller = std::make_unique<KeyInput>();
	controller->SetUp();

}
