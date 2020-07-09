#pragma once
#include "BaseScene.h"
#include <vector>
#include <Obj.h>


class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;					// 更新

private:
	std::vector<sharedObj> _objList;								// シェアポインタ-Obj
};