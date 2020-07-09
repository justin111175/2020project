#pragma once
#include <functional>
#include <vector>
#include <BaseScene.h>
#include <Obj.h>
#include <FuncBullet.h>
#include <FuncSlash.h>
#include <FuncCheck.h>
#include "FuncMove.h"

#include <FuncLevelUp.h>
#include <InputState.h>
#include "LoadScene.h"

// ファンク
using funcAct = std::function<bool(ActQueT&, void*)>;				

//enum class CHIP_TYPE
//{
//	森1,
//	森2,
//	森3,
//	MAX
//};



class GameScene :
	public BaseScene
{
public:
	static GameScene& GetInstance()
	{
		static GameScene s_Instance;
		return s_Instance;
	}


	GameScene();													
	~GameScene();
	unique_Base Update(unique_Base own) override;					// 更新
	bool Clear(void);

private:
	// ファンク-フレンド
	friend FuncBullet;
	friend FuncSlash;
	friend FuncCheck;
	friend FuncLevelUp;
	friend FuncMove;

	void funcInit(void);											// ファンク初期化
	void RunActQue(std::vector<ActQueT> actList) override;			// ファンク活動キュー

	std::map<CHIP_TYPE, std::function<void(void)>> _Draw;			// 描画関数化	

	
	std::vector<sharedObj> _objList=LoadScene::GetInstance()._objList;								// シェアポインタ-Obj
	std::map<CHIP_TYPE, std::function<void(void)>> _Init=LoadScene::GetInstance()._Init;			// 描画関数化	


	std::map<ACT_QUE, funcAct> funcQue;								// ファンク活動キュー

	std::shared_ptr<InputState>_input;								// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言


	// マップ初期化
	void MapBG(void);											// クラス1

	// 音初期化
	int _shakeCount;
	
};
