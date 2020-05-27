#pragma once
#include "BaseScene.h"
#include <vector>
#include <Obj.h>
#include <InputState.h>
#include <functional>





using funcAct = std::function<bool(ActQueT&, void*)>;

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;					// 更新

private:

	void funcInit(void);											// ファンク初期化
	void RunActQue(std::vector<ActQueT> actList) override;			// ファンク活動キュー
	std::vector<sharedObj> _objList;								// シェアポインタ-Obj
	std::map<ACT_QUE, funcAct> funcQue;							// ファンク活動キュー
	//std::shared_ptr<InputState>_input;							// ｲﾝﾌﾟｯﾄのﾕﾆｰｸﾎﾟｲﾝﾀ宣言

};