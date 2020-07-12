#include "GameScene.h"
#include <Dxlib.h>
#include "..\common\ImageMng.h"
#include "SceneMng.h"
#include "..\Player.h"
#include "..\Floor.h"



GameScene::GameScene()
{
	IpImageMng.GetID("1", "image/1.png", { 2400,2400 }, { 1,1 });
	IpImageMng.GetID("�v���C���[����", "image/Player/walk.png", { 32,32 }, { 3,4 });
	IpImageMng.GetID("block", "image/block.png", { 32,32 }, { 10,2 });



	MapInit();

	_objList.emplace_back(new Player({0,0 }, { 32,32 }, { 1.0f,1.0f }));
	




	_Init[CHIP_TYPE::�X1]();

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
	

	

	// �`�������
	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());
	
	return std::move(own);
}

void GameScene::MapInit(void)
{
	_Init.try_emplace(CHIP_TYPE::�X1, [&]() {
		
		IpSceneMng.mapSize = { 2400,2400 };
		// �`���ǂݍ���
		for (int x = 0; x < 75 * 75; x++)
		{
			IpSceneMng._mapNow.try_emplace(x, NULL);
		}

		//IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 10,2 });


		// csv�t�@�C����ǂݍ���
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
				Flrdata = { FLOOR_TYPE::�����蔻��,{32.0 * (x % 75),32.0 * (x / 75)},{32.0,32.00} };
				_objList.emplace_back(new Floor(Flrdata));
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


}




