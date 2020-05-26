#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>
#include <Number.h>
#include <Letter.h>
#define PLSPEED 4												// プレイヤーの最大値スピード（左右）

enum MEAN_ID
{
	ステータス,
	装備,
	保存,
	オプション,
	ゲーム終了
};

enum ME_ST
{
	MEAN_OUT,
	MEAN_IN,

};



class Player :
	public Obj
{	
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate);
	void Update(sharedObj plObj) override;									// 更新
	~Player();

private:
	bool SetAlive(bool alive);
	int _treadCnt;												
	ACT playerAct;												// プレイヤーの動き

	void PlayerMove(void);										// プレイヤーの移動
	void Init(void);											// 初期化
	std::shared_ptr<InputState>_input;							// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言

	MEAN_ID meanId;
	ME_ST MeanState;

	STATUS_UP statusupId;
	void MeanDraw(void);
	void StatusUpdate(void);
	bool meanFlag;
	bool LetterFlag;
	
	Number number;
	Letter letter;

	unsigned int s[STATUS::MAX];

};

