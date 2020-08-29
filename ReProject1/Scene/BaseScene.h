#pragma once
#include <memory>
#include <string>
#include "..\common\Vector2.h"
#include "..\Obj.h"
#include <map>
#include "../common/Input/Controller.h"

class BaseScene;


enum class ACT_QUE
{
	NON,																// �������Ȃ�
	SHOT,
	SLASH,
	CHECK,
	LEVELUP,
	MOVE
};

enum class ACT_STATE
{
	ACT_QUE,															// �����L���[
	Obj,																// Obj
	MAX
};
using unique_Base = std::unique_ptr<BaseScene>;							// �X�}�[�g�|�C���^-BaseScene
using ActQueT = std::pair<ACT_QUE, Obj&>;								// ��ԁAObj


class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	virtual unique_Base Update(unique_Base own) = 0;					// �������z�֐�
	virtual void RunActQue(std::vector<ActQueT> actList);				// �t�@���N�����L���[
	virtual void BaseDraw(void) = 0;					                // �X�V

protected:
	void FadeInit(std::string fadeType);								// Fade������
	bool FadeUpdate(void);												// Fade�X�V
	std::map<conType, std::unique_ptr<Controller>> controller;

private:
	int _fadeScrID;														// Fade�`��ID
	std::string _fadeType;												// Fade�^�C�v
};


