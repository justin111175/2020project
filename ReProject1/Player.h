#pragma once
#include "common/Vector2.h"
#include "common/Input/InputID.h"
#include"common/Input/Controller.h"
#include <memory>



enum class Dir
{
	Up,
	Down,
	Right,
	Left,
	stay
};
class Player
{
public:
	Player(Vector2&& pos);
	~Player();
	
	int GetScreenId(void);

	void Draw(void);
	void Run(void);
	void Move(InputID id);
	Vector2 _pos;
	Dir _dir;

	bool _runFlag;
private:
	int screenID;

	void Init(void);
	Vector2 _size;
	std::unique_ptr<Controller> controller;

};

