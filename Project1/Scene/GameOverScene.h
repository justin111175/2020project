#pragma once
#include "BaseScene.h"


class GameOverScene :
	public BaseScene
{
public:
	GameOverScene();											
	~GameOverScene();
	unique_Base Update(unique_Base own) override;				// �X�V
private:
	std::vector<sharedObj> _objList;							// �V�F�A�|�C���^-Obj
	void SoundInit(void);
	int cnt;
};

