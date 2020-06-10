#include "GameOverScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "TitleScene.h"
#include "algorithm"

GameOverScene::GameOverScene()
{
	IpImageMng.GetID("�Q�[���I�[�o�[", "image/gmaeover.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("�Q�[���I�[�o�[Sel", "image/gameoverSel.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });
	IpImageMng.GetID("BG", "image/bg.png", { 1280,720 }, { 1,1 });
	//IpImageMng.GetID("�X�R�A", "image/score.png", { 300,380 }, { 1,1 });
	//SoundInit();
	//Number number;
	//number.Init();


	cnt = -100;
	//_OverId = �f�[�^�ǂݍ���;
}

GameOverScene::~GameOverScene()
{
}

unique_Base GameOverScene::Update(unique_Base own)
{

	if (cnt < 0)
	{
		if (IpSceneMng.frames() % 60)
		{
			cnt++;
		}
	}

	IpSceneMng.AddDrawQue({ IMAGE_ID("BG")[0], 0,0,0,0,1.0f,1.0f,0,1,LAYER::BG });

	IpSceneMng.AddDrawQue({ IMAGE_ID("�Q�[���I�[�o�[")[0], 0,cnt,0,0,1.0f,1.0f,0,1,LAYER::UI });
	if (cnt >= 0)
	{
		IpSceneMng.AddDrawQue({ IMAGE_ID("�Q�[���I�[�o�[Sel")[0], 0,0,0,0,1.0f,1.0f,0,1,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], 480,415+ (_select.s_id.GameOver)*110,0,0,1.0f,1.0f,0,1,LAYER::UI });

	}
	
	_select.Updata(IpSceneMng._input, INPUT_ID::UP, SceneSel::GameOver, 1, -1);
	_select.Updata(IpSceneMng._input, INPUT_ID::DOWN, SceneSel::GameOver, 1, 1);


	FILE* fp = NULL;	

	if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
	{
		switch (_select.s_id.GameOver)
		{
		case 0:
			if (fopen_s(&fp, "Dat/player.dat", "rb") == 0)
			{
				return std::make_unique<GameScene>();
			}
			break;
		case 1:
			DxLib_End();
			break;
		default:
			break;
		}
	}
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

	// �`�������
	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());


	return std::move(own);
}

void GameOverScene::SoundInit(void)
{
	IpImageMng.GetSound("�{�^����", "image/sound/bottom.mp3");

}
