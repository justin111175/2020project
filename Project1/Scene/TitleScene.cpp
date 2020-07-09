#include "TitleScene.h"
#include "algorithm"
#include "SceneMng.h"
#include <ImageMng.h>
#include <Dxlib.h>
#include <Select.h>
#include "..\LoadScene.h"

#include "GameScene.h"
TitleScene::TitleScene()
{
	IpImageMng.GetID("�^�C�g��", "image/title.png", { 1280,800 }, { 1,1 });
	IpImageMng.GetID("�I��", "image/textplate.png", { 486,150 }, { 1,1 });
	
	FILE* fp = NULL;

	if (fopen_s(&fp, "player.dat", "rb") == 0)
	{
		_select.s_id.Title = 1;
		fclose(fp);

	}
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
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

	//�^�C�g���`��
	IpSceneMng.AddDrawQue({ IMAGE_ID("�^�C�g��")[0],{0,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("�I��")[0],{400.0,420 + 85.0 * _select.s_id.Title} ,{0,0},{1.0f,1.0f},false,0,0,LAYER::UI });

	//�I��
	_select.Updata(IpSceneMng._input, INPUT_ID::UP, SceneSel::TITLE, 2,-1);
	_select.Updata(IpSceneMng._input, INPUT_ID::DOWN, SceneSel::TITLE, 2,1);


	
	
	if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
	{
		switch (_select.s_id.Title)
		{
		case 0:		//�V�����Q�[��	

			return std::make_unique<LoadScene>();
			break;
			
		case 1:		//�f�[�^�ǂݍ���
			IpSceneMng._chipType.first = CHIP_TYPE::�X1;
			return std::make_unique<LoadScene>();
			break;
		case 2:		//�Q�[���I��
			DxLib_End();
			break;
		default:
			break;
		}
	}

	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());

	return std::move(own);

}


