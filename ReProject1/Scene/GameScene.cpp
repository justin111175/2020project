#include "GameScene.h"
#include <Dxlib.h>
#include "..\common\ImageMng.h"
#include "SceneMng.h"
#include "..\Player.h"
#include "..\Floor.h"
#include "..\Remove.h"



GameScene::GameScene()
{
	IpImageMng.GetID("vC[à­", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("block", "image/block.png", { 32,32 }, { 10,2 });
	IpImageMng.GetID("âÕ1", "image/âÕ1.png", { 1280,1280 }, { 1,1 });
	
	MapInit();
	ChangeInit();
	FuncInit();


	IpSceneMng._changeFlag = false;


	


	_Init[IpSceneMng._chipNo.first]();
	//_Init[CHIP_TYPE::n}3]();

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	if (IpSceneMng._changeFlag)
	{
		IpSceneMng._chipNo.second = IpSceneMng._chipNo.first;
		_Change[IpSceneMng._chipNo.first]();
		//_Change[CHIP_TYPE::n}3]();

		Clear();
		return std::make_unique<GameScene>();

	}

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

	//IpSceneMng.AddDrawQue({ IMAGE_ID("block")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG});
	
	_Draw[IpSceneMng._chipNo.first]();
	//_Draw[CHIP_TYPE::n}3]();
	



	// `æðÁ·
	_objList.erase(std::remove_if(
		_objList.begin(),									// `FbNÍÍÌJn
		_objList.end(),										// `FbNÍÍÌI¹
		[](sharedObj& obj) {return (*obj).isDead(); }),		// _®()
		_objList.end());
	
	return std::move(own);
}

void GameScene::FuncInit(void)
{

	//funcQue[ACT_QUE::SHOT] = FuncBullet();

	//funcQue[ACT_QUE::SLASH] = FuncSlash();
	//funcQue[ACT_QUE::LEVELUP] = FuncLevelUp();
	funcQue[ACT_QUE::CHECK] = FuncCheck();


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
	_Init.try_emplace(CHIP_TYPE::n}1, [&]() {
		
		IpSceneMng.mapSize = { 960,960 };
		int blocksize =32;

		Vector2 ChipMax = IpSceneMng.mapSize/ blocksize;
		// `æðÇÝÞ
		IpSceneMng._dataBase.resize((__int64)ChipMax .x* ChipMax.y);
		for (size_t no = 0; no < ChipMax.y; no++)
		{
			IpSceneMng._data.emplace_back(&IpSceneMng._dataBase[no * ChipMax.y]);
		}


		IpImageMng.GetID("Map001", "image/Map001.png", IpSceneMng.mapSize, { 1,1 });


		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/1.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._dataBase[x] = type;
			x++;
		}


		if (IpSceneMng._chipNo.second == CHIP_TYPE::n}1)
		{
			_objList.emplace_back(new Player({832,704}, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 160,360 };

		}
		else
		{
			_objList.emplace_back(new Player({ 448,192 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 48,0 };


		}


		

		FloorState Flrdata;
		RemoveState RemovaData;

		for (int x = 0; x < ChipMax.x * ChipMax.y; x++)
		{
			if (IpSceneMng._dataBase[x] == 1)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._dataBase[x] == 2)
			{
				RemovaData = { Remove_ID::test1,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Remove(RemovaData));
			}


		}



		////GÁ|_®
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
		//		EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});

	_Init.try_emplace(CHIP_TYPE::n}2 , [&]() {

		IpSceneMng.mapSize = { 960,1248 };
		int blocksize = 32;

		Vector2 ChipMax = IpSceneMng.mapSize / blocksize;
		// `æðÇÝÞ
		IpSceneMng._dataBase.resize((__int64)ChipMax.x * ChipMax.y);
		for (size_t no = 0; no < ChipMax.y; no++)
		{
			IpSceneMng._data.emplace_back(&IpSceneMng._dataBase[no * ChipMax.x]);
		}


		IpImageMng.GetID("Map002", "image/Map002.png", IpSceneMng.mapSize, { 1,1 });


		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/2.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._dataBase[x] = type;
			x++;
		}

		if (IpSceneMng._chipNo.second == CHIP_TYPE::n}1)
		{
			_objList.emplace_back(new Player({ 480,1184 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 80,648 };

		}
		else
		{
			_objList.emplace_back(new Player({ 96,64 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 0,0 };


		}



		FloorState Flrdata;
		RemoveState RemovaData;

		for (int x = 0; x < ChipMax.x * ChipMax.y; x++)
		{
			if (IpSceneMng._dataBase[x] == 1)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._dataBase[x] == 2)
			{
				RemovaData = { Remove_ID::test1,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Remove(RemovaData));
			}


		}



		////GÁ|_®
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
		//		EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});

	_Init.try_emplace(CHIP_TYPE::n}3, [&]() {

		IpSceneMng.mapSize = { 832,800 };
		int blocksize = 32;

		Vector2 ChipMax = IpSceneMng.mapSize / blocksize;
		// `æðÇÝÞ
		IpSceneMng._dataBase.resize((__int64)ChipMax.x * ChipMax.y);
		for (size_t no = 0; no < ChipMax.y; no++)
		{
			IpSceneMng._data.emplace_back(&IpSceneMng._dataBase[no * ChipMax.x]);
		}


		IpImageMng.GetID("Map003", "image/Map003.png", IpSceneMng.mapSize, { 1,1 });


		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/3.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._dataBase[x] = type;
			x++;
		}


		if (IpSceneMng._chipNo.second == CHIP_TYPE::n}2)
		{
			_objList.emplace_back(new Player({ 64,704 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 0,200 };

		}
		else
		{
			_objList.emplace_back(new Player({ 704,64 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 32,0 };


		}


		FloorState Flrdata;
		RemoveState RemovaData;

		for (int x = 0; x < ChipMax.x * ChipMax.y; x++)
		{
			if (IpSceneMng._dataBase[x] == 1)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._dataBase[x] == 2)
			{
				RemovaData = { Remove_ID::test1,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Remove(RemovaData));
			}


		}



		////GÁ|_®
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
		//		EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});

	_Init.try_emplace(CHIP_TYPE::n}4, [&]() {

		IpSceneMng.mapSize = { 960,1120 };
		int blocksize = 32;

		Vector2 ChipMax = IpSceneMng.mapSize / blocksize;
		// `æðÇÝÞ
		IpSceneMng._dataBase.resize((__int64)ChipMax.x * ChipMax.y);
		for (size_t no = 0; no < ChipMax.y; no++)
		{
			IpSceneMng._data.emplace_back(&IpSceneMng._dataBase[no * ChipMax.x]);
		}


		IpImageMng.GetID("Map004", "image/Map004.png", IpSceneMng.mapSize, { 1,1 });


		// csvt@CðÇÝÞ
		int type = NULL;
		int y = 0;
		int x = 0;

		FILE* fp = NULL;
		fopen_s(&fp, "csv/4.csv", "rb");
		while (fscanf_s(fp, "%d", &type) != EOF)
		{
			IpSceneMng._dataBase[x] = type;
			x++;
		}



		if (IpSceneMng._chipNo.second == CHIP_TYPE::n}3)
		{
			_objList.emplace_back(new Player({ 768,1024 }, { 32,32 }, { 1.0f,1.0f }));
			IpSceneMng.mapPos = { 160,520 };

		}
		//else
		//{
		//	_objList.emplace_back(new Player({ 704,64 }, { 32,32 }, { 1.0f,1.0f }));
		//	IpSceneMng.mapPos = { 32,0 };


		//}

		FloorState Flrdata;
		RemoveState RemovaData;

		for (int x = 0; x < ChipMax.x * ChipMax.y; x++)
		{
			if (IpSceneMng._dataBase[x] == 1)
			{
				Flrdata = { FLOOR_TYPE::½è»è,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._dataBase[x] == 2)
			{
				RemovaData = { Remove_ID::test1,{blocksize * (x % ChipMax.x),blocksize * (x / ChipMax.x)},{32.0,32.0} };
				_objList.emplace_back(new Remove(RemovaData));
			}


		}



		////GÁ|_®
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
		//		EnemyAdd(ENEMY_TYPE::RE, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});
	_Draw.try_emplace(CHIP_TYPE::n}1, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("Map001")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });

	
	});

	_Draw.try_emplace(CHIP_TYPE::n}2, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("Map002")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });


	});
	_Draw.try_emplace(CHIP_TYPE::n}3, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("Map003")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });


	});
	_Draw.try_emplace(CHIP_TYPE::n}4, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("Map004")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });


	});



}

