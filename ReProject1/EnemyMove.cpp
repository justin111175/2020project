#include "EnemyMove.h"
#include <math.h>

#include "Scene/SceneMng.h"
#include <Dxlib.h>
#include "common/TimeCount.h"

EnemyMove::EnemyMove(Vector2& pos, double& rad, Vector2Dbl& size, DIR_ID& dir, bool& runFlag):
	_pos(pos),
	_rad(rad), 
	_size(size), 
	_dir(dir),
	_runFlag(runFlag)
{
	_unitID = UNIT_ID::ENEMY;
	_move = nullptr;
	_runFlag = false;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// 関数ポインタはnullptrだかどうか、確認する
	if (_move != nullptr)
	{
		// 関数ポインタ自分自身を呼ぶ	:	this->*_move();エラーが出る原因は_move()の優先度が高いことです
		(this->*_move)();
	}

}

// 移動種類設定
bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	// 新しい移動があれば、古い移動を消す
	if (newFlag)
	{
		_aim.clear();
	}

	// moveを使って、コピーと削除のコストがいらなくなる
	_aim = std::move(state);
	if (newFlag)
	{
		SetMovePrg();
	}
	return true;
}

// セットムーブプログラム
void EnemyMove::SetMovePrg(void)
{

	auto aimRev = [&]() {
		for (_aimCnt = 0; _aimCnt < _aim.size(); _aimCnt++)
		{
			if (_aim[_aimCnt].first == MOVE_TYPE::Normal)
			{
				return true;
			}
		}
		return false;
	};
	_aimCnt++;

	//範囲内に入ったかどうか
	if (_aimCnt >= _aim.size())
	{
		if (!aimRev())
		{
			return;
		}

	}

	_startPos = _pos;						// スタートのゴール地点

	_endPos = _aim[_aimCnt].second;			// エンドのゴール地点

	// _moveの移動種類の設定
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::Normal:
		_move = &EnemyMove::Normal;

		break;

	case MOVE_TYPE::Stay:
		_move = &EnemyMove::Saty;
		break;
	default:
		//AST();
		break;
	}

}

void EnemyMove::Normal(void)
{
	_pData._bit = { 1,1,1,1 };


	if (static_cast<int>(_pos.x % 32) == 0)
	{
		if (static_cast<int>(_pos.y % 32) == 0)
		{
			if (IpSceneMng._data[_posOld.y / 32][_posOld.x / 32] == 4)
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

	


	//auto CheckMove = [&](int no) {
	//	Vector2	Pos = { static_cast<int>((_pos.x + _size.x - 1) / 32),static_cast<int>(_pos.y / 32) };

	//	if (IpSceneMng._data[Pos.y][Pos.x - 1] == no)
	//	{
	//		_pData._bit.LEFT = 0;
	//		return true;
	//	}

	//	Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y - 1) / 32) };
	//	if (IpSceneMng._data[Pos.y - 1][Pos.x] == no)
	//	{
	//		_pData._bit.UP = 0;
	//		return true;

	//	}

	//	Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
	//	if (IpSceneMng._data[Pos.y][Pos.x + 1] == no)
	//	{
	//		_pData._bit.RIGHT = 0;
	//		return true;


	//	}
	//	if (IpSceneMng._data[Pos.y + 1][Pos.x] == no)
	//	{
	//		_pData._bit.DOWN = 0;
	//		return true;

	//	}
	//	return false;

	//};
	int list[] = { 0,1,4 };
	for (int i = 0;i < 2; i++)
	{
		CheckUP(list[i]);
		CheckRight(list[i]);
		CheckLeft(list[i]);
		CheckDown(list[i]);
	}

	//CheckMove(5);
	//CheckMove(10);
	
	if (static_cast<int>(_pos.x % 32) == 0 && static_cast<int>(_pos.y % 32) == 0)
	{

		if (IpSceneMng.frames() % 60==0)
		{
			switch (static_cast<DIR_ID>(rand() % 4) )
			{
			case DIR_ID::DOWN:
				_dir = DIR_ID::DOWN;
				if (_pData._bit.DOWN)
				{
					_posOld = _pos;

					_runFlag = true;
				}
				break;
			case DIR_ID::LEFT:
				_dir = DIR_ID::LEFT;
				if (_pData._bit.LEFT)
				{
					_posOld = _pos;

					_runFlag = true;
				}

				break;
			case DIR_ID::RIGHT:
				_dir = DIR_ID::RIGHT;
				if (_pData._bit.RIGHT)
				{
					_posOld = _pos;

					_runFlag = true;
				}
				break;
			case DIR_ID::UP:
				_dir = DIR_ID::UP;
				if (_pData._bit.UP)
				{
					_posOld = _pos;

					_runFlag = true;
				}
				break;

			default:
				break;
			}
		}

	}
	
	if (static_cast<int>(_pos.x % 32) == 0 && static_cast<int>(_pos.y % 32) == 0)
	{

		if (CheckHitKey(KEY_INPUT_W))
		{
			_dir = DIR_ID::UP;
			if (_pData._bit.UP)
			{
				_posOld = _pos;

				_runFlag = true;
			}

		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			_dir = DIR_ID::DOWN;
			if (_pData._bit.DOWN)
			{
				_posOld = _pos;

				_runFlag = true;
			}

		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			_dir = DIR_ID::LEFT;
			if (_pData._bit.LEFT)
			{
				_posOld = _pos;

				_runFlag = true;
			}

		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			_dir = DIR_ID::RIGHT;
			if (_pData._bit.RIGHT)
			{
				_posOld = _pos;

				_runFlag = true;
			}
		}
	}

	if (_runFlag)
	{

		switch (_dir)
		{
		case DIR_ID::DOWN:
			
			//if (_pData._bit.DOWN)
			{
				_pos.y += 1;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32] = 4;
				}
			}
			break;
		case DIR_ID::LEFT:

			//if (_pData._bit.LEFT)
			{
				_pos.x -= 1;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32 ][_pos.x / 32] =4;
				}
			}
			break;
		case DIR_ID::RIGHT:

			//if (_pData._bit.RIGHT)
			{
				_pos.x += 1;
				if (IpSceneMng._data[_pos.y / 32][_pos.x / 32 ] == -1)
				{
					IpSceneMng._data[_pos.y / 32][_pos.x / 32 ] = 4;
				}

			}
			break;
		case DIR_ID::UP:

			//if (_pData._bit.UP)
			{
				_pos.y -= 1;
				if (IpSceneMng._data[_pos.y / 32 ][_pos.x / 32] == -1)
				{
					IpSceneMng._data[_pos.y / 32 ][_pos.x / 32] = 4;
				}

			}
			break;

		default:
			break;
		}
		

	}


}

void EnemyMove::Saty(void)
{


}



