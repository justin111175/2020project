#include "TitleScene.h"
#include "algorithm"
#include "SceneMng.h"
#include <ImageMng.h>
#include <GameScene.h>
#include <Dxlib.h>

TitleScene::TitleScene()
{
	IpImageMng.GetID("�^�C�g��", "image/title.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("�I��", "image/textplate.png", { 486,150 }, { 1,1 });
	meanID = �V�����Q�[��;
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	






	//return std::make_unique<LoadingScene>();
	
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







	IpSceneMng.AddDrawQue({ IMAGE_ID("�^�C�g��")[0],0,0,0,0,1.0f,1.0f,0,0,LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("�I��")[0],400,370+76*meanID,0,0,1.0f,1.0f,0,0,LAYER::UI });


	if ((*_Input).state(INPUT_ID::UP).first && !(*_Input).state(INPUT_ID::UP).second)
	{
		if (meanID > �V�����Q�[��)
		{
			meanID = (MEAN_ID)(meanID - 1);
		}
		else
		{
			meanID = �Q�[���I��;
		}
	}
	if ((*_Input).state(INPUT_ID::DOWN).first && !(*_Input).state(INPUT_ID::DOWN).second)
	{
		if (meanID < �Q�[���I��)
		{
			meanID = (MEAN_ID)(meanID + 1);
		}
		else
		{
			meanID = �V�����Q�[��;
		}
	}


	switch (meanID)
	{
	case �V�����Q�[��:

		if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
		{
			return std::make_unique<GameScene>();

		}
		break;
	case �f�[�^�ǂݍ���:
		break;
	case �Q�[���I��:
		if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
		{
			DxLib_End();

		}

		break;
	default:
		break;
	}

	//DrawString(640, 360, "Hello C World!", GetColor(255, 255, 255));


	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());

	return std::move(own);

}

void TitleScene::funcInit(void)
{
}

void TitleScene::RunActQue(std::vector<ActQueT> actList)
{
}
