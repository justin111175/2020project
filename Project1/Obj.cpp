#include <Dxlib.h>
#include <SceneMng.h>
#include <ImageMng.h>
#include <Obj.h>
#include <Vector2.h>
#include <GameScene.h>

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
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// _animFrame��T���āA���݂��Ȃ��m�ۂ���F�O��菬�����A�v�f�̃R�}�����傫��
	if (_animFrame<0 || _animFrame>=_animMap[_state].size())
	{
		return;
	}

	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			// �t���[���̉��Z
			_animFrame++;
		}
		if (_animFrame >= _animMap[_state].size())
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
	IpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,/*-_mapPos.x+*/ _pos.x, _pos.y ,_size.x,_size.y,_rad,_zorder,LAYER::CHAR});

}

void Obj::Draw(int id)
{
	// �`��L���[�̐ݒ�oKey�A���WX�A���WY�A�p�x�AZ�I�[�_�[�i���C���[�̑O�㏇�ԁj�A���C���[ID�p
	IpSceneMng.AddDrawQue({ id, _pos.x, _pos.y ,_size.x,_size.y,_rad,_zorder,LAYER::CHAR});
}

Obj::~Obj()
{
}

// �ǂ̃A�j���V�������Đ����邩�w�肷��
bool Obj::state(const STATE state)
{
	if (_animMap.find(state) == _animMap.end())
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
		state(STATE::DETH);
	}

	return true;
}

bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	return (_animMap.try_emplace(state, std::move(data))).second;
}


// �A�j��������������ǂ���
bool Obj::isAnimEnd(void)
{
	if (_animMap.find(_state) == _animMap.end())
	{
		return true;
	}
	if (_animFrame < 0 || _animFrame >= _animMap[_state].size())
	{
		return true;
	}
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
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
