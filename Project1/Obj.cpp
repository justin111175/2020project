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
	// _animkeyを探して、存在しているかどうか確保する
	if (_animMap.find(_state) == _animMap.end())
	{
		return;
	}
	// _animFrameを探して、存在しない確保する：０より小さい、要素のコマ数より大きい
	if (_animFrame<0 || _animFrame>=_animMap[_state].size())
	{
		return;
	}

	if (_animMap[_state][_animFrame].first >= 0)
	{
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			// フレームの加算
			_animFrame++;
		}
		if (_animFrame >= _animMap[_state].size())
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
	IpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,/*-_mapPos.x+*/ _pos.x, _pos.y ,_size.y,_rad,_zorder,LAYER::CHAR});

}

void Obj::Draw(int id)
{
	// 描画キューの設定｛Key、座標X、座標Y、角度、Zオーダー（レイヤーの前後順番）、レイヤーID｝
	IpSceneMng.AddDrawQue({ id, _pos.x, _pos.y ,_size.y,_rad,_zorder,LAYER::CHAR});
}

Obj::~Obj()
{
}

// どのアニメションを再生するか指定する
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


// アニメがおわったかどうか
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
