#include "Floor.h"
#include "ImageMng.h"
#include "_DeBugConOut.h"

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
	A1_ID= std::get<static_cast<int>(FLOOR_STATE::ID)>(state);
	Init();


}

void Floor::Update(sharedObj plObj)
{



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
	case FLOOR_TYPE::Outside_A1_ID:
		for (auto i : Outside_A1_ID())
		{
			//switch (A1_ID)
			//{
			//case static_cast<int>(i):


			//	break;

			//default:
			//	break;
			//}
			if (A1_ID == i)
			{
				data.emplace_back(IMAGE_ID("Outside_A1")[static_cast<int>(i)], 30);
				SetAnim(STATE::NORMAL, data);
			}
		}

		break;
	default:
		break;
	}




	state(STATE::NORMAL);

}
