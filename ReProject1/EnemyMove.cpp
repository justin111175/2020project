#include "EnemyMove.h"
#include <math.h>

#include "Scene/SceneMng.h"
#include <Dxlib.h>
#include "common/TimeCount.h"

EnemyMove::EnemyMove(Vector2& pos, double& rad, Vector2Dbl& size, DIR_ID& dir) :_pos(pos), _rad(rad), _size(size), _dir(dir)
{
	_move = nullptr;
	_runFlag = false;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
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
			if (_aim[_aimCnt].first == MOVE_TYPE::Normal)
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
	case MOVE_TYPE::Normal:
		_posOld = _pos;
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
			_runFlag = false;

		}
	}
	if (static_cast<int>(_pos.x % 32) == 0)
	{
		if (static_cast<int>(_pos.y % 32) == 0)
		{
			if (CheckHitKey(KEY_INPUT_A))
			{
				_dir = DIR_ID::LEFT;
				_runFlag = true;
			}
			if (CheckHitKey(KEY_INPUT_D))
			{
				_dir = DIR_ID::RIGHT;
				_runFlag = true;
			}
			if (CheckHitKey(KEY_INPUT_W))
			{
				_dir = DIR_ID::UP;
				_runFlag = true;
			}
			if (CheckHitKey(KEY_INPUT_S))
			{
				_dir = DIR_ID::DOWN;
				_runFlag = true;
			}
		}
	}

	if (!_runFlag)
	{
		switch (static_cast<DIR_ID>(rand() % 4) )
		{
		case DIR_ID::DOWN:

			_dir = DIR_ID::DOWN;
			_runFlag = true;

			break;
		case DIR_ID::LEFT:
			_dir = DIR_ID::LEFT;
			_runFlag = true;

			break;
		case DIR_ID::RIGHT:
			_dir = DIR_ID::RIGHT;
			_runFlag = true;


			break;
		case DIR_ID::UP:
			_dir = DIR_ID::UP;
			_runFlag = true;


			break;
		default:
			break;
		}
	}

	

	auto CheckMove = [&](int no) {
		Vector2	Pos = { static_cast<int>((_pos.x + _size.x - 1) / 32),static_cast<int>(_pos.y / 32) };

		if (IpSceneMng._data[Pos.y][Pos.x - 1] == no)
		{
			_pData._bit.LEFT = 0;
		}

		Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>((_pos.y + _size.y - 1) / 32) };
		if (IpSceneMng._data[Pos.y - 1][Pos.x] == no)
		{
			_pData._bit.UP = 0;

		}

		Pos = { static_cast<int>((_pos.x) / 32),static_cast<int>(_pos.y / 32) };
		if (IpSceneMng._data[Pos.y][Pos.x + 1] == no)
		{
			_pData._bit.RIGHT = 0;

		}
		if (IpSceneMng._data[Pos.y + 1][Pos.x] == no)
		{
			_pData._bit.DOWN = 0;
		}

	};
	CheckMove(1);

	if (_runFlag)
	{
		switch (_dir)
		{
		case DIR_ID::DOWN:
			if (_pData._bit.DOWN)
			{
				_pos.y += 1;
			}
			break;
		case DIR_ID::LEFT:
			if (_pData._bit.LEFT)
			{
				_pos.x -= 1;
			}
			break;
		case DIR_ID::RIGHT:
			if (_pData._bit.RIGHT)
			{
				_pos.x += 1;
			}
			break;
		case DIR_ID::UP:
			if (_pData._bit.UP)
			{
				_pos.y -= 1;
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



