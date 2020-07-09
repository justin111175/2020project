#pragma once
#include "BaseScene.h"
#include <functional>
#include <Obj.h>
#include <vector>

//#include "GameScene.h"



enum class CHIP_TYPE
{
	�X1,
	�X2,
	�X3,
	MAX
};



class LoadScene:
	public BaseScene
{
public:
	
	static LoadScene& GetInstance()
	{
		static LoadScene s_Instance;
		return s_Instance;
	}

	LoadScene();
	~LoadScene();
	unique_Base Update(unique_Base own) override;					// �X�V


	std::vector<sharedObj>_objList ;
	std::map<CHIP_TYPE, std::function<void(void)>> _Init;


private:
	void Clear(void);
	void MapInit(void);

};

