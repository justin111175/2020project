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
	unique_Base Update(unique_Base own) override;					// �X�V

private:
	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
};