#pragma once
#include "BaseScene.h"
#include <vector>
#include <Obj.h>
#include <InputState.h>
#include <functional>


enum MEAN_ID
{
	�V�����Q�[��,
	�f�[�^�ǂݍ���,
	�Q�[���I��
};



using funcAct = std::function<bool(ActQueT&, void*)>;

class TitleScene :
	public BaseScene
{
public:
	TitleScene();
	~TitleScene();
	unique_Base Update(unique_Base own) override;					// �X�V

private:


	void funcInit(void);											// �t�@���N������
	void RunActQue(std::vector<ActQueT> actList) override;			// �t�@���N�����L���[
	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj
	std::map<ACT_QUE, funcAct> funcQue;							// �t�@���N�����L���[
	MEAN_ID meanID;
	//std::shared_ptr<InputState>_input;							// ���߯Ă��ư��߲���錾

};