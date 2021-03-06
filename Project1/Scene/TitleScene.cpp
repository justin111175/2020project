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
	IpImageMng.GetID("タイトル", "image/title.png", { 1280,800 }, { 1,1 });
	IpImageMng.GetID("選択", "image/textplate.png", { 486,150 }, { 1,1 });
	
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

	//タイトル描画
	IpSceneMng.AddDrawQue({ IMAGE_ID("タイトル")[0],{0,0},{0,0},{1.0f,1.0f},false,0,0,LAYER::BG });
	IpSceneMng.AddDrawQue({ IMAGE_ID("選択")[0],{400.0,420 + 85.0 * _select.s_id.Title} ,{0,0},{1.0f,1.0f},false,0,0,LAYER::UI });

	//選択
	_select.Updata(IpSceneMng._input, INPUT_ID::UP, SceneSel::TITLE, 2,-1);
	_select.Updata(IpSceneMng._input, INPUT_ID::DOWN, SceneSel::TITLE, 2,1);


	
	
	if (((*_Input).state(INPUT_ID::BTN_1).first && !(*_Input).state(INPUT_ID::BTN_1).second))
	{
		switch (_select.s_id.Title)
		{
		case 0:		//新しいゲーム	

			return std::make_unique<LoadScene>();
			break;
			
		case 1:		//データ読み込む
			IpSceneMng._chipType.first = CHIP_TYPE::森1;
			return std::make_unique<LoadScene>();
			break;
		case 2:		//ゲーム終了
			DxLib_End();
			break;
		default:
			break;
		}
	}

	_objList.erase(std::remove_if(
		_objList.begin(),									// チェック範囲の開始
		_objList.end(),										// チェック範囲の終了
		[](sharedObj& obj) {return (*obj).isDead(); }),		// ラムダ式()
		_objList.end());

	return std::move(own);

}


