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


GameScene::GameScene()
{	
	funcInit();
	

		
	// 描画を増加
	IpImageMng.GetID("プレイヤー歩く", "image/Player/walk.png", { 48,49 }, { 3,4 });
	IpImageMng.GetID("プレイヤー死ぬ", "image/Player/dead.png", { 50,55 }, { 3,1 });
	
	IpImageMng.GetID("モンスター歩く", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("弾", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("斬撃", "image/slash.png", { 39,37 }, { 1,1 });
	IpImageMng.GetID("斬撃1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("斬撃2", "image/slash2.png", { 37,49 }, { 1,1 });
	IpImageMng.GetID("斬撃3", "image/Sword.png", { 380,384 }, { 2,7 });

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
	
	
	
	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });
	
	IpImageMng.GetID("UP", "image/levelUp.png", { 450,250 }, { 1,8 });
	IpImageMng.GetID("UP1", "image/levelUp1.png", { 250,150 }, { 1,8 });

	IpImageMng.GetID("文字", "image/letter.png", { 1280,720 }, { 1,1 });


	
	_objList.emplace_back(new Player({ 0,0 }, { 48,49 }, {1.0f,1.0f}));



	MapInit_1();
	
	


	_input = std::make_shared<KeyState>();


	_shakeCount = 0;
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Update(unique_Base own)
{
	// 描画
	auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

	if (!FadeUpdate())
	{
		for (auto data : _objList)
		{
			(*data).Update(*PlObj);
		}
	}

	for (auto data : _objList)
	{

		(*data).Draw();
	}
	



	(*_input).Update();







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
	
	//IpImageMng.GetID("Outside_A2", "image/chip/Outside_A2.png", { 768,576 }, { 16,12 });

	IpImageMng.GetID("Outside_A1", "image/chip/Outside_A1.png", { 48,48 }, { 8,16 });

	// csvファイルを読み込む
	int type = NULL;
	int y = 0;
	int x = 0;
	FILE* fp = NULL;
	fopen_s(&fp, "csv/test1.csv", "rb");
	while (fscanf_s(fp, "%d", &type) != EOF)
	{
		IpSceneMng.mapNow[y][x] = type;
		x++;
	}
	
	
	FloorState Flrdata;


	MoveState tmpMoveState;
	for (auto i : Outside_A1_ID())
	{

		for (int x = 0; x < 50; x++)
		{
			for (int y = 0; y < 20; y++)
			{

				if (IpSceneMng.mapNow[y][x] == static_cast<int>(i))
				{
					Flrdata = { FLOOR_TYPE::Outside_A1_ID,{48.0*x,48.0*y},{48.0,48.0} ,i };
					_objList.emplace_back(new Floor(Flrdata));
				}
			}
		}
		
	}

	//敵増加－ラムダ式
	auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
		MoveState tmpMoveState;
		tmpMoveState.emplace_back(MOVE_TYPE::RIGHT, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(MOVE_TYPE::DOWN, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(MOVE_TYPE::LEFT, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(MOVE_TYPE::UP, Vector2Dbl{ 0,0 });

		EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
		_objList.emplace_back(new Enemy(data));
	};

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			EnemyAdd(ENEMY_TYPE::コウモリ, _objList, { 400.0 + x * 30.0,300.0 + y * 30 }, { 48.0,48.0 }, { 1.0f,1.0f });

		}
	}

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

}