#include "GameScene.h"
#include <Dxlib.h>
#include "..\common\ImageMng.h"
#include "SceneMng.h"
#include "..\Player.h"
#include "..\Floor.h"



GameScene::GameScene()
{

	FuncInit();

	IpImageMng.GetID("1", "image/1.png", { 2400,2400 }, { 1,1 });
	IpImageMng.GetID("プレイヤー歩く", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("block", "image/block.png", { 32,32 }, { 10,2 });



	MapInit();

	




	_Init[CHIP_TYPE::森1]();

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	if (!FadeUpdate())
	{
		for (auto data : _objList)
		{
			(*data).Update();
		}
	}

	for (auto data : _objList)
	{

		(*data).Draw();
	}

	IpSceneMng.AddDrawQue({ IMAGE_ID("1")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG});
	//IpSceneMng.AddDrawQue({ IMAGE_ID("block")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG});
	

	

	// 描画を消す
	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());
	
	return std::move(own);
}

void GameScene::FuncInit(void)
{

	//funcQue[ACT_QUE::SHOT] = FuncBullet();

	//funcQue[ACT_QUE::SLASH] = FuncSlash();
	//funcQue[ACT_QUE::LEVELUP] = FuncLevelUp();
	//funcQue[ACT_QUE::CHECK] = FuncCheck();

	funcQue[ACT_QUE::MOVE] = FuncMove();

}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	for (auto actQue : actList)
	{
		try
		{
			funcQue.at(actQue.first)(actQue, this);
		}
		catch (...)
		{
			//AST();
		}

	}


}

void GameScene::MapInit(void)
{
	_Init.try_emplace(CHIP_TYPE::森1, [&]() {
		
		IpSceneMng.mapSize = { 2400,2400 };
		// 描画を読み込む
		for (int x = 0; x < 75 * 75; x++)
		{
			IpSceneMng._mapNow.try_emplace(x, NULL);
		}

		//IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });


		// csvファイルを読み込む
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/1.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._mapNow[x] = type;
			x++;
		}




		FloorState Flrdata;


		for (int x = 0; x < 75 * 75; x++)
		{
			if (IpSceneMng._mapNow[x] == 0)
			{
				Flrdata = { FLOOR_TYPE::当たり判定,{32.0 * (x % 75),32.0 * (x / 75)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._mapNow[x] == 10)
			{
				_objList.emplace_back(new Player({ 32.0 * (x % 75),32.0 * (x / 75) }, { 32,32 }, { 1.0f,1.0f }));

			}

		}



		////敵増加－ラムダ式
		//auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
		//	MoveState tmpMoveState;
		//	tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
		//	tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
		//	tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
		//	tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });

		//	EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
		//	_objList.emplace_back(new Enemy(data));
		//};

		//for (int x = 0; x < 1; x++)
		//{
		//	for (int y = 0; y < 1; y++)
		//	{
		//		EnemyAdd(ENEMY_TYPE::コウモリ, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});


}




