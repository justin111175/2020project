#include <Dxlib.h>
#include "Scene/SceneMng.h"

#include "common/ImageMng.h"

#include "Obj.h"
#include "Scene/GameScene.h"

Obj::Obj()
{
	_alive = true;
	_dead = false;
	_animCount = 0;
	_animFrame = 0;
	_rad = 0;
	_zorder = 0;
}

void Obj::Draw(void)
{
	// _animkey��T���āA���݂��Ă��邩�ǂ����m�ۂ���
	if (_animMap[static_cast<int>(_dir)].find(_state) == _animMap[static_cast<int>(_dir)].end())
	{
		return;
	}
	// _animFrame��T���āA���݂��Ȃ��m�ۂ���F�O��菬�����A�v�f�̃R�}�����傫��
	if (_animFrame<0 || _animFrame>=_animMap[static_cast<int>(_dir)][_state].size())
	{
		return;
	}

	if (_animMap[static_cast<int>(_dir)][_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[static_cast<int>(_dir)][_state][_animFrame].second)
		{
			// �t���[���̉��Z
			_animFrame++;
		}
		if (_animFrame >= _animMap[static_cast<int>(_dir)][_state].size())
		{
			// �t���[���ƃJ���g0�ɂ���
			_animFrame = 0;
			_animCount = 0;
		}
		else
		{
			// �J���g�̉��Z
			_animCount++;
		}
	}
	
	// �`��L���[�̐ݒ�
	IpSceneMng.AddDrawQue({ _animMap[static_cast<int>(_dir)][_state][_animFrame].first,{ _pos.x, _pos.y },{_size.x,_size.y},{_exrate.x,_exrate.y},_rad,_turnFlag,_zorder,LAYER::CHAR });

}

void Obj::Draw(int id)
{
	// �`��L���[�̐ݒ�oKey�A���WX�A���WY�A�T�C�YX�A�T�C�YY�A�g��k����X�A�g��k����Y�A�p�x�AZ�I�[�_�[�i���C���[�̑O�㏇�ԁj�A���C���[ID�p
	IpSceneMng.AddDrawQue({ id, {_pos.x, _pos.y} ,{_size.x,_size.y},{_exrate.x,_exrate.y},_rad,_turnFlag,_zorder,LAYER::CHAR });
}

Obj::~Obj()
{
}

// �ǂ̃A�j���V�������Đ����邩�w�肷��
bool Obj::stateDir(const STATE state, const DIR_ID dir)
{
	stateDir(state);
	_dir = dir;
	return true;
}

bool Obj::stateDir(const STATE state)
{
	if (_animMap[static_cast<int>(_dir)].find(state) == _animMap[static_cast<int>(_dir)].end())
	{
		return false;
	}
	if (_state != state)
	{
		_animCount = 0;
		_animFrame = 0;
	}
	_state = state;
	return true;
}




bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		stateDir(STATE::DETH);
	}

	return true;
}

bool Obj::SetRepel(bool repel)
{
	return _repelFlag= repel;
}



bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	return (_animMap[static_cast<int>(_dir)].try_emplace(state, std::move(data))).second;
}

bool Obj::SetAnim(const STATE state,const DIR_ID _dir, AnimVector& data)
{
	return (_animMap[static_cast<int>(_dir)].try_emplace(state, std::move(data))).second;
}

// �A�j��������������ǂ���
bool Obj::isAnimEnd(void)
{
	if (_animMap[static_cast<int>(_dir)].find(_state) == _animMap[static_cast<int>(_dir)].end())
	{
		return true;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[static_cast<int>(_dir)][_state].size())
	{
		return true;
	}
	if (_animMap[static_cast<int>(_dir)][_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}



Vector2Dbl Obj::posGet(void)
{
	return _pos;
}

Vector2Dbl Obj::posOldGet(void)
{

	return _posOld;
}

Vector2Dbl Obj::sizeGet(void)
{
	return _size;
}

DIR_ID Obj::dirGet(void)
{
	return _dir;
}


// �����A�j�����I��������ǂ����m�F�A�I�������A���ł���
bool Obj::DestroyPrpc(void)
{
	if (_alive)
	{
		return false;
	}
	if (isAnimEnd())
	{
		_dead = true;
	}
	return true;
}


