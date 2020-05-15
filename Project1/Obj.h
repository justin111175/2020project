#pragma once
#include <string>
#include <vector>
#include <Vector2.h>
#include <map>
#include <memory>


enum class MOVE_TYPE
{
	DOWN,
	LEFT,						// 左
	RIGHT,						// 右
	UP,
};

// 状態管理
enum class STATE
{	
	DOWN,
	LEFT,						// 左
	RIGHT,						// 右
	UP,
	
	STAY,						// 止まる
	NORMAL,
	DETH,						// 爆発(死亡)
	MAX
};




enum class UNIT_ID
{
	NON,						// 何もなし
	PLAYER,						// プレイヤー
	ENEMY,						// 敵
	PLaS,						// プレイヤー近距離攻撃
	PLaB
};

enum class ACT
{
	STAY,						// 止まる
	RIGHT,						// 右
	LEFT,						// 左
	MAX
};

class Obj;
class Player;
class Enemy;
class iteam;
class Floor;

using AnimVector = std::vector<std::pair<int, unsigned int>>;

//shared_ptr：		指定されたリソースへの所有権(ownership)を共有(share)するスマートポインタである。
using sharedObj = std::shared_ptr<Obj>;									// shared_ptr 側だけコビーできます

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj)=0;								// 純粋仮想関数
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool state(const STATE state);										// ゲット関数-どのアニメションを再生するか指定する
	UNIT_ID _unitID;													// ユニットID
	MOVE_TYPE movetype;
	virtual bool SetAlive(bool alive);									// 生きているかどうか設定

	bool SetAnim(const STATE state,AnimVector& data);					// アニメの設定
	bool isAlive(void) { return _alive; }								// 生きている管理
	bool isDead(void) { return _dead; }									// 死んでいる管理
	bool isAnimEnd(void);												// アニメがおわったかどうか
	Vector2Dbl _pos;													// 座標
	Vector2Dbl _posOld;
	Vector2 _size;														// サイズ

private:

	std::map <STATE, AnimVector> _animMap;								// キー、アニメフレーム
	STATE _state;														// 状態
	unsigned int _animFrame;											// フレーム
	unsigned int _animCount;											// アニメカント

protected:

	bool DestroyPrpc(void);												// 爆発アニメが終わったかどうか確認、終わったら、消滅する
	bool _alive;														// アライブー＞生きているかグラフ
	bool _dead;															// 死亡－＞死んでいるかグラフ
	double _rad;														// 角度
	int _zorder;														// 描画優先度用
};
