#include <Dxlib.h>
#include "MapState.h"
#include "common/ImageMng.h"

MapState::MapState(Vector2 size)
{
	_size = size;
	Init();


}

MapState::~MapState()
{
}

int MapState::GetScreenId(void)
{
	return screenID;
}

void MapState::Draw(void)
{
	SetDrawScreen(screenID);

	ClsDrawScreen();

	DrawGraph(0, 0, IMAGE_ID("1")[0], true);





}

void MapState::Run(void)
{



}

void MapState::Init(void)
{


	screenID = MakeScreen(_size.x, _size.y, true);


}
