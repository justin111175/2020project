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
	unique_Base Update(unique_Base own) override;					// �X�V

private:
	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
	std::map<ACT_QUE, funcAct> funcQue;								// �t�@���N�����L���[
};