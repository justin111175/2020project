#pragma once
#include "BaseScene.h"
#include <vector>
#include "..\Obj.h"
#include <functional>

enum class CHIP_TYPE
{
	森1,
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
	unique_Base Update(unique_Base own) override;					// 更新
private:

	void MapInit(void);

	std::vector<sharedObj> _objList;								// シェアポインタ-Obj

	
	std::map<CHIP_TYPE, std::function<void(void)>> _Init;

};

