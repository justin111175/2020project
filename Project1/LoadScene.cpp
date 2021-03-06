#include "LoadScene.h"
#include <ImageMng.h>
#include "Scene/SceneMng.h"
#include <Player.h>
#include <Enemy.h>
#include <Number.h>
#include <Floor.h>

LoadScene::LoadScene()
{
	Clear();
	IpImageMng.GetID("vC[à­", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("vC[Ê", "image/Player/dead.png", { 50,55 }, { 3,1 });

	IpImageMng.GetID("X^[à­", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("e", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("a", "image/slash.png", { 39,37 }, { 1,1 });

	IpImageMng.GetID("a1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("a2", "image/slash2.png", { 37,49 }, { 1,1 });

	IpImageMng.GetID("weapons", "image/weapons.png", { 98,65 }, { 3,4 });



	IpImageMng.GetID("j[", "image/mean.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("bZ[W", "image/messagecursor.png", { 50,78 }, { 1,1 });
	IpImageMng.GetID("Xe[^X", "image/status.png", { 1280,720 }, { 1,1 });


	IpImageMng.GetID("õ", "image/Equipment.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("Á¸", "image/1.png", { 186,50 }, { 1,1 });
	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });

	IpImageMng.GetID("Bar", "image/bar.png", { 510,66 }, { 1,1 });

	IpImageMng.GetID("HP", "image/gaugeB.png", { 325,22 }, { 1,1 });
	IpImageMng.GetID("MP", "image/gaugeB (1).png", { 325,22 }, { 1,1 });
	IpImageMng.GetID("GHP", "image/EnemyHp.png", { 60,18 }, { 1,1 });
	IpImageMng.GetID("GHP_BAR", "image/EnemyHpBar.png", { 60,18 }, { 1,1 });



	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });

	IpImageMng.GetID("UP1", "image/levelUp1.png", { 250,150 }, { 1,8 });

	IpImageMng.GetID("¶", "image/letter.png", { 1280,720 }, { 1,1 });

	IpImageMng.GetID("UIwi", "image/UI_back.png", { 480,480 }, { 1,1 });


	MapInit();
	
	IpSceneMng._chipType.first = CHIP_TYPE::X3;
	//if (IpSceneMng._chipType.second == CHIP_TYPE::X1)
	//{
	//	IpSceneMng._chipType.first = CHIP_TYPE::X2;
	//}
	//else if (IpSceneMng._chipType.second == CHIP_TYPE::X2)
	//{
	//	IpSceneMng._chipType.first = CHIP_TYPE::X3;
	//}


	_Init[IpSceneMng._chipType.first]();

}

LoadScene::~LoadScene()
{
}

unique_Base LoadScene::Update(unique_Base own)
{
	//if (!FadeUpdate())
	//{
	//	for (auto data : _objList)
	//	{
	//		(*data).Update();
	//	}
	//}

	//for (auto data : _objList)
	//{

	//	(*data).Draw();
	//}




	////if (IpSceneMng._chipType.first == CHIP_TYPE::MAX)
	////{
	////	return std::make_unique<GameScene>();
	////}

	//// `æðÁ·
	_objList.erase(std::remove_if(
		_objList.begin(),									// `FbNÍÍÌJn
		_objList.end(),										// `FbNÍÍÌI¹
		[](sharedObj& obj) {return (*obj).isDead(); }),		// _®()
		_objList.end());

	return std::make_unique<GameScene>();


	
}





void LoadScene::Clear(void)
{
	_Init.clear();
	_objList.clear();

}

// NX1
void LoadScene::MapInit(void)
{

	_Init.try_emplace(CHIP_TYPE::X1, [&]() {
		IpSceneMng.mapSize = { 2880,2880 };
		// `æðÇÝÞ
		for (int x = 0; x < 90 * 90; x++)
		{
			IpSceneMng._mapNow.try_emplace(x, NULL);
		}

		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });

		IpImageMng.GetID("X1", "image/chip/X1.png", { 2880,2880 }, { 1,1 });

		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/X1.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._mapNow[x] = type;
			x++;
		}

		FloorState Flrdata;

		MoveState tmpMoveState;

		for (int x = 0; x < 90 * 90; x++)
		{
			if (IpSceneMng._mapNow[x] == 0)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{32.0 * (x % 90),32.0 * (x / 90)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
			}

			if (IpSceneMng._mapNow[x] == 1)
			{
				_objList.emplace_back(new Player({ 32.0 * (x % 90),32.0 * (x / 90) }, { 32,32 }, { 1.0f,1.0f }));

			}

			if (IpSceneMng._mapNow[x] == 10)
			{
				Flrdata = { FLOOR_TYPE::`,{32.0 * (x % 90),32.0 * (x / 90)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));

			}

		}


		//GÁ|_®
		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });

			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
			_objList.emplace_back(new Enemy(data));
		};

		for (int x = 0; x < 1; x++)
		{
			for (int y = 0; y < 1; y++)
			{
				EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
			}
		}
		return true;


	});


	_Init.try_emplace(CHIP_TYPE::X2, [&]() {
		IpSceneMng.mapSize = { 3840,2432 };



		// `æðÇÝÞ
		for (int x = 0; x < 120 * 76; x++)
		{
			IpSceneMng._mapNow.try_emplace(x, NULL);
		}

		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });

		IpImageMng.GetID("X2", "image/chip/X2.png", { 3840,2432 }, { 1,1 });

		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/X2.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._mapNow[x] = type;
			x++;
		}

		FloorState Flrdata;

		MoveState tmpMoveState;

		for (int x = 0; x < 120 * 76; x++)
		{
			if (IpSceneMng._mapNow[x] == 0)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{32.0 * (x % 120),32.0 * (x / 120)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
			}

			if (IpSceneMng._mapNow[x] == 1)
			{
				_objList.emplace_back(new Player({ 32.0 * (x % 120),32.0 * (x / 120) }, { 32,32 }, { 1.0f,1.0f }));

			}

			if (IpSceneMng._mapNow[x] == 10)
			{
				Flrdata = { FLOOR_TYPE::`,{32.0 * (x % 120),32.0 * (x / 120)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));

			}

		}

		//GÁ|_®
		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });

			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
			_objList.emplace_back(new Enemy(data));
		};

		for (int x = 0; x < 1; x++)
		{
			for (int y = 0; y < 1; y++)
			{
				EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
			}
		}

		return true;


	});


	_Init.try_emplace(CHIP_TYPE::X3, [&]() {
		IpSceneMng.mapSize = { 1440,1440 };



		// `æðÇÝÞ
		for (int x = 0; x < 45 * 45; x++)
		{
			IpSceneMng._mapNow.try_emplace(x, NULL);
		}

		IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });
		IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1 });

		IpImageMng.GetID("X3", "image/chip/X3.png", { 1440,1440 }, { 1,1 });

		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/X3.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._mapNow[x] = type;
			x++;
		}

		FloorState Flrdata;

		MoveState tmpMoveState;

		for (int x = 0; x < 45 * 45; x++)
		{
			if (IpSceneMng._mapNow[x] == 0)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{32.0 * (x % 45),32.0 * (x / 45)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
			}

			if (IpSceneMng._mapNow[x] == 1)
			{
				_objList.emplace_back(new Player({ 32.0 * (x % 45),32.0 * (x / 45) }, { 32,32 }, { 1.0f,1.0f }));

			}

			if (IpSceneMng._mapNow[x] == 10)
			{
				Flrdata = { FLOOR_TYPE::`,{32.0 * (x % 45),32.0 * (x / 45)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));

			}

		}

		//GÁ|_®
		auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
			MoveState tmpMoveState;
			tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
			tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });

			EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
			_objList.emplace_back(new Enemy(data));
		};

		for (int x = 0; x < 1; x++)
		{
			for (int y = 0; y < 1; y++)
			{
				EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
			}
		}
		
		
		return true;

	});



}