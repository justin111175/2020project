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
	

		
	// �`��𑝉�
	IpImageMng.GetID("�v���C���[����", "image/Player/walk.png", { 48,49 }, { 3,4 });
	IpImageMng.GetID("�v���C���[����", "image/Player/dead.png", { 50,55 }, { 3,1 });
	
	IpImageMng.GetID("�����X�^�[����", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("�e", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("�a��", "image/slash.png", { 39,37 }, { 1,1 });
	IpImageMng.GetID("�a��1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("�a��2", "image/slash2.png", { 37,49 }, { 1,1 });
	IpImageMng.GetID("�a��3", "image/Sword.png", { 380,384 }, { 2,7 });

	IpImageMng.GetID("weapons", "image/weapons.png", { 98,65 }, { 3,4 });
	


	IpImageMng.GetID("���j���[", "image/mean.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("���b�Z�[�W", "image/messagecursor.png", { 50,78 }, { 1,1 });
	IpImageMng.GetID("�X�e�[�^�X", "image/status.png", { 1280,720 }, { 1,1 });
	
	
	IpImageMng.GetID("����", "image/Equipment.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("����", "image/1.png", { 186,50 }, { 1,1 });
	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });
	
	IpImageMng.GetID("Bar", "image/bar.png", { 510,66 }, { 1,1 });

	IpImageMng.GetID("HP", "image/gaugeB.png", { 325,22 }, { 1,1 });
	IpImageMng.GetID("MP", "image/gaugeB (1).png", { 325,22 }, { 1,1 });
	
	
	
	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });
	
	IpImageMng.GetID("����", "image/letter.png", { 1280,720 }, { 1,1 });





	
	_objList.emplace_back(new Player({ 0,0 }, { 48,49 }, {1.0f,1.0f}));

	auto EnemyAdd = []( ENEMY_TYPE E_type, std::vector<sharedObj>& _objList,Vector2Dbl pos, Vector2Dbl size,Vector2Dbl exrate) {
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
			EnemyAdd(ENEMY_TYPE::�R�E����, _objList, { 400.0 + x * 30,300.0 + y * 30 }, { 48.0,48.0 }, {1.0f,1.0f});

		}
	}

	MapInit_1();
	
	


	_input = std::make_shared<KeyState>();


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
	



	(*_input).Update();



	//for (auto i : Outside_A1_ID())
	//{

	//	for (int x = 0; x < TESTMAX; x++)
	//	{

	//		if (IpSceneMng.mapNow[x] == static_cast<int>(i))
	//		{
	//			DrawRectGraph(
	//				chipSize.x*x,
	//				chipSize.y*y,
	//				chipSize.x *(pzData[y][x] % divTable[divID]),
	//				chipSize.y *(pzData[y][x] / divTable[divID]),
	//				chipSize.x,
	//				chipSize.y,
	//				puzzleImg[pzlImageID[PZL_SEL_NOW]],
	//				false,
	//				false);
	//		}

	//	}

	//}

	//IpSceneMng.AddDrawQue({ IMAGE_ID("Outside_A5")[76], 100.0,100.0,0,0,1.0f,1.0f,0,1,LAYER::UI });
		

	//switch (IpSceneMng._classCnt)
	//{0
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
	
	//IpImageMng.GetID("Outside_A2", "image/chip/Outside_A2.png", { 768,576 }, { 16,12 });

	IpImageMng.GetID("Outside_A1", "image/chip/Outside_A1.png", { 48,48 }, { 8,16 });

	// csv�t�@�C����ǂݍ���
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
	//for (auto i : Outside_A1_ID())
	//{

	//	for (int x = 0; x < 50; x++)
	//	{
	//		for (int y = 0; y < 50; y++)
	//		{

	//			if (IpSceneMng.mapNow[y][x] == static_cast<int>(i))
	//			{
	//				Flrdata = { FLOOR_TYPE::Outside_A1_ID,{48.0*x,48.0*y},{48.0,48.0} ,i };
	//				_objList.emplace_back(new Floor(Flrdata));
	//			}
	//		}
	//	}
	//	
	//}
	//for (int x = 0; x < 50; x++)
	//{
	//	for (int y = 0; y < 50; y++)
	//	{

	//			Flrdata = { FLOOR_TYPE::Outside_A1_ID,{48.0*x,48.0*y},{48.0,48.0} ,Outside_A1_ID::A10 };
	//			_objList.emplace_back(new Floor(Flrdata));
	//		
	//	}
	//}

	for (int x = 0; x < 100; x++)
	{
		for (int y = 0; y < 100; y++)
		{


				Flrdata = { FLOOR_TYPE::Outside_A1_ID,{48.0*x,48.0*y},{48.0,48.0} ,Outside_A1_ID::A10 };
				_objList.emplace_back(new Floor(Flrdata));
			
		}
	}
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
	funcQue[ACT_QUE::CHECK] = FuncCheck();

}