#include "SceneMng.h"
#include <Dxlib.h>
#include "GameScene.h"
#include "common/TimeCount.h"

SceneMng* SceneMng::sInstance = nullptr;



bool SceneMng::Run(void)
{
	if (!SysInit())
	{
		return false;
	}

	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{
		// clear：全ての要素を削除する

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// moveはコピーしません、所有権を渡すだけ

		//Draw();




		_frames++;
		_timeCount.Run();
	}


	return true;
}

const int SceneMng::frames(void) const
{
    return _frames;
}



SceneMng::SceneMng():
    ScreenSize{ 1280,800 }
{
    _blendCnt = 0;
    _frames = 0;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetWindowText("失われた都 アトランティス");		// タイトルバー
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:フルスクリーン
	if (DxLib_Init() == -1)												// DXラリブラリの初期化
	{
		return false;
	}





	// レイヤーの設定
	//_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::MEAN, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::NUMBER, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::LETTER, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	//_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	return true;
}


void SceneMng::Draw(void)
{
}