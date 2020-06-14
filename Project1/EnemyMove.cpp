#include "EnemyMove.h"
#include <math.h>
#include "_DeBugConOut.h"
#include "_DebugDispOut.h"
#include "SceneMng.h"
#include <Dxlib.h>


EnemyMove::EnemyMove(Vector2Dbl& pos, double& rad, Vector2Dbl& size, MOVE_TYPE& movetype) :_pos(pos), _rad(rad), _size(size), movetype(movetype)
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(sharedObj plObj)
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
			if (_aim[_aimCnt].first == MOVE_TYPE::RIGHT)
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
	case MOVE_TYPE::UP:
		_posOld = _pos;
		_move = &EnemyMove::MoveUp;

		break;

	case MOVE_TYPE::RIGHT:
		_posOld = _pos;
		_move = &EnemyMove::MoveRight;

		break;

	case MOVE_TYPE::DOWN:
		_posOld = _pos;
		_move = &EnemyMove::MoveDown;

		break;

	case MOVE_TYPE::LEFT:
		_posOld = _pos;
		_move = &EnemyMove::MoveLeft;

		break;

	default:
		AST();
		break;
	}

}

void EnemyMove::MoveNormal(void)
{

	//TRACE(" %d\n", movetype);

	//if (_pos == _posOld)
	//{
	//	movetype = MOVE_TYPE::RIGHT;
	//}
	//else if ((abs(_pos.x - _posOld.x) > 100)&& movetype == MOVE_TYPE::RIGHT)
	//{
	//	movetype = MOVE_TYPE::DOWN;
	//	//_posOld = _pos;
	//}
	//else if ((abs(_pos.y - _posOld.y) > 100)&& movetype == MOVE_TYPE::DOWN)
	//{
	//	movetype = MOVE_TYPE::LEFT;
	//}
	//else if (_pos.x == _posOld.x &&movetype == MOVE_TYPE::LEFT)
	//{
	//	movetype=MOVE_TYPE::UP;
	//}


}


// 四方向移動-100ピクセル移動したら、抜けます
void EnemyMove::MoveUp(void)
{
	if (abs(_pos.y - _posOld.y) < 100)
	{
		movetype = MOVE_TYPE::UP;
	}
	else
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveRight(void)
{	
	if (abs(_pos.x - _posOld.x) < 100)
	{
		movetype = MOVE_TYPE::RIGHT;
	}
	else
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveLeft(void)
{
	if (abs(_pos.x - _posOld.x) < 100)
	{
		movetype = MOVE_TYPE::LEFT;
	}
	else
	{
		SetMovePrg();
	}
}

void EnemyMove::MoveDown(void)
{

	if (abs(_pos.y - _posOld.y) < 100)
	{
		movetype = MOVE_TYPE::DOWN;
	}
	else
	{
		SetMovePrg();
	}
}






