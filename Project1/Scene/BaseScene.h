#pragma once
#include <memory>
#include "Obj.h"
#include <tuple>														//�v�f���O�ȏ���Ǘ����鎞���g��

// �N���X�̃v���g�^�C�v�錾
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
	Vector2 _screenPos;													// �`����W
protected:
	void FadeInit(std::string fadeType);								// Fade������
	bool FadeUpdate(void);												// Fade�X�V
private:
	int _fadeScrID;														// Fade�`��ID
	std::string _fadeType;												// Fade�^�C�v
};


