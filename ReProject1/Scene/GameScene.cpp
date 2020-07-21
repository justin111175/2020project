#include "GameScene.h"
#include <Dxlib.h>
#include "..\common\ImageMng.h"
#include "SceneMng.h"
#include "..\Player.h"
#include "..\Floor.h"
#include "..\Remove.h"



GameScene::GameScene()
{
	IpImageMng.GetID("�v���C���[����", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("block", "image/block.png", { 32,32 }, { 10,2 });
	IpImageMng.GetID("���1", "image/���1.png", { 1280,1280 }, { 1,1 });
	
	MapInit();

	FuncInit();


	IpSceneMng._chipNo.second = false;


	


	_Init[CHIP_TYPE::�X1]();

}

GameScene::~GameScene()
{
}

unique_Base GameScene::Update(unique_Base own)
{
	if (IpSceneMng._chipNo.second)
	{
		_objList.clear();
		_Draw.clear();
		_Init.clear();
		IpSceneMng._chipNo.first = CHIP_TYPE::test;

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
	
	//_Draw[IpSceneMng._chipNo.first]();
	_Draw[CHIP_TYPE::�X1]();
	



	// �`�������
	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
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
	_Init.try_emplace(CHIP_TYPE::�X1, [&]() {
		
		IpSceneMng.mapSize = { 2400,2400 };
		
		// �`���ǂݍ���
		IpSceneMng._dataBase.resize((__int64)75*75);
		for (size_t no = 0; no < 75; no++)
		{
			IpSceneMng._data.emplace_back(&IpSceneMng._dataBase[no * 75]);
		}


		IpImageMng.GetID("1", "image/1.png", { 2400,2400 }, { 1,1 });


		// csv�t�@�C����ǂݍ���
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



			//_objList.emplace_back(new Player({ 0,0}, { 32,32 }, { 1.0f,1.0f }));

		

		FloorState Flrdata;
		RemoveState RemovaData;

		for (int x = 0; x < 75 * 75; x++)
		{
			if (IpSceneMng._dataBase[x] == 0)
			{
				Flrdata = { FLOOR_TYPE::�����蔻��,{32 * (x % 75),32 * (x / 75)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
			}
			if (IpSceneMng._dataBase[x] == 1)
			{
				RemovaData = { Remove_ID::test1,{32 * (x % 75),32 * (x / 75)},{32.0,32.00} };
				_objList.emplace_back(new Remove(RemovaData));
			}
			if (IpSceneMng._dataBase[x] == 10)
			{
				_objList.emplace_back(new Player({ 32 * (x % 75),32 * (x / 75) }, { 32,32 }, { 1.0f,1.0f }));

			}

		}



		////�G�����|�����_��
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
		//		EnemyAdd(ENEMY_TYPE::�R�E����, _objList, { 400 + x * 30.0,300 + y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });
		//	}
		//}
		return true;


	});



	_Draw.try_emplace(CHIP_TYPE::�X1, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("1")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });

	
	});

	_Draw.try_emplace(CHIP_TYPE::test, []() {
		IpSceneMng.AddDrawQue({ IMAGE_ID("���1")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });


	});

}




