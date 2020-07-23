#include "Remove.h"
#include "common/ImageMng.h"


Remove::Remove(RemoveState& state)
{
	_exrate = { 1.0f,1.0f };

	_id = std::get<static_cast<int>(Remove_State::ID)>(state);
	_pos = std::move(std::get<static_cast<int>(Remove_State::���W)>(state));
	_size = std::move(std::get<static_cast<int>(Remove_State::�T�C�Y)>(state));
	_zorder = 0;

	Init();

}

Remove::~Remove()
{
}

void Remove::Update(void)
{



}

void Remove::Init(void)
{

	AnimVector data;
	_zorder = -1;
	_unitID = UNIT_ID::�`��;
	data.emplace_back(IMAGE_ID("block")[2], 30);
	SetAnim(STATE::NORMAL, data);


	stateDir(STATE::NORMAL);


}
