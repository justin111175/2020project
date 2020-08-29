#include "GameOverScene.h"
#include "../common/Input/PadInput.h"
#include "TitleScene.h"
#include <Dxlib.h>
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/Input/KeyInput.h"





GameOverScene::GameOverScene(unique_Base own)
{
	childScene_ = std::move(own);

	controller.emplace(conType::Key, std::make_unique<KeyInput>());
	controller[conType::Key]->SetUp();

	cnt_ = 0;
}



GameOverScene::~GameOverScene()
{
}

unique_Base GameOverScene::Update(unique_Base own)
{

	if (cnt_ < 200)
	{
		cnt_+=5;
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
				case InputID::Z:
					IpSceneMng.mapPos = { 0,0 };

					return std::make_unique<TitleScene>();

					break;
				}
			}

		}
	}


	BaseDraw();
	return std::move(own);
}

void GameOverScene::BaseDraw(void)
{

	childScene_->BaseDraw();


	SetDrawBlendMode(DX_BLENDMODE_ALPHA,cnt_);

	DrawBox(0, 0, IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, 0x000000, true);

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	if (cnt_ >= 200)
	{
		//if (state_->winFlag_)
		//{
		//	SetFontSize(50);
		//	DrawString(515, 300, "GAME CLEAR", 0xFFFFFF, 0x000000);

		//}
		//else
		//{			

		SetFontSize(50);
		DrawString(280, 250, "GAME OVER", 0xFFFFFF, 0x000000);




		//SetDrawBlendMode(DX_BLENDMODE_ALPHA, sin((double)IpSceneMng.frames() / 10) * 250);
		//DrawGraph(350, 500, IMAGE_ID("space")[0], true);

		//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

	}
	
	ScreenFlip();

}


