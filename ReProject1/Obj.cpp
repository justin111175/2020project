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
	// _animkeyを探して、存在しているかどうか確保する
	if (_animMap[static_cast<int>(_dir)].find(_state) == _animMap[static_cast<int>(_dir)].end())
	{
		return;
	}
	// _animFrameを探して、存在しない確保する：０より小さい、要素のコマ数より大きい
	if (_animFrame<0 || _animFrame>=_animMap[static_cast<int>(_dir)][_state].size())
	{
		return;
	}

	if (_animMap[static_cast<int>(_dir)][_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[static_cast<int>(_dir)][_state][_animFrame].second)
		{
			// フレームの加算
			_animFrame++;
		}
		if (_animFrame >= _animMap[static_cast<int>(_dir)][_state].size())
		{
			// フレームとカント0にする
			_animFrame = 0;
			_animCount = 0;
		}
		else
		{
			// カントの加算
			_animCount++;
		}
	}
	
	// 描画キューの設定
	IpSceneMng.AddDrawQue({ _animMap[static_cast<int>(_dir)][_state][_animFrame].first,{ _pos.x, _pos.y },{_size.x,_size.y},{_exrate.x,_exrate.y},_rad,_turnFlag,_zorder,LAYER::CHAR });

}

void Obj::Draw(int id)
{
	// 描画キューの設定｛Key、座標X、座標Y、サイズX、サイズY、拡大縮小率X、拡大縮小率Y、角度、Zオーダー（レイヤーの前後順番）、レイヤーID｝
	IpSceneMng.AddDrawQue({ id, {_pos.x, _pos.y} ,{_size.x,_size.y},{_exrate.x,_exrate.y},_rad,_turnFlag,_zorder,LAYER::CHAR });
}

Obj::~Obj()
{
}

// どのアニメションを再生するか指定する
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

// アニメがおわったかどうか
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



Vector2 Obj::Pos(void)
{
	return _pos;
}

bool Obj::Pos(Vector2 pos)
{
	_pos = pos;
	return true;
}

const STATE Obj::GetState(void)
{
	return _state;
}

const double Obj::GetRad(void)
{
	return _rad;
}

bool Obj::SetRad(double rad)
{
	_rad = rad;
	return true;;
}

Vector2 Obj::posOldGet(void)
{

	return _posOld;
}

Vector2 Obj::sizeGet(void)
{
	return _size;
}

DIR_ID Obj::DIR(void)
{
	return _dir;
}

bool Obj::DIR(DIR_ID dir)
{
	_dir = dir;
	return true;
}

bool Obj::RunFlag(bool flag)
{
	_runFlag = flag;
	return true;
}

const DIR_ID Obj::GetDir(void)
{
	return _dir;
}


// 爆発アニメが終わったかどうか確認、終わったら、消滅する
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


