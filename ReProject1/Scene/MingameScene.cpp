#include "MingameScene.h"
#include "../common/Input/KeyInput.h"
#include <Dxlib.h>
#include "../common/ImageMng.h"
#include "SceneMng.h"
#include "GameScene.h"

MingameScene::MingameScene(unique_Base own,int no)
{

	childScene_ = std::move(own);

	controller.emplace(conType::Key, std::make_unique<KeyInput>());
	controller[conType::Key]->SetUp();
	classCnt_ = no;

	DivBase_.resize((__int64)divTable[classCnt_] * divTable[classCnt_]);

	for (size_t no = 0; no < divTable[classCnt_]; no++)
	{
		Div_.emplace_back(&DivBase_[no * divTable[classCnt_]]);
	}


	for (int y = 0; y < divTable[classCnt_]; y++)
	{
		for (int x = 0; x < divTable[classCnt_]; x++)
		{
			Div_[y][x] = x + divTable[classCnt_] * y;

		}
	}
	blackID_ = rand()% divTable[classCnt_]* divTable[classCnt_];

	IpImageMng.GetID("ミニゲーム", "image/Dragon.png", { 420,420 }, { 1,1 });


	
	Size_ = 420 / divTable[classCnt_];



	for (int y = 0; y < divTable[classCnt_]; y++)
	{
		for (int x = 0; x < divTable[classCnt_]; x++)
		{
			if (blackID_ == Div_[y][x])
			{
				Panel_ = { x,y };

			}

		}
	}

	for (int j = 0; j < 3; j++)
	{
		InputID id = static_cast<InputID>(rand() % 4);
		PanelCtl(id);

	}
}

MingameScene::~MingameScene()
{
}

unique_Base MingameScene::Update(unique_Base own)
{

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

				PanelCtl(data.first);
				if (data.first == InputID::Esc)
				{
					return childScene_->Update(std::move(childScene_));
				}
			}

		}



		if (isClear())
		{
			IpSceneMng._chipNo.first = CHIP_TYPE::地図5;
			IpSceneMng._dataBase.clear();
			IpSceneMng._data.clear();

			return std::make_unique<GameScene>();

		}
	}
	BaseDraw();

	return std::move(own);
}

void MingameScene::BaseDraw(void)
{
	childScene_->BaseDraw();


	SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt_);

	DrawBox(0, 0, IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, 0x000000, true);

	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);

	DrawBox(500, 100, 700, 500, 0xffffff, true);

	for (int y = 0; y < divTable[classCnt_]; y++)
	{
		for (int x = 0; x < divTable[classCnt_]; x++)
		{
			if (blackID_ != Div_[y][x]/* && moveID != pzData[y][x]*/)
			{
				DrawRectGraph(
					100+ Size_ * x,
					100+ Size_* y,
					Size_ * (Div_[y][x] % divTable[classCnt_]),
					Size_ * (Div_[y][x] / divTable[classCnt_]),
					Size_,
					Size_,
					IMAGE_ID("ミニゲーム")[0],
					false,
					false
				);
				DrawFormatString(100 + Size_ * x, 100 + Size_ * y, 0x00FF00, "%d", Div_[y][x]);
				DrawFormatString(100 + Size_ * x, 100 + Size_ * y+50, 0x00FF00, "%d,%d", x,y);
			}

			DrawBox(100 + Size_ * x, 100 + Size_ * y, 100 + Size_ * (x + 1), 100 + Size_ * (y + 1), GetColor(255, 0, 0), false);
			//DrawFormatString(50, 50, 0x00FF00, "%d,%d", NextPanel_.x, NextPanel_.y);
		
		}
	}

	//DrawString(200, 200, "ミニゲーム", 0xFFFFFF);
	ScreenFlip();

}

bool MingameScene::isClear(void)
{
	for (int y = 0; y < divTable[classCnt_]; y++)
	{
		for (int x = 0; x < divTable[classCnt_]; x++)
		{
			if (Div_[y][x] != y * divTable[classCnt_] + x)
			{
				return false;
			}
		}
	}
	return true;
}

void MingameScene::SwapNum(int* num1, int* num2)
{
	int tmpNum = *num1;
	*num1 = *num2;
	*num2 = tmpNum;
}

void MingameScene::PanelCtl(InputID id)
{
	NextPanel_ = Panel_;

		switch (id)
		{
		case InputID::Up:

			if (NextPanel_.y < divTable[classCnt_]-1)
			{
				NextPanel_.y++;
				SwapNum(&Div_[NextPanel_.y][NextPanel_.x], &Div_[Panel_.y][Panel_.x]);
				Panel_ = NextPanel_;
			}
			break;

		case InputID::Down:
			if (NextPanel_.y > 0)
			{
				NextPanel_.y--;
				SwapNum(&Div_[NextPanel_.y][NextPanel_.x], &Div_[Panel_.y][Panel_.x]);
				Panel_ = NextPanel_;
			}


			break;
		case InputID::Left:


			if (NextPanel_.x < divTable[classCnt_]-1)
			{
				NextPanel_.x++;
				SwapNum(&Div_[NextPanel_.y][NextPanel_.x], &Div_[Panel_.y][Panel_.x]);
				Panel_ = NextPanel_;
			}
			break;
		case InputID::Right:


			if (NextPanel_.x > 0)
			{
				NextPanel_.x--;
				SwapNum(&Div_[NextPanel_.y][NextPanel_.x], &Div_[Panel_.y][Panel_.x]);
				Panel_ = NextPanel_;

			}
			break;


		default:
			//SetDir(data.first);

			break;
		}
	




}
