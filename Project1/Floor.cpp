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
	Init();


}

void Floor::Update(sharedObj plObj)
{
	TRACE("%f,%f\n", _pos.x,_pos.y);



}

Floor::~Floor()
{
}

void Floor::Init(void)
{
	_unitID = UNIT_ID::FLOOR;
	AnimVector data;


	switch (_type)
	{
	case FLOOR_TYPE::�h���S��_��_1:
		data.emplace_back(IMAGE_ID("Outside_A5")[76], 30);
		SetAnim(STATE::NORMAL, data);

		break;
	case FLOOR_TYPE::�h���S��_��_2:
		data.emplace_back(IMAGE_ID("Outside_A5")[77], 30);
		SetAnim(STATE::NORMAL, data);

		break;
	case FLOOR_TYPE::�h���S��_��_3:
		data.emplace_back(IMAGE_ID("Outside_A5")[76+8], 30);
		SetAnim(STATE::NORMAL, data);

		break;
	case FLOOR_TYPE::�h���S��_��_4:
		data.emplace_back(IMAGE_ID("Outside_A5")[76+9], 30);
		SetAnim(STATE::NORMAL, data);

		break;
	//case FLOOR_TYPE::�h���S��_�E_1:
	//	break;
	//case FLOOR_TYPE::�h���S��_�E_2:
	//	break;
	//case FLOOR_TYPE::�h���S��_�E_3:
	//	break;
	//case FLOOR_TYPE::�h���S��_�E_4:
	//	break;
	default:
		break;
	}




	state(STATE::NORMAL);

}
