#pragma once
#include "Obj.h"

enum class ENEMY_TYPE
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
	MAX
};


// 種類、座標、サイズ、移動方法
using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);										// Enemyオーバーロード
	void Update(sharedObj plObj) override;							// 更新
	~Enemy();
private:
	bool SetAlive(bool alive);										// 生きているかどうか
	ACT act;														// 移動状態
	void Init(void);												// 初期化
	ENEMY_TYPE _type;												// 敵種類
};
