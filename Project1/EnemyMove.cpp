#include "EnemyMove.h"
#include <math.h>
#include "_DeBugConOut.h"
#include "_DebugDispOut.h"
#include "SceneMng.h"
#include <Dxlib.h>


EnemyMove::EnemyMove(Vector2Dbl& pos, double& rad, Vector2Dbl& size, DIR_ID& movetype) :_pos(pos), _rad(rad), _size(size), movetype(movetype)
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(sharedObj plObj)
{
	// �֐��|�C���^��nullptr�����ǂ����A�m�F����
	if (_move != nullptr)
	{
		// �֐��|�C���^�������g���Ă�	:	this->*_move();�G���[���o�錴����_move()�̗D��x���������Ƃł�
		(this->*_move)();
	}

}

// �ړ���ސݒ�
bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	// �V�����ړ�������΁A�Â��ړ�������
	if (newFlag)
	{
		_aim.clear();
	}

	// move���g���āA�R�s�[�ƍ폜�̃R�X�g������Ȃ��Ȃ�
	_aim = std::move(state);
	if (newFlag)
	{
		SetMovePrg();
	}
	return true;
}

// �Z�b�g���[�u�v���O����
void EnemyMove::SetMovePrg(void)
{

	auto aimRev = [&]() {
		for (_aimCnt = 0; _aimCnt < _aim.size(); _aimCnt++)
		{
			if (_aim[_aimCnt].first == DIR_ID::RIGHT)
			{
				return true;
			}
		}
		return false;
	};
	_aimCnt++;

	//�͈͓��ɓ��������ǂ���
	if (_aimCnt >= _aim.size())
	{
		if (!aimRev())
		{
			return;
		}

	}

	_startPos = _pos;						// �X�^�[�g�̃S�[���n�_

	_endPos = _aim[_aimCnt].second;			// �G���h�̃S�[���n�_

	// _move�̈ړ���ނ̐ݒ�
	switch (_aim[_aimCnt].first)
	{
	case DIR_ID::UP:
		_posOld = _pos;
		_move = &EnemyMove::MoveUp;

		break;

	case DIR_ID::RIGHT:
		_posOld = _pos;
		_move = &EnemyMove::MoveRight;

		break;

	case DIR_ID::DOWN:
		_posOld = _pos;
		_move = &EnemyMove::MoveDown;

		break;

	case DIR_ID::LEFT:
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


// �l�����ړ�-100�s�N�Z���ړ�������A�����܂�
void EnemyMove::MoveUp(void)
{
	if (abs(_pos.y - _posOld.y) < 100)
	{
		movetype = DIR_ID::UP;
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
		movetype = DIR_ID::RIGHT;
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
		movetype = DIR_ID::LEFT;
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
		movetype = DIR_ID::DOWN;
	}
	else
	{
		SetMovePrg();
	}
}






