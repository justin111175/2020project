#pragma once
#include "BaseScene.h"
#include <vector>
#include "MapState.h"
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
	Vector2 mapPos;
private:
	void Draw(void);
	
	std::unique_ptr<MapState> _mapState;
	std::unique_ptr<Player> _player;

};

