#pragma once
#include <memory>
#include "Obj.h"
#include <tuple>														//要素が三つ以上を管理する時を使う

// クラスのプロトタイプ宣言
class BaseScene;

enum class ACT_QUE
{
	NON,																// 何もしない
	SHOT,
	SLASH,
	CHECK,
	LEVELUP,
	MOVE
};

enum class ACT_STATE
{
	ACT_QUE,															// 活動キュー
	Obj,																// Obj
	MAX
};

using unique_Base = std::unique_ptr<BaseScene>;							// スマートポインタ-BaseScene
using ActQueT = std::pair<ACT_QUE, Obj&>;								// 状態、Obj

class BaseScene
{
public:
	BaseScene();														
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;					// 純粋仮想関数
	
	virtual void RunActQue(std::vector<ActQueT> actList);				// ファンク活動キュー
	Vector2 _screenPos;													// 描画座標
protected:
	void FadeInit(std::string fadeType);								// Fade初期化
	bool FadeUpdate(void);												// Fade更新
private:
	int _fadeScrID;														// Fade描画ID
	std::string _fadeType;												// Fadeタイプ
};




