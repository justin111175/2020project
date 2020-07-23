#pragma once
#include "BaseScene.h"
#include <vector>
#include "..\Obj.h"
#include <functional>
#include "..\FuncCheck.h"
using funcAct = std::function<bool(ActQueT&, void*)>;


enum class CHIP_TYPE
{
	�n�}1,
	�n�}2,
	�n�}3,
	�n�}4,
	MAX
};


class GameScene :
    public BaseScene
{
public:

	static GameScene& GetInstance()
	{
		static GameScene s_Instance;
		return s_Instance;
	}

	GameScene();
	~GameScene();
	unique_Base Update(unique_Base own) override;					// �X�V
private:
	friend FuncCheck;

	void FuncInit(void);											// �t�@���N������

	void RunActQue(std::vector<ActQueT> actList) override;			// �t�@���N�����L���[

	std::map<ACT_QUE, funcAct> funcQue;								// �t�@���N�����L���[

	void MapInit(void);

	std::vector<sharedObj> _objList;								// �V�F�A�|�C���^-Obj

	void Clear(void);
	void ChangeInit(void);
	std::map<CHIP_TYPE, std::function<void(void)>> _Init;
	std::map<CHIP_TYPE, std::function<void(void)>> _Draw;
	std::map<CHIP_TYPE, std::function<void(void)>> _Change;

};

