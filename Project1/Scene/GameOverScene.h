#pragma once
#include "BaseScene.h"


class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();											
	~GameOverScene();
	unique_Base Update(unique_Base own) override;				// 更新
private:
	std::vector<sharedObj> _objList;							// シェアポインタ-Obj
	void SoundInit(void);
	int cnt;
};

