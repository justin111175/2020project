#include "LevelUp.h"
#include <ImageMng.h>

LevelUp::LevelUp()
{

	Init();

}

LevelUp::LevelUp(UNIT_ID unitID, Vector2Dbl pos,Vector2Dbl size)
{
	_exrate = { 1.0f,1.0f };
	_size = { 250,150 };
	_unitID = unitID;


	_pos.x = pos.x-_size.x/2+size.x/2;
	_pos.y = pos.y-_size.y+20;

	_posOld = _pos;


	Init();


}

LevelUp::~LevelUp()
{
}

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

	DestroyPrpc();

	if ((*plObj)._pos != (*plObj)._posOld)
	{
		_pos = (*plObj)._pos - (*plObj)._posOld + _posOld;

	}


}

bool LevelUp::SetAlive(bool alive)
{
	if (!alive)
	{
		// ‰æ–Ê—h‚ç‚µ‚ÌQUE‚ð“Š‚°‚é
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