void GameScene::Clear(void)
{
	_objList.clear();
	_Draw.clear();
	_Init.clear();
	IpSceneMng._dataBase.clear();
	IpSceneMng._data.clear();

}

void GameScene::ChangeInit(void)
{

	_Change.try_emplace(CHIP_TYPE::n}1, [&]() {

		auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

		if ((*PlObj)->posGet() == Vector2(448, 188) )
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}2;
		}

	});

	_Change.try_emplace(CHIP_TYPE::n}2, [&]() {

		auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });


		if ((*PlObj)->posGet().y >IpSceneMng.mapSize.y/2)
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}1;
		}
		if ((*PlObj)->posGet().y < IpSceneMng.mapSize.y / 2)
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}3;
		}
	});
	
	_Change.try_emplace(CHIP_TYPE::n}3, [&]() {

		auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

		if ((*PlObj)->posGet().y > IpSceneMng.mapSize.y / 2)
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}2;
		}
		if ((*PlObj)->posGet().y < IpSceneMng.mapSize.y / 2)
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}4;
		}
	});
	
	_Change.try_emplace(CHIP_TYPE::n}4, [&]() {

		auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

		if ((*PlObj)->posGet().y > IpSceneMng.mapSize.y / 2)
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::n}3;
		}
		//if ((*PlObj)->posGet() == Vector2(704, 60))
		//{
		//	IpSceneMng._chipNo.first = CHIP_TYPE::n}4;
		//}
	});
}




