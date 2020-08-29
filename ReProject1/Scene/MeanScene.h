#pragma once
#include "BaseScene.h"
#include <memory>
#include "../common/Number.h"
#include "../id/MeanID.h"
#include "../Player.h"


class MeanScene :
    public BaseScene
{

public:

	MeanScene(unique_Base own);
	~MeanScene();
	unique_Base Update(unique_Base own) override;					// 更新
	void BaseDraw(void) override;					// 更新
private:
	unique_Base childScene_;
	int cnt_;

	MeanState meanState_;
	Number number;												//数字用
	MeanID meanID_;

	int _screenID;

};

