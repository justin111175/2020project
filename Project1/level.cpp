#include "level.h"




void Level::Init(void)
{


	level = 1;

	_status[STATUS::HP] = 100;
	_status[STATUS::MP] = 100;
	_status[STATUS::¨à] = 9999;
	_status[STATUS::UÍ] = 0;
	_status[STATUS::häÍ] = 0;
	_status[STATUS::q·] = 0;
	_status[STATUS::ñ] = 0;

	_statusUp[STATUS_UP::­»_ñ] = 10;
	_statusUp[STATUS_UP::­»_UÍ] =0;
	_statusUp[STATUS_UP::­»_ÅåHP] =0;
	_statusUp[STATUS_UP::­»_ÅåMP] = 0;
	_statusUp[STATUS_UP::­»_q·] = 0;
	_statusUp[STATUS_UP::­»_häÍ] = 0;
	_statusUp[STATUS_UP::cé{[iX|Cg] = 5;


}

void Level::Updata(void)
{
	_status[STATUS::UÍ] = _statusUp[STATUS_UP::­»_UÍ]*1.3;
	_status[STATUS::häÍ] = _statusUp[STATUS_UP::­»_häÍ] * 1.3;
	

	_status[STATUS::HP] = BaseHP + ((level * 100) * 3 / 10)+_statusUp[STATUS_UP::­»_ÅåHP] * 30;
	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::­»_ÅåMP] * 30;
	
	_status[STATUS::ñ] = _statusUp[STATUS_UP::­»_ñ] * 1.3;

	_status[STATUS::q·] = _statusUp[STATUS_UP::­»_q·] * 1.3;

}

//Up::Up()
//{
//	Init();
//}
//
//Up::Up(Vector2Dbl pos, Vector2Dbl size)
//{
//	_pos = pos;
//	_exrate = { 1.0f,1.0f };
//	Init();
//}
//
//Up::~Up()
//{
//}
//
//void Up::Init(void)
//{
//	_alive = true;
//
//	_unitID = UNIT_ID::PLaS;
//
//	AnimVector data;
//	data.reserve(1);
//	//data.emplace_back(IMAGE_ID("a2")[0], 0);
//	//for (int i = 0; i < 7; i++)
//	//{
//	//	data.emplace_back(IMAGE_ID("a3")[i], i*5);
//	//}
//	//data.emplace_back(-1, 40);
//
//	SetAnim(STATE::NORMAL, data);
//
//
//
//
//	data.reserve(1);
//	data.emplace_back(-1, 40);
//	SetAnim(STATE::DETH, data);
//
//	state(STATE::NORMAL);
//
//}
//
//void Up::Update(sharedObj plObj)
//{
//	DestroyPrpc();
//
//
//
//}
//
//bool Up::SetAlive(bool alive)
//{
//	if (!alive)
//	{
//		// æÊhçµÌQUEð°é
//		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
//	}
//
//	return Obj::SetAlive(alive);
//}
//
//bool Up::DestroyPrpc(void)
//{
//	if (Obj::DestroyPrpc())
//	{
//		return true;
//	}
//
//	return false;
//}
