#include "level.h"




void Level::Init(void)
{


	level = 1;

	_status[STATUS::HP] = 100;
	_status[STATUS::MP] = 100;
	_status[STATUS::����] = 9999;
	_status[STATUS::�U����] = 0;
	_status[STATUS::�h���] = 0;
	_status[STATUS::�q��] = 0;
	_status[STATUS::��] = 0;

	_statusUp[STATUS_UP::����_��] = 10;
	_statusUp[STATUS_UP::����_�U����] =0;
	_statusUp[STATUS_UP::����_�ő�HP] =0;
	_statusUp[STATUS_UP::����_�ő�MP] = 0;
	_statusUp[STATUS_UP::����_�q��] = 0;
	_statusUp[STATUS_UP::����_�h���] = 0;
	_statusUp[STATUS_UP::�c��{�[�i�X�|�C���g] = 5;


}

void Level::Updata(void)
{
	_status[STATUS::�U����] = _statusUp[STATUS_UP::����_�U����]*1.3;
	_status[STATUS::�h���] = _statusUp[STATUS_UP::����_�h���] * 1.3;
	

	_status[STATUS::HP] = BaseHP + ((level * 100) * 3 / 10)+_statusUp[STATUS_UP::����_�ő�HP] * 30;
	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::����_�ő�MP] * 30;
	
	_status[STATUS::��] = _statusUp[STATUS_UP::����_��] * 1.3;

	_status[STATUS::�q��] = _statusUp[STATUS_UP::����_�q��] * 1.3;

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
//	//data.emplace_back(IMAGE_ID("�a��2")[0], 0);
//	//for (int i = 0; i < 7; i++)
//	//{
//	//	data.emplace_back(IMAGE_ID("�a��3")[i], i*5);
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
//		// ��ʗh�炵��QUE�𓊂���
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
