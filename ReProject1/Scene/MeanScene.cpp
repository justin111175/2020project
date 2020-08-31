#include "MeanScene.h"
#include "GameScene.h"
#include <Dxlib.h>
#include "TitleScene.h"
#include "../common/Input/PadInput.h"
#include "../common/Input/KeyInput.h"
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include <Dxlib.h>
#include "MingameScene.h"

MeanScene::MeanScene(unique_Base own)
{
    childScene_ = std::move(own);


	controller.emplace(conType::Key, std::make_unique<KeyInput>());
	controller[conType::Key]->SetUp();
	
	number.Init();

	diffIndex_ = DiffIndex::�T���ł��ł���;
	cnt_ = 0;

}

MeanScene::~MeanScene()
{
}

unique_Base MeanScene::Update(unique_Base own)
{
	if (CheckHitKey(KEY_INPUT_F2))
	{
		return childScene_->Update(std::move(childScene_));
	}

	//childScene_

	if (cnt_ < 200)
	{
		cnt_ += 5;
	}
	else
	{

		(*controller[conType::Key])();

		for (auto data : controller[conType::Key]->GetCntData())
		{
			if (data.second[static_cast<int>(Trg::Now)] && !data.second[static_cast<int>(Trg::Old)])
			{
				switch (data.first)
				{
				case InputID::Up:

					if (diffIndex_ > DiffIndex::�T���ł��ł���)
					{
						diffIndex_ = (DiffIndex)(static_cast<int>(diffIndex_) - 1);

					}
					else
					{
						diffIndex_ = DiffIndex::���������ČN�͐_�l;
					}
					break;
				case InputID::Down:
					if (diffIndex_ < DiffIndex::���������ČN�͐_�l)
					{
						diffIndex_ = (DiffIndex)(static_cast<int>(diffIndex_) + 1);

					}
					else
					{
						diffIndex_ = DiffIndex::�T���ł��ł���;
					}
					break;
				case InputID::Z:

					//childScene_->Update(std::move(childScene_));
					return std::make_unique<MingameScene>(std::move(childScene_), static_cast<int>(diffIndex_));

					break;
				}
			}

		}
	}

	BaseDraw();

	return std::move(own);
}



void MeanScene::BaseDraw(void)
{	

	
	childScene_->BaseDraw();


	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt_);

	//DrawBox(0, 0, IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, 0x000000, true);

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);



	//if (cnt_ >= 200)
	{
	

		DrawBox(250, 100, 550, 300, 0x000000, true);
		DrawBoxAA(250, 100, 550, 300, 0xFFFFFF, false,3.0f);


		DrawString(280, 125, "�T���ł��ł���", 0xFFFFFF);
		DrawString(280, 175, "�����������", 0xFFFFFF);
		DrawString(280, 225, "���������āA�N�͐_�l�H", 0xFFFFFF);
		DrawGraph(260, 125+ static_cast<int>(diffIndex_)*50, IMAGE_ID("�Z���N�g")[0], true);

	}
	ScreenFlip();
}


