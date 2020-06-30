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
	

		
	// �`��𑝉�
	IpImageMng.GetID("�v���C���[����", "image/Player/walk.png", { 48,49 }, { 3,4 });
	IpImageMng.GetID("�v���C���[����", "image/Player/dead.png", { 50,55 }, { 3,1 });
	
	IpImageMng.GetID("�����X�^�[����", "image/Monsters/walk.png", { 48,48 }, { 3,32 });

	IpImageMng.GetID("�e", "image/shot.png", { 43,11 }, { 1,1 });
	IpImageMng.GetID("�a��", "image/slash.png", { 39,37 }, { 1,1 });
	
	IpImageMng.GetID("�a��1", "image/slash1.png", { 37,38 }, { 1,1 });
	IpImageMng.GetID("�a��2", "image/slash2.png", { 37,49 }, { 1,1 });

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
	IpImageMng.GetID("�GHP", "image/EnemyHp.png", { 60,18 }, { 1,1 });
	IpImageMng.GetID("�GHP_BAR", "image/EnemyHpBar.png", { 60,18 }, { 1,1 });

	
	
	IpImageMng.GetID("blast", "image/blast.png", { 40,40 }, { 6,4 });
	
	IpImageMng.GetID("UP1", "image/levelUp1.png", { 250,150 }, { 1,8 });

	IpImageMng.GetID("����", "image/letter.png", { 1280,720 }, { 1,1 });
	
	IpImageMng.GetID("UI�w�i", "image/UI_back.png", { 480,480 }, { 1,1 });


	
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
	for (int x = 0; x < 50*60; x++)
	{
		IpSceneMng._mapNow.try_emplace(x, NULL);
	}

	IpImageMng.GetID("block", "image/chip/block.png", { 32,32 }, { 1,1});
	IpImageMng.GetID("1_1", "image/chip/1_1.png", { 1600,1920 }, { 1,1});

	// csv�t�@�C����ǂݍ���
	int type = NULL;
	int y = 0;
	int x = 0;
	
	FILE* fp = NULL;
	fopen_s(&fp, "csv/1_1_1.csv", "rb");
	while (fscanf_s(fp, "%d", &type) != EOF)
	{
		IpSceneMng._mapNow[x]=type;
		x++;
	}
	
	
	FloorState Flrdata;


	MoveState tmpMoveState;


	for (int x = 0; x < 50*60; x++)
	{


		if (IpSceneMng._mapNow[x] == 0)
		{
			Flrdata = { FLOOR_TYPE::�����蔻��,{32.0*(x%50),32.0*(x/50)},{32.0,32.00}};
			_objList.emplace_back(new Floor(Flrdata));
		}

	}
		
	



	//�G�����|�����_��
	auto EnemyAdd = [](ENEMY_TYPE E_type, std::vector<sharedObj>& _objList, Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate) {
		MoveState tmpMoveState;
		tmpMoveState.emplace_back(DIR_ID::RIGHT, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(DIR_ID::DOWN, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(DIR_ID::LEFT, Vector2Dbl{ 0,0 });
		tmpMoveState.emplace_back(DIR_ID::UP, Vector2Dbl{ 0,0 });

		EnemyState data = { E_type,{pos.x,pos.y}, { size.x,size.y },{exrate.x,exrate.y},tmpMoveState };
		_objList.emplace_back(new Enemy(data));
	};

	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5; y++)
		{
			EnemyAdd(ENEMY_TYPE::�R�E����, _objList, { 400+ x * 30.0,300+ y * 30.0 }, { 48.0,48.0 }, { 1.0f,1.0f });

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
	funcQue[ACT_QUE::LEVELUP] = FuncLevelUp();
	funcQue[ACT_QUE::CHECK] = FuncCheck();

}