#pragma once
#include "BaseScene.h"
#include <vector>
#include "../Obj.h"
#include "../common/Input/Controller.h"


enum class TitleMean
{
	�V�����Q�[��,
	�Q�[���I��
};

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;					// �X�V

private:
	void Draw(void);
	void Init(void);
	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
	std::map<conType, std::unique_ptr<Controller>> controller;
	void MeanCtl(void);

	TitleMean titleMean_;
	bool sceneFlag_;
};