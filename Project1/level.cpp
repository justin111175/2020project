#include "level.h"



////ステータスの初期化
//void Level::Init(void)
//{
//	level = 1;
//
//	_status[STATUS::HP] = 100;
//	_status[STATUS::MP] = 100;
//	_status[STATUS::お金] = 9999;
//	_status[STATUS::攻撃力] = 0;
//	_status[STATUS::防御力] = 0;
//	_status[STATUS::敏捷] = 0;
//	_status[STATUS::回復] = 0;
//
//	_statusUp[STATUS_UP::強化_回復] = 10;
//	_statusUp[STATUS_UP::強化_攻撃力] =0;
//	_statusUp[STATUS_UP::強化_最大HP] =0;
//	_statusUp[STATUS_UP::強化_最大MP] = 0;
//	_statusUp[STATUS_UP::強化_敏捷] = 0;
//	_statusUp[STATUS_UP::強化_防御力] = 0;
//	_statusUp[STATUS_UP::残るボーナスポイント] = 5;
//
//}
//
////ステータスの更新
//void Level::Updata(void)
//{
//	_status[STATUS::攻撃力] = static_cast<int>(_statusUp[STATUS_UP::強化_攻撃力]*1.3);
//	_status[STATUS::防御力] = static_cast<int>(_statusUp[STATUS_UP::強化_防御力] * 1.3);
//	
//
//	_status[STATUS::HP] = BaseHP + ((level * 100) * 3 / 10)+_statusUp[static_cast<int>(STATUS_UP::強化_最大HP)] * 30;
//	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::強化_最大MP] * 30;
//	
//	_status[STATUS::回復] = static_cast<int>(_statusUp[STATUS_UP::強化_回復] * 1.3);
//
//	_status[STATUS::敏捷] = static_cast<int>(_statusUp[STATUS_UP::強化_敏捷] * 1.3);
//
//}
//
//Level::~Level()
//{
//}

