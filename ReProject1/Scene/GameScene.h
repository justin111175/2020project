#pragma once
#include "BaseScene.h"
#include <vector>
#include "..\Obj.h"
#include <functional>
#include "..\FuncCheck.h"
using funcAct = std::function<bool(ActQueT&, void*)>;


enum class CHIP_TYPE
{
	森1,
	test,
	MAX
};


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
private:
	friend FuncCheck;

	void FuncInit(void);											// ファンク初期化

	void RunActQue(std::vector<ActQueT> actList) override;			// ファンク活動キュー

	std::map<ACT_QUE, funcAct> funcQue;								// ファンク活動キュー

	void MapInit(void);

	std::vector<sharedObj> _objList;								// シェアポインタ-Obj


	std::map<CHIP_TYPE, std::function<void(void)>> _Init;
	std::map<CHIP_TYPE, std::function<void(void)>> _Draw;

};

