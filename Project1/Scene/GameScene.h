#pragma once
#include <functional>
#include <vector>
#include <BaseScene.h>
#include <Obj.h>
#include <FuncBullet.h>
#include <FuncSlash.h>
#include <FuncCheck.h>
#include <InputState.h>

// �t�@���N
using funcAct = std::function<bool(ActQueT&, void*)>;				


class GameScene :
	public BaseScene
{
public:
	GameScene();													
	~GameScene();
	unique_Base Update(unique_Base own) override;					// �X�V

private:
	// �t�@���N-�t�����h
	//friend FuncCheckSelf;
	//friend FuncCheckDown;
	//friend FuncCheckRight;
	//friend FuncCheckLeft;
	//friend FuncCheckLRHit;
	//friend FuncCheckOn;

	friend FuncBullet;
	friend FuncSlash;
	friend FuncCheck;


	void funcInit(void);											// �t�@���N������
	void RunActQue(std::vector<ActQueT> actList) override;			// �t�@���N�����L���[
	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
	std::map<ACT_QUE, funcAct> funcQue;								// �t�@���N�����L���[

	std::shared_ptr<InputState>_input;							// ���߯Ă��ư��߲���錾



	// �}�b�v������
	void MapInit_1(void);											// �N���X1

	
	// ��������
	int _shakeCount;
};
