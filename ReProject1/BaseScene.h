#pragma once
#include <memory>
#include<string>
#include "common/Vector2.h"



class BaseScene;
using unique_Base = std::unique_ptr<BaseScene>;							// �X�}�[�g�|�C���^-BaseScene


class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;					// �������z�֐�

protected:
	void FadeInit(std::string fadeType);								// Fade������
	bool FadeUpdate(void);												// Fade�X�V
private:
	int _fadeScrID;														// Fade�`��ID
	std::string _fadeType;												// Fade�^�C�v
};


