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

GameScene::GameScene()
{	
	funcInit();
	

		
	// �`��𑝉�
	IpImageMng.GetID("�v���C���[����", "image/Player/walk.png", { 48,49 }, { 3,4 });
	IpImageMng.GetID("�v���C���[����", "image/Player/dead.png", { 50,55 }, { 3,1 });
	
	IpImageMng.GetID("�����X�^�[����", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("�e", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("�a��", "image/slash.png", { 39,37 }, { 1,1 });
	IpImageMng.GetID("�a��1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("weapons", "image/weapons.png", { 98,65 }, { 3,4 });




	IpSceneMng.AddDrawQue({ IMAGE_ID("�����X�^�[����")[0], 400 ,300,0,0,0,0,LAYER::BG });

	
	_objList.emplace_back(new Player({ 0,0 }, { 48,49 }));

	EnemyState data = { ENEMY_TYPE::�R�E����,{400.0,300.0}, { 48,48 } };
	_objList.emplace_back(new Enemy(data));

	EnemyState data1 = { ENEMY_TYPE::�I�[�N,{500.0,300.0}, { 48,48 } };
	_objList.emplace_back(new Enemy(data1));

	IpImageMng.GetID("�E�F�|��", "image/weapons.png", { 98,68 }, { 3,5 });


	_shakeCount = 0;
}


GameScene::~GameScene()
{

}

unique_Base GameScene::Update(unique_Base own)
{
	// �`��
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
		

	//IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0], 4096/2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });

	//switch (IpSceneMng._classCnt)
	//{
	//case 1:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i")[0], 4096*1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG});
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�G���h����_��")[0], 5960 - _mapPos.x,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;

	//case 2:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i2")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i2")[0], 4096 * 1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�G���h����_��")[0], 5960 - _mapPos.x,800 / 2-250,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;
	//case 3:
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i3")[0], 4096 / 2 - _mapPos.x ,800 / 2,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("�w�i3")[0], 4096 * 1.5 - _mapPos.x,800 / 2,0,0,0,LAYER::BG});
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("feed")[0], 6000 - _mapPos.x,800 / 2-100,0,0,0,LAYER::BG });
	//	IpSceneMng.AddDrawQue({ IMAGE_ID("UI")[0], 800 / 2 ,72 / 2,0,0,0,LAYER::UI });
	//	break;	
	//default:
	//	// ���Ȃ��͂�
	//	AST();
	//	break;
	//}



	// �`�������
	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());


	
	return std::move(own);
}

// �t�@���N�����L���[
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

// �N���X1
void GameScene::MapInit_1(void)
{
	// �`���ǂݍ���
	//IpImageMng.GetID("UI", "image/UI.png", { 800,72 }, { 1,1 });
	//IpImageMng.GetID("�v���C���[1", "image/player1.png", { 40,40 }, { 3,4 });
	//
	//IpImageMng.GetID("�w�i", "image/BG.png", { 4096,800 }, { 1,1 });
	//IpImageMng.GetID("�u���b�N", "image/block.png", { 30,30 }, { 9,2 });
	//
	//IpImageMng.GetID("�X���C��", "image/enemy/slime.png", { 55,30 }, { 3,1 });
	//IpImageMng.GetID("�R�C��", "image/coin.png", { 25,24 }, { 4,1 });
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
	//IpImageMng.GetID("�G���h����_��", "image/end_tree.png", { 453,600 }, { 1,1 });
	//_mapPos = { 0,0 };
	//
	// csv�t�@�C����ǂݍ���
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
	//			Flrdata = { FLOOR_TYPE::��1_����,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 5:
	//			Flrdata = { FLOOR_TYPE::��2_����,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,20} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 6:
	//			Flrdata = { FLOOR_TYPE::�K�i_��,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 15},{30,30} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;
	//		case 13:
	//			Flrdata = { FLOOR_TYPE::�����K,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y + 25},{30,25} };
	//			_objList.emplace_back(new Floor(Flrdata));
	//			break;

	//		default:
	//			break;
	//		}

	//		if (IpSceneMng.mapNow[y][x] == 26)
	//		{
	//			MoveState tmpMoveState;
	//			tmpMoveState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 0,0 });
	//			EnemyState data = { ENEMY_TYPE::�X���C��,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y}, { 43,20 },tmpMoveState };
	//			_objList.emplace_back(new Enemy(data));
	//		}
	//		if (IpSceneMng.mapNow[y][x] == 22)
	//		{
	//			MoveState tmpMoveState;
	//			IteamState data = { ITEAM_TYPE::�R�C��,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y}, { 25,24 } ,tmpMoveState };
	//			_objList.emplace_back(new iteam(data));

	//		}
	//		if (IpSceneMng.mapNow[y][x] == 25)
	//		{
	//			MoveState tmpMoveState;
	//			IteamState data = { ITEAM_TYPE::�G���h,{_mapSize.x / 2 - _mapPos.x + _mapSize.x * x,_mapSize.y / 2 - _mapPos.y + _mapSize.y * y+30}, { 116,150 } ,tmpMoveState };
	//			_objList.emplace_back(new iteam(data));

	//		}
	//	}
	//}
}



//void GameScene::SoundInit(void)
//{
//	// ���̓ǂݍ���
//	IpImageMng.GetSound("�R�C����", "image/sound/coin.mp3");
//	IpImageMng.GetSound("�W�����v��", "image/sound/jump.wav");
//	IpImageMng.GetSound("�G�����艹", "image/sound/hitenemy.wav");
//	IpImageMng.GetSound("������", "image/sound/number.mp3");
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

}