#pragma once
#include <functional>
#include <vector>
#include <BaseScene.h>
#include <Obj.h>
#include <FuncBullet.h>
#include <FuncSlash.h>
#include <FuncCheck.h>
#include "FuncMove.h"

#include <FuncLevelUp.h>
#include <InputState.h>
// �t�@���N
using funcAct = std::function<bool(ActQueT&, void*)>;				

enum class CHIP_TYPE
{
	�X1,
	�X2,
	�X3
};



class GameScene :
	public BaseScene
{
public:
	GameScene();													
	~GameScene();
	unique_Base Update(unique_Base own) override;					// �X�V

private:
	// �t�@���N-�t�����h
	friend FuncBullet;
	friend FuncSlash;
	friend FuncCheck;
	friend FuncLevelUp;
	friend FuncMove;

	void funcInit(void);											// �t�@���N������
	void RunActQue(std::vector<ActQueT> actList) override;			// �t�@���N�����L���[

	std::map<CHIP_TYPE, std::function<void(void)>> _Draw;			// �`��֐���	
	std::map<CHIP_TYPE, std::function<void(void)>> _Init;			// �`��֐���	



	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
	std::map<ACT_QUE, funcAct> funcQue;								// �t�@���N�����L���[

	std::shared_ptr<InputState>_input;								// ���߯Ă��ư��߲���錾


	// �}�b�v������
	void MapInit(void);											// �N���X1

	// ��������
	int _shakeCount;
};
