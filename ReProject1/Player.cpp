#include "Player.h"
#include <Dxlib.h>
#include "common/Input/KeyInput.h"
#include "GameScene.h"

Player::Player(Vector2&& pos)
{
	_pos = std::move(pos);
	//_size = { 48,48 };
	Init();
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

	SetDrawScreen(screenID);

	ClsDrawScreen();

	DrawCircle(_pos.x, _pos.y + 24, 24, 0xFFFFFF, true);

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



	(*controller)();

}

void Player::Move(InputID id)
{

	switch (id)
	{
	case InputID::Up:
		GameScene::GetInstance().mapPos.y-=10;
		_pos.y -= 10;
		break;
	case InputID::Down:
		//GameScene::GetInstance().mapPos.y-=10;
		_pos.y += 10;

		break;
	case InputID::Left:
		//GameScene::GetInstance().mapPos.x-=10;
		_pos.x -= 10;
		break;
	case InputID::Right:
		//GameScene::GetInstance().mapPos.x+=10;
		_pos.x += 10;

		break;

	default:
		break;
	}

}

void Player::Init(void)
{
	screenID = MakeScreen(1280, 800, true);

	controller = std::make_unique<KeyInput>();
	controller->SetUp();

}
