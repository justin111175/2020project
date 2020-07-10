#include "GameScene.h"
#include <Dxlib.h>
#include "common/ImageMng.h"

GameScene::GameScene()
{
	IpImageMng.GetID("1", "image/1.png", { 2400,2400 }, { 1,1 });

	_mapState=std::make_unique<MapState>(Vector2{2400,2400});
	_player = std::make_unique<Player>(std::move(Vector2(0, 0)));

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{

	Draw();



	_mapState->Run();
	

	_player->Run();


	if (_player->_pos.x + mapPos.x > 640)
	{
		mapPos.x--;
	}
	if (_player->_pos.y + mapPos.y > 400)
	{
		mapPos.y--;
	}
	//if (CheckHitKey(KEY_INPUT_RIGHT))
	//{
	//	mapPos.x+=10;
	//}
	//if (CheckHitKey(KEY_INPUT_LEFT))
	//{
	//	mapPos.x-=10;
	//}
	//if (CheckHitKey(KEY_INPUT_UP))
	//{
	//	mapPos.y-=10;
	//}
	//if (CheckHitKey(KEY_INPUT_DOWN))
	//{
	//	mapPos.y+=10;
	//}

	return std::move(own);
}

void GameScene::Draw(void)
{
	ClsDrawScreen();

	_mapState->Draw();
	
	_player->Draw();

	SetDrawScreen(DX_SCREEN_BACK);

	//SetDrawScreen(DX_SCREEN_BACK);


	DrawGraph(mapPos.x, mapPos.y, _mapState->GetScreenId(), true);
	DrawGraph(0,0, _player->GetScreenId(), true);
	


	ScreenFlip();


}

