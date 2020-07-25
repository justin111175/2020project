#pragma once
#include "Obj.h"
#include "EnemyMove.h"
#include "Player.h"

enum class ENEMY_TYPE		//敵タイプ
{
	コウモリ,
	スライム,
	オーク,
	ミノタウロス,
	小悪魔,
	スカルマン,
	ゴースト,
	魔族,
	MAX
};


// 機能管理
enum class ENEMY_STATE
{
	TYPE,					// 種類
	VECTOR,					// 座標
	SIZE,					// 大きさ
	EXRATE,					//拡大縮小率
	AIM,					// 移動種類
	MAX
};


// 種類、座標、サイズ、拡大縮小率、移動方法
using EnemyState = std::tuple<ENEMY_TYPE, Vector2, Vector2Dbl,Vector2Dbl, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);										// Enemyオーバーロード
	void Update(void) override;							// 更新
	~Enemy();
private:
	friend Player;
	EnemyMove _moveCtl{ _pos,_rad,_size,_dir};					// ムーブコントロール｛座標、角度、サイズ、移動種類｝
	bool SetAlive(bool alive);										// 生きているかどうか
	void Init(void);												// 初期化
	ENEMY_TYPE _type;												// 敵種類
};
