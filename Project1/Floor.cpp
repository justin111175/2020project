#include "Floor.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"
#include <Dxlib.h>
#include "SceneMng.h"

Floor::Floor()
{
	Init();


}

Floor::Floor(FloorState & state)
{	


	_exrate = { 1.0f,1.0f };

	_type = std::get<static_cast<int>(FLOOR_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(FLOOR_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(FLOOR_STATE::SIZE)>(state));
	_zorder = 0;


	Init();


}

void Floor::Update(sharedObj plObj)
{
	//IpSceneMng.AddDrawQue({ IMAGE_ID("1_1")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });

}

Floor::~Floor()
{
}

void Floor::Init(void)
{
	_unitID = UNIT_ID::FLOOR;
	AnimVector data;
	_zorder = -1;
	switch (_type)
	{
	case FLOOR_TYPE::�����蔻��:
		data.emplace_back(IMAGE_ID("block")[0], 30);
		SetAnim(STATE::NORMAL, data);
		break;
	default:
		break;
	}


	stateDir(STATE::NORMAL,DIR_ID::DOWN);

}
