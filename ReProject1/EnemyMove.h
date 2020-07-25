#pragma once
#include "Obj.h"
#include"common/Vector2.h"
#include <vector>

enum class MOVE_TYPE
{
	Normal,
	MAX
};

//移動種類、ゴール地点
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2>>;

class EnemyMove :
	public Obj
{
public:
	EnemyMove(Vector2& pos, double& rad, Vector2Dbl& size, DIR_ID& dir);
	~EnemyMove();

	bool SetMoveState(MoveState& state, bool newFlag);	// 移動種類設定：新しい移動があれば古い移動を消す
	void Update(void) override;				// 更新
private:
	void SetMovePrg(void);								// セットムーブプログラム
	void (EnemyMove::*_move)(void);						// ムーブ用関数ポインタ

	// 移動用関数
	void MoveNormal(void);								




	MoveState _aim;										// 移動種類、ゴール地点
	int _aimCnt;										// 移動種類の計算

	Vector2 _startPos;								// 各移動関数のスタート地点
	Vector2 _endPos;									// 各移動関数のエンド地点

	Vector2& _pos;									// ゴール地点
	Vector2Dbl& _size;									// サイズ
	DIR_ID& _dir;								//移動のタイプ


	double & _rad;										// 角度
	int cnt;											// 頻度用計算
	int _limit;											// LR移動の移動量制限
};

