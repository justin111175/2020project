#include "level.h"




void level::Init(void)
{


	for (int x=1; x <= LevelMax; x++)
	{
		experience[x] = 100*x;
	}

	_status[STATUS::HP] = 100;
	_status[STATUS::レベル] = 1;
	_status[STATUS::お金] = 999999;
	_status[STATUS::攻撃力] = 0;
	_status[STATUS::防御力] = 0;
	_status[STATUS::敏捷] = 0;
	_status[STATUS::回復] = 0;

	_statusUp[STATUS_UP::強化_回復] = 10;
	_statusUp[STATUS_UP::強化_攻撃力] =99;
	_statusUp[STATUS_UP::強化_最大HP] =99;
	_statusUp[STATUS_UP::強化_最大MP] = 99;
	_statusUp[STATUS_UP::強化_敏捷] = 99;
	_statusUp[STATUS_UP::強化_防御力] = 99;
	_statusUp[STATUS_UP::残るボーナスポイント] = 99;

}

