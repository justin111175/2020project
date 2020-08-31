#pragma once
#include "BaseScene.h"
#include <memory>
#include "../common/Number.h"
#include "../id/MeanID.h"
#include "../Player.h"


enum class DiffIndex
{
	�T���ł��ł���,
	�����������,
	���������ČN�͐_�l
};

class MeanScene :
    public BaseScene
{

public:

	MeanScene(unique_Base own);
	~MeanScene();
	unique_Base Update(unique_Base own) override;					// �X�V
	void BaseDraw(void) override;					// �X�V
private:
	unique_Base childScene_;
	int cnt_;

	MeanState meanState_;
	Number number;												//�����p
	MeanID meanID_;

	int _screenID;
	DiffIndex diffIndex_;
};

