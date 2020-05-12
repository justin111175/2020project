#include <Dxlib.h>
#include <_DeBugConOut.h>
#include <GameScene.h>
#include <ImageMng.h>
#include <algorithm>
#include <Vector2.h>
#include <SceneMng.h>
#include <Obj.h>

GameScene::GameScene()
{	
	//funcInit();
	
//	switch (IpSceneMng._classCnt)
//	{
//	case 1:
//		MapInit_1();
////		PlaySoundMem(IMAGE_SOUND("BGM1")[0], DX_PLAYTYPE_LOOP);
//		break;
//	case 2:
//		MapInit_2();
////		PlaySoundMem(IMAGE_SOUND("BGM2")[0], DX_PLAYTYPE_LOOP);
//		break;
//	case 3:
//		MapInit_3();
////		PlaySoundMem(IMAGE_SOUND("BGM3")[0], DX_PLAYTYPE_LOOP);
//		break;
//	default:
//		AST();
//		break;
//	}
		
	
// 描画を増加
	//_objList.emplace_back(new Player({ 0,0 }, { 30,30 }));

	_shakeCount = 0;
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Update(unique_Base own)
{
	// 描画
	//auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

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
		
	//IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0], 4096/2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });

	//switch (IpSceneMng._classCnt)
	//{
	//case 1:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("背景")[0], 4096*1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG});
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("エンド飾り_木")[0], 5960 - _mapPos.x,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;

	//case 2:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("背景2")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("背景2")[0], 4096 * 1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("エンド飾り_闇")[0], 5960 - _mapPos.x,800 / 2-250,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;
	//case 3:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("背景3")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("背景3")[0], 4096 * 1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG});
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("feed")[0], 6000 - _mapPos.x,800 / 2-100,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;	
	//default:
	//	// こないはず
	//	AST();
	//	break;
	//}



	// 描画を消す
	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());


	
	return std::move(own);
}

// ファンク活動キュー
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

// クラス1
void GameScene::MapInit_1(void)
{
	// 描画を読み込む
	//IpImageMng.GetID("UI", "image/UI.png", { 800,72 }, { 1,1 });
	//IpImageMng.GetID("プレイヤー1", "image/player1.png", { 40,40 }, { 3,4 });
	//
	//IpImageMng.GetID("背景", "image/BG.png", { 4096,800 }, { 1,1 });
	//IpImageMng.GetID("ブロック", "image/block.png", { 30,30 }, { 9,2 });
	//
	//IpImageMng.GetID("スライム", "image/enemy/slime.png", { 55,30 }, { 3,1 });
	//IpImageMng.GetID("コイン", "image/coin.png", { 25,24 }, { 4,1 });
	//
	//IpImageMng.GetID("end1", "image/end1.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end2", "image/end2.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end3", "image/end3.png", { 115,150 }, { 1,1 });
	//IpImageMng.GetID("end4", "image/end4.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end5", "image/end5.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end6", "image/end6.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end7", "image/end7.png", { 116,150 }, { 1,1 });
	//IpImageMng.GetID("end8", "image/end8.png", { 116,150 }, { 1,1 });
	//
	//IpImageMng.GetID("エンド飾り_木", "image/end_tree.png", { 453,600 }, { 1,1 });
	//_mapPos = { 0,0 };
	//
	// csvファイルを読み込む
	//int type = NULL;
	//int y = 0;
	//int x = 0;
	//FILE* fp = NULL;
	//fopen_s(&fp, "csv/1-1.csv", "rb");
	//while (fscanf_s(fp, "%d", &type) != EOF)
	//{
	//	IpSceneMng.mapNow[y][x] = type;
	//	x++;
	//}
	
	
	//FloorState Flrdata;
	//MoveState tmpMoveState;
	//
	//for (int y = 0; y < 20; y++)
	//{
	//	for (int x = 0; x < 220; x++)
	//	{
	//		switch (IpSceneMng.mapNow[y][x])
	//		{
	//		case 4:
	//			Flrdata = { FLOOR_TYPE::床1_草原,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 5:
	//			Flrdata = { FLOOR_TYPE::床2_草原,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,20} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 6:
	//			Flrdata = { FLOOR_TYPE::階段_光,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 13:
	//			Flrdata = { FLOOR_TYPE::レンガ,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 25},{30,25} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;

	//		default:
	//			break;
	//		}

	//		if (IpSceneMng.mapNow[y][x] == 26)
	//		{
	//			MoveState tmpMoveState;
	//			tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 0,0 });
	//			EnemyState data = { ENEMY_TYPE::スライム,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y}, { 43,20 },tmpMoveState };
	//			_objList.emplace_back(new Enemy(data));
	//		}
	//		if (IpSceneMng.mapNow[y][x] == 22)
	//		{
	//			MoveState tmpMoveState;
	//			IteamState data = { ITEAM_TYPE::コイン,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y}, { 25,24 } ,tmpMoveState };
	//			_objList.emplace_back(new iteam(data));

	//		}
	//		if (IpSceneMng.mapNow[y][x] == 25)
	//		{
	//			MoveState tmpMoveState;
	//			IteamState data = { ITEAM_TYPE::エンド,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y+30}, { 116,150 } ,tmpMoveState };
	//			_objList.emplace_back(new iteam(data));

	//		}
	//	}
	//}
}



//void GameScene::SoundInit(void)
//{
//	// 音の読み込み
//	IpImageMng.GetSound("コイン音", "image/sound/coin.mp3");
//	IpImageMng.GetSound("ジャンプ音", "image/sound/jump.wav");
//	IpImageMng.GetSound("敵当たり音", "image/sound/hitenemy.wav");
//	IpImageMng.GetSound("数字音", "image/sound/number.mp3");
//	//IpImageMng.GetSound("BGM1", "image/sound/BGM1.mp3");
//	//IpImageMng.GetSound("BGM2", "image/sound/BGM2.mp3");
//	//IpImageMng.GetSound("BGM3", "image/sound/BGM3.mp3");
//
//
//}

// ファンク初期化
//void GameScene::funcInit(void)
//{
//	funcQue[ACT_QUE::CHECK_SELF] = FuncCheckSelf();
//	funcQue[ACT_QUE::CHECK_DOWN] = FuncCheckDown();
//	funcQue[ACT_QUE::CHECK_RIFGT] = FuncCheckRight();
//	funcQue[ACT_QUE::CHECK_LEFT] = FuncCheckLeft();
//	funcQue[ACT_QUE::CHECK_ON] = FuncCheckOn();
//}


