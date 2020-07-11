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
	unique_Base Update(unique_Base own) override;					// çXêV
	Vector2 mapPos;
	int chip[75][75];
private:
	void Draw(void);
	void CameraUpdata(void);
	std::unique_ptr<MapState> _mapState;
	std::unique_ptr<Player> _player;

};

