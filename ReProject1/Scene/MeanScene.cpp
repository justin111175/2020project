#include "MeanScene.h"
#include "GameScene.h"
#include <Dxlib.h>
#include "TitleScene.h"
#include "../common/Input/PadInput.h"
#include "../common/Input/KeyInput.h"
#include "SceneMng.h"
#include "../common/ImageMng.h"
#include <Dxlib.h>
MeanScene::MeanScene(unique_Base own)
{
    childScene_ = std::move(own);


	controller.emplace(conType::Key, std::make_unique<KeyInput>());
	controller[conType::Key]->SetUp();
	
	number.Init();
	meanID_ = MeanID::ステータス;
	meanState_ = MeanState::外;
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
				case InputID::Z:

					meanState_ = MeanState::中;

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

	//SetDrawScreen(_screenID);
	//ClsDrawScreen();

	childScene_->BaseDraw();
	//SetDrawScreen(DX_SCREEN_BACK);


	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, cnt_);

	//DrawBox(0, 0, IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, 0x000000, true);

	//SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
	//DrawGraph(0, 0, _screenID, true);



	if (cnt_ >= 200)
	{
	

		auto size = { 0.5f,0.5f };

		auto Pos = [&](MeanID id) {

			return Vector2(50, 120 + mean_size_Y * static_cast<int>(id));
		};

		IpSceneMng.AddDrawQue({ "ステータス",Pos(MeanID::ステータス), {1.0f,1.0f },20,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "保存",Pos(MeanID::保存), {1.0f,1.0f },20,0,LAYER::UI });
		IpSceneMng.AddDrawQue({ "終了",Pos(MeanID::終了),{ 1.0f,1.0f },20,0,LAYER::UI });




		IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {20,100}, { 0,0 }, {0.5f,0.5f }, false, 0, 0, LAYER::UI });

		//DrawRotaGraph3(20, 100, 0, 0, 0.5f, 0.5f, 0, IMAGE_ID("test")[0], false, false);

		if (meanState_ == MeanState::外)
		{


			IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {30,120 + 40 * static_cast<int>(meanID_)}, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });
			//DrawGraph(30, 120 + 40 * static_cast<int>(meanID_), IMAGE_ID("セレクト")[0], true);
		}

		if (meanState_ == MeanState::中)
		{
			auto Pos = [&](Vector2 pos) {

				return Vector2(200 + pos.x, 140 + 30 * pos.y);
			};

			auto color = [&](Vector2 pos, Status_ID id) {
				int tmp = 0;
				//_status[id] == _statusOld[id] ? tmp = 0 : tmp = 1;

				//number.Draw(pos, { 0.2f,0.2f }, _status[id], tmp);

			};

			switch (meanID_)
			{
			case MeanID::ステータス:

				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {170,100}, { 0,0 }, {1.0f,1.4f}, false, 0, 0, LAYER::UI });
				IpSceneMng.AddDrawQue({ IMAGE_ID("test")[0], {470,100}, { 0,0 }, {1.0f,0.8f}, false, 0, 0, LAYER::UI });



				IpSceneMng.AddDrawQue({ "レベル　 　   -> ",{200,155},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "経験値　 　   -> ",{200,185},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "必要量",{200,215},{1.0f,1.0f},20,0,LAYER::UI });



				IpSceneMng.AddDrawQue({ "体力",{220,265},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "持久力",{220,295},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "筋力",{220,325},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "敏捷",{220,355},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "回復",{220,385},{1.0f,1.0f },20,0,LAYER::UI });

				IpSceneMng.AddDrawQue({ "HP           ->",{490,155},{1.0f,1.0f},20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "スタミナ      ->",{490,185},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "攻撃力        ->",{490,215},{1.0f,1.0f },20,0,LAYER::UI });
				IpSceneMng.AddDrawQue({ "防御力        ->",{490,245},{1.0f,1.0f },20,0,LAYER::UI });

				IpSceneMng.AddDrawQue({ "決定",{270,450},{1.0f,1.0f },20,0,LAYER::UI });


				//number.Draw({ 330, 155 }, { 0.2f,0.2f }, _statusOld[Status_ID::レベル], 0);

				//number.Draw({ 620,155 }, { 0.2f,0.2f }, _statusOld[Status_ID::HP], 0);
				//number.Draw({ 620,185 }, { 0.2f,0.2f }, _statusOld[Status_ID::スタミナ], 0);
				//number.Draw({ 620,215 }, { 0.2f,0.2f }, _statusOld[Status_ID::攻撃力], 0);
				//number.Draw({ 620,245 }, { 0.2f,0.2f }, _statusOld[Status_ID::防御力], 0);

				color({ 730,155 }, Status_ID::HP);
				color({ 730,185 }, Status_ID::スタミナ);
				color({ 730,215 }, Status_ID::攻撃力);
				color({ 730,245 }, Status_ID::防御力);

				//number.Draw({ 330, 185 }, { 0.2f,0.2f }, _experience[-1], 0);
				//_experience[-1] == _experience[0] ? number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 0) : number.Draw({ 430, 185 }, { 0.2f,0.2f }, _experience[0], 1);
				//number.Draw({ 430, 215 }, { 0.2f,0.2f }, _experience[_status[Status_ID::レベル]], 0);



				color({ 430, 155 }, Status_ID::レベル);
				color({ 430, 265 }, Status_ID::体力);
				color({ 430, 295 }, Status_ID::持久力);
				color({ 430, 325 }, Status_ID::筋力);
				color({ 430, 355 }, Status_ID::敏捷);
				color({ 430, 385 }, Status_ID::回復);

				//status_ != Status_ID::MAX ? IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {200,265 + 30 * (static_cast<int>(status_) - (static_cast<int>(Status_ID::体力))) }, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI }) :
				//	IpSceneMng.AddDrawQue({ IMAGE_ID("セレクト")[0], {250,450}, { 0,0 }, { 1.0f,1.0f }, false, 0, 1, LAYER::UI });




				break;
			case MeanID::保存:
				break;
			case MeanID::終了:
				DxLib_End();
				break;

			default:
				break;
			}

		}





	}
	ScreenFlip();
}


