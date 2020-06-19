#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>
#include <Number.h>
#include <Letter.h>

#define PLSPEED 4												// プレイヤーの最大値スピード（左右）

enum MEAN_ID													//メニューのID
{
	ステータス,
	装備,
	保存,
	オプション,
	ゲーム終了
};

enum class ME_ST												//メニューの状態	
{
	MEAN_OUT,													// メニューの外
	MEAN_IN,													// メニューの中

};


class Player :
	public Obj
{	
public:
	Player();													//コンストラクタ
	Player(Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate);
	void Update(sharedObj plObj) override;									// 更新
	~Player();													//デストラクタ
	//Level _level;														//レベル


private:
	bool SetAlive(bool alive);

	void PlayerMove(void);										// プレイヤーの移動
	void Init(void);											// 初期化
	void Save(void);
	void Read(void);

	void StatusInit(void);
	void StatusUpdate(void);									//ステータス更新

	ME_ST MeanState;											//メニューの状態

	STATUS_UP statusupId;										//ステータスのID
	void UIDraw(void);											//ゲーム画面描画
	void MeanDraw(void);										//メニュー描画

	bool meanFlag;												//メニュー開いたかどうかフラグ
	bool LetterFlag;
	
	Number number;												//数字用
	Letter letter;												//文字用
	int Bmax;													//弾の最大値
	
	Vector2Dbl speed;											//移動速度


	double HpRatio;
	double MpRatio;
};

