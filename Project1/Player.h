#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>

#define PLSPEED 4												// プレイヤーの最大値スピード（左右）

class Player :
	public Obj
{	
public:
	Player();
	Player(Vector2Dbl pos, Vector2 size);
	void Update(sharedObj plObj) override;									// 更新
	~Player();

private:
	bool SetAlive(bool alive);
	int _treadCnt;												
	ACT playerAct;												// プレイヤーの動き

	void PlayerMove(void);										// プレイヤーの移動
	void Init(void);											// 初期化
	std::shared_ptr<InputState>_input;				// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言


	int levelCnt;


	int level[10];
	int a[9];
	int HP;
};

