#pragma once
#include <functional>
#include <vector>
#include <BaseScene.h>
#include <Obj.h>

// ファンク
using funcAct = std::function<bool(ActQueT&, void*)>;				


class GameScene :
	public BaseScene
{
public:
	GameScene();													
	~GameScene();
	unique_Base Update(unique_Base own) override;					// 更新

private:
	// ファンク-フレンド
	//friend FuncCheckSelf;
	//friend FuncCheckDown;
	//friend FuncCheckRight;
	//friend FuncCheckLeft;
	//friend FuncCheckLRHit;
	//friend FuncCheckOn;

	//void funcInit(void);											// ファンク初期化
	void RunActQue(std::vector<ActQueT> actList) override;			// ファンク活動キュー
	std::vector<sharedObj> _objList;								// シェアポインタ-Obj
	std::map<ACT_QUE, funcAct> funcQue;								// ファンク活動キュー

	// マップ初期化
	void MapInit_1(void);											// クラス1

	
	// 音初期化
	int _shakeCount;
};
