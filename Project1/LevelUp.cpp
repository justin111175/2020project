#include "LevelUp.h"
#include <ImageMng.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>

LevelUp::LevelUp()
{

	Init();

}

LevelUp::LevelUp(UNIT_ID unitID, Vector2Dbl pos,Vector2Dbl size)
{
	_exrate = { 1.0f,1.0f };
	_size = { 250,150 };
	_unitID = unitID;

	//プレイヤーのの頭の上
	_pos.x = pos.x-_size.x/2+size.x/2;
	_pos.y = pos.y-_size.y+20;

	// レベルアップしたプレイヤーの位置をとる
	_posOld = _pos;

	Init();

}

LevelUp::~LevelUp()
{
}
//レベルアップ画像の初期化
void LevelUp::Init(void)
{

	_alive = true;

	AnimVector data;
	data.reserve(1);
	
	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(IMAGE_ID("UP1")[i], i*5);
	}
	data.emplace_back(-1, 40);

	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	state(STATE::NORMAL);
}

void LevelUp::Update(sharedObj plObj)
{

	//TRACE("E:%d\n", Player::_level._statusUp[STATUS_UP::残るボーナスポイント]);

	//消失確認
	DestroyPrpc();
	//レベルアップして、アニメが終わってない、そしてプレイヤーの位置が変更した場合の補正
	if ((*plObj).posGet() != (*plObj).posOldGet())
	{
		_pos = (*plObj).posGet() - (*plObj).posOldGet() + _posOld;

	}


}

bool LevelUp::SetAlive(bool alive)
{
	if (!alive)
	{
		// 画面揺らしのQUEを投げる
		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
	}

	return Obj::SetAlive(alive);
}

bool LevelUp::DestroyPrpc(void)
{
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
