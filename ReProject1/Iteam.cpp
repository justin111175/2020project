#include "Iteam.h"
#include "common/ImageMng.h"
#include "Scene/SceneMng.h"

Iteam::Iteam()
{
	Init();

}

Iteam::Iteam(IteamState& state)
{



	_exrate = { 1.0f,1.0f };

	_type = std::get<static_cast<int>(ITEAM_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(ITEAM_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(ITEAM_STATE::SIZE)>(state));


	Init();

}

void Iteam::Update(void)
{
	if (_type== ITEAM_TYPE::石)
	{
		StoneMove();

	}
	stateDir(STATE::NORMAL, _dir);

}

Iteam::~Iteam()
{
}

void Iteam::StoneMove(void)
{
	_pData._bit = { 1,1,1,1 };

	stateDir(STATE::NORMAL, _dir);


	IpSceneMng.AddActQue({ ACT_QUE::CHECK , *this });

	//if (static_cast<int>(_pos.x % 32) == 0)
	//{
	//	if (static_cast<int>(_pos.y % 32) == 0)
	//	{
	//		_runFlag = false;

	//	}
	//}
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
	CheckUP(1);
	CheckRight(1);
	CheckLeft(1);
	CheckDown(1);
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


}

void Iteam::Init(void)
{

	AnimVector data;
	_zorder = -1;
	switch (_type)
	{

	case ITEAM_TYPE::石:
		_unitID = UNIT_ID::石;
		_zorder = 0;

		_runFlag = false;
		for (auto dir : DIR_ID())
		{
			int dirCnt = static_cast<int>(dir) * 12;
			data.emplace_back(IMAGE_ID("other")[(__int64)dirCnt + 0], 10);
			data.emplace_back(IMAGE_ID("other")[(__int64)dirCnt + 1], 20);
			data.emplace_back(IMAGE_ID("other")[(__int64)dirCnt + 2], 30);
			data.emplace_back(IMAGE_ID("other")[(__int64)dirCnt + 1], 40);
			SetAnim(STATE::NORMAL, dir, data);

			data.emplace_back(IMAGE_ID("other")[(__int64)dirCnt + 0], 10);
			SetAnim(STATE::STAY, dir, data);


		}


		break;
	case ITEAM_TYPE::メニュー:
		_unitID = UNIT_ID::メニュー;
		data.emplace_back(IMAGE_ID("other")[56], 30);
		data.emplace_back(IMAGE_ID("other")[55], 60);
		data.emplace_back(IMAGE_ID("other")[54], 90);
		data.emplace_back(IMAGE_ID("other")[55], 120);
		data.emplace_back(IMAGE_ID("other")[56], 150);
		SetAnim(STATE::NORMAL, data);

		break;
	case ITEAM_TYPE::スウィッチ:
		_unitID = UNIT_ID::スウィッチ;
		_zorder = -1;

		data.emplace_back(IMAGE_ID("switch")[50], 30);
		data.emplace_back(IMAGE_ID("switch")[49], 60);
		data.emplace_back(IMAGE_ID("switch")[48], 90);
		data.emplace_back(IMAGE_ID("switch")[49], 120);
		data.emplace_back(IMAGE_ID("switch")[50], 150);
		SetAnim(STATE::NORMAL, data);


		

		break;
	default:
		break;
	}


	stateDir(STATE::NORMAL);


}
