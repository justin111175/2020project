#pragma once
#include "common/Vector2.h"
#include "common/Input/InputID.h"
#include"common/Input/Controller.h"
#include <memory>
#include "Obj.h"



class Player:
	public Obj
{
public:
	Player();
	Player(Vector2Dbl&& pos, Vector2Dbl&& size, Vector2Dbl&& exrate);
	~Player();
	void Update(void) override;									// çXêV


	void SetDir(InputID id);
	void Move(void);
	bool _runFlag;
private:

	void Init(void);
	std::unique_ptr<Controller> controller;
	void Camera(void);
};

