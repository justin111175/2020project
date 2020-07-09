#include <Dxlib.h>
#include <_DeBugConOut.h>
#include <GameScene.h>
#include <ImageMng.h>
#include <algorithm>
#include <Vector2.h>
#include <SceneMng.h>
#include <Obj.h>
#include <Player.h>
#include <Enemy.h>
#include <KeyState.h>
#include <Number.h>
#include <Floor.h>
#include "_DebugDispOut.h"


GameScene::GameScene()
{	
	funcInit();
	
	IpImageMng.GetID("プレイヤー歩く", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("プレイヤー死ぬ", "image/Player/dead.png", { 50,55 }, { 3,1 });

	IpImageMng.GetID("モンスター歩く", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("弾", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("斬撃", "image/slash.png", { 39,37 }, { 1,1 });

	IpImageMng.GetID("斬撃1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("斬撃2", "image/slash2.png", { 37,49 }, { 1,1 });

	IpImageMng.GetID("weapons", "image/weapons.png", { 98,65 }, { 3,4 });



	IpImageMng.GetID("メニュー", "image/mean.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("メッセージ", "image/messagecursor.png", { 50,78 }, { 1,1 });
	IpImageMng.GetID("ステータス", "image/status.png", { 1280,720 }, { 1,1 });


	IpImageMng.GetID("装備", "image/Equipment.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("加減", "image/1.png", { 186,50 }, { 1,1 });
	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });

	IpImageMng.GetID("Bar", "image/bar.png", { 510,66 }, { 1,1 });

	IpImageMng.GetID("HP", "image/gaugeB.png", { 325,22 }, { 1,1 });
	IpImageMng.GetID("MP", "image/gaugeB (1).png", { 325,22 }, { 1,1 });
	IpImageMng.GetID("敵HP", "image/EnemyHp.png", { 60,18 }, { 1,1 });
	IpImageMng.GetID("敵HP_BAR", "image/EnemyHpBar.png", { 60,18 }, { 1,1 });



	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });

	IpImageMng.GetID("UP1", "image/levelUp1.png", { 250,150 }, { 1,8 });

	IpImageMng.GetID("文字", "image/letter.png", { 1280,720 }, { 1,1 });

	IpImageMng.GetID("UI背景", "image/UI_back.png", { 480,480 }, { 1,1 });


	
	

	MapBG();
	//IpSceneMng._chipType.first = CHIP_TYPE::森1;

	//_Init[IpSceneMng._chipType.first]();



	_input = std::make_shared<KeyState>();


	_shakeCount = 0;


}


GameScene::~GameScene()
{
	
}

unique_Base GameScene::Update(unique_Base own)
{


	// 描画
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


	(*_input).Update();

	_Draw[IpSceneMng._chipType.first]();


	if (IpSceneMng._chipType.first == CHIP_TYPE::MAX)
	{
		if (Clear())
		{
			return std::make_unique<LoadScene>();

		}
	}

	// 描画を消す
	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());


	
	return std::move(own);
}

bool GameScene::Clear(void)
{
	_Init.clear();
	_objList.clear();
	return true;

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
void GameScene::MapBG(void)
{




	_Draw.try_emplace(CHIP_TYPE::森1, [&]() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("森1")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });

	});
	
	_Draw.try_emplace(CHIP_TYPE::森2, [&]() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("森2")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });

	});
	_Draw.try_emplace(CHIP_TYPE::森3, [&]() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("森3")[0], {0 ,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });

	});
	_Draw.try_emplace(CHIP_TYPE::MAX, []() {
		//何もない

	});
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




void GameScene::funcInit(void)
{
	funcQue[ACT_QUE::SHOT] = FuncBullet();

	funcQue[ACT_QUE::SLASH] = FuncSlash();
	funcQue[ACT_QUE::LEVELUP] = FuncLevelUp();
	funcQue[ACT_QUE::CHECK] = FuncCheck();
	funcQue[ACT_QUE::MOVE] = FuncMove();

}