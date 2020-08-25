#include "TitleScene.h"
#include "algorithm"
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include <Dxlib.h>

#include "GameScene.h"
#include "../common/Input/KeyInput.h"

TitleScene::TitleScene()
{

	Init();

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

	MeanCtl();

	Draw();



	if (sceneFlag_)
	{
		return std::make_unique<GameScene>();

	}


	_objList.erase(std::remove_if(
		_objList.begin(),									// �`�F�b�N�͈͂̊J�n
		_objList.end(),										// �`�F�b�N�͈͂̏I��
		[](sharedObj& obj) {return (*obj).isDead(); }),		// �����_��()
		_objList.end());

	return std::move(own);

}

void TitleScene::Draw(void)
{

	IpSceneMng.AddDrawQue({ IMAGE_ID("�^�C�g��")[0], {0,0 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("�^�C�g��1")[0], {125,150 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {250,250 }, { 0,0 }, { 1.0f,1.0f }, false, true, 0, LAYER::BG });
	
	IpSceneMng.AddDrawQue({ IMAGE_ID("�I��")[0], {240,300+ static_cast<int>(titleMean_)*50 }, { 0,0 }, { 1.0f,1.0f }, false, 0, 0, LAYER::BG });


	IpSceneMng.AddDrawQue({ "�V�����Q�[��",{310,300}, {1.0f,1.0f },30,0,LAYER::UI });
	//IpSceneMng.AddDrawQue({ "�ۑ�",{}, {1.0f,1.0f },20,0,LAYER::UI });
	IpSceneMng.AddDrawQue({ "�Q�[���I��",{310,350},{ 1.0f,1.0f },30,0,LAYER::UI });
}

void TitleScene::Init(void)
{
	IpImageMng.GetID("�^�C�g��", "image/title.jpg", { 800,600 }, { 1,1 });
	IpImageMng.GetID("�^�C�g��1", "image/title1.png", { 563,66 }, { 1,1 });
	IpImageMng.GetID("test", "image/test.png", { 300,300 }, { 1,1 });
	IpImageMng.GetID("�I��", "image/selsct.png", { 56,40 }, { 1,1 });

	controller.emplace(conType::Key, std::make_unique<KeyInput>());
	controller[conType::Key]->SetUp();

	sceneFlag_ = false;
	titleMean_ = TitleMean::�V�����Q�[��;
}

void TitleScene::MeanCtl(void)
{

	(*controller[conType::Key])();

	for (auto data : controller[conType::Key]->GetCntData())
	{
		if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
		{
			switch (data.first)
			{
			case InputID::Down:
				if (titleMean_ < TitleMean::�Q�[���I��)
				{
					titleMean_ = (TitleMean)(static_cast<int>(titleMean_) + 1);

				}
				else
				{
					titleMean_ = TitleMean::�V�����Q�[��;
				}
				break;
			case InputID::Up:
				if (titleMean_ > TitleMean::�V�����Q�[��)
				{
					titleMean_ = (TitleMean)(static_cast<int>(titleMean_) - 1);

				}
				else
				{
					titleMean_ = TitleMean::�Q�[���I��;
				}
				break;
			case InputID::Z:
				switch (titleMean_)
				{
				case TitleMean::�V�����Q�[��:
					sceneFlag_ = true;

					break;
				case TitleMean::�Q�[���I��:
					DxLib_End();
					break;
				default:
					break;
				}
				break;
			}
		}

	}

}


