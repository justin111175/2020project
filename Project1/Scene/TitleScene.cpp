#include "TitleScene.h"
#include "algorithm"
#include "SceneMng.h"
#include <ImageMng.h>
#include <GameScene.h>
#include <Dxlib.h>

TitleScene::TitleScene()
{
	IpImageMng.GetID("タイトル", "image/title.png", { 1280,720 }, { 1,1 });
	IpImageMng.GetID("選択", "image/textplate.png", { 486,150 }, { 1,1 });
	_TitleId = 新しいゲーム;
}

TitleScene::~TitleScene()
{
}

unique_Base TitleScene::Update(unique_Base own)
{
	






	//return std::make_unique<LoadingScene>();
	
	auto PlObj = std::find_if(_objList.begin(), _objList.end(), [](sharedObj obj) {return (*obj)._unitID == UNIT_ID::PLAYER; });

	auto _level = [](sharedObj& plobj) {return (*plobj)._level; };
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






	IpSceneMng.AddDrawQue({ IMAGE_ID("タイトル")[0],0,0,0,0,1.0f,1.0f,0,0,LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("選択")[0],400,370+76* _TitleId,0,0,1.0f,1.0f,0,0,LAYER::UI });


	if ((*_Input).state(INPUT_ID::UP).first && !(*_Input).state(INPUT_ID::UP).second)
	{
		if (_TitleId > 新しいゲーム)
		{
			_TitleId = (TITLE_ID)(_TitleId - 1);
		}
		else
		{
			_TitleId = 終了;
		}
	}
	if ((*_Input).state(INPUT_ID::DOWN).first && !(*_Input).state(INPUT_ID::DOWN).second)
	{
		if (_TitleId < 終了)
		{
			_TitleId = (TITLE_ID)(_TitleId + 1);
		}
		else
		{
			_TitleId = 新しいゲーム;
		}
	}

	FILE* fp = NULL;
	switch (_TitleId)
	{
	case 新しいゲーム:

		if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
		{
			return std::make_unique<GameScene>();

		}
		break;
	case データ読み込む:


		
		if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
		{
			if (fopen_s(&fp, "Dat/player.dat", "rb") == 0)
			{
				return std::make_unique<GameScene>();


			}


		}
		break;
	case 終了:
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
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());

	return std::move(own);

}

void TitleScene::funcInit(void)
{
}

void TitleScene::RunActQue(std::vector<ActQueT> actList)
{
}
