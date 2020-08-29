#pragma once
#include "BaseScene.h"
#include <vector>
#include "../Obj.h"


enum class TitleMean
{
	新しいゲーム,
	ゲーム終了
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;					// 更新
	void BaseDraw(void) override;					                // 更新

private:
	void Draw(void);
	void Init(void);
	std::vector<sharedObj> _objList;								// シェアポインタ-Obj
	void MeanCtl(void);

	TitleMean titleMean_;
	bool sceneFlag_;
};