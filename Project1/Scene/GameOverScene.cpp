#include "GameOverScene.h"
#include "DxLib.h"
#include "GameScene.h"
#include "ImageMng.h"
#include "SceneMng.h"
#include "TitleScene.h"
#include "algorithm"

GameOverScene::GameOverScene()
{
	IpImageMng.GetID("ゲームオーバー", "image/gmaeover.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("ゲームオーバーSel", "image/gameoverSel.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("messagecursorD3", "image/messagecursorD3.png", { 56,40 }, { 1,1 });
	IpImageMng.GetID("BG", "image/bg.png", { 1280,720 }, { 1,1 });


	cnt = -100;
	//_OverId = データ読み込む;
}

GameOverScene::~GameOverScene()
{
}

unique_Base GameOverScene::Update(unique_Base own)
{
	//アニメ
	if (cnt < 0)
	{
		if (IpSceneMng.frames() % 60)
		{
			cnt++;
		}
	}

	IpSceneMng.AddDrawQue({ IMAGE_ID("BG")[0], {0,0},{0,0},{1.0f,1.0f},false,0,1,LAYER::BG });

	IpSceneMng.AddDrawQue({ IMAGE_ID("ゲームオーバー")[0], {0,cnt*1.0},{0,0},{1.0f,1.0f},false,0,1,LAYER::UI });
	if (cnt >= 0)
	{
		IpSceneMng.AddDrawQue({ IMAGE_ID("ゲームオーバーSel")[0], {0,0},{0,0},{1.0f,1.0f},false,0,1,LAYER::UI });
		IpSceneMng.AddDrawQue({ IMAGE_ID("messagecursorD3")[0], {480.0,415 + (_select.s_id.GameOver) * 110.0},{0,0},{1.0f,1.0f},false,0,1,LAYER::UI });

	}
	
	//選択
	_select.Updata(IpSceneMng._input, INPUT_ID::UP, SceneSel::GameOver, 1, -1);
	_select.Updata(IpSceneMng._input, INPUT_ID::DOWN, SceneSel::GameOver, 1, 1);


	FILE* fp = NULL;	

	if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
	{
		switch (_select.s_id.GameOver)
		{
		case 0:			//データ読み込む
			if (fopen_s(&fp, "player.dat", "rb") == 0)
			{
				return std::make_unique<GameScene>();
			}
			break;
		case 1:			//ゲーム終了
			DxLib_End();
			break;
		default:
			break;
		}
	}
	//auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

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

	// 描画を消す
	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());


	return std::move(own);
}

void GameOverScene::SoundInit(void)
{
	IpImageMng.GetSound("ボタン音", "image/sound/bottom.mp3");

}
