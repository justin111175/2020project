#pragma once
#include "common/Vector2.h"
#include "common/Input/InputID.h"
#include"common/Input/Controller.h"
#include <memory>
#include "Obj.h"


struct DirBit
{
	unsigned int UP : 1;
	unsigned int RIGHT : 1;
	unsigned int DOWN : 1;
	unsigned int LEFT : 1;

};

union Permit_Data
{
	DirBit _bit;
	unsigned int _flag;
};




class Player:
	public Obj
{
public:
	Player();
	Player(Vector2&& pos, Vector2Dbl&& size, Vector2Dbl&& exrate);
	~Player();
	void Update(void) override;									// çXêV


	void SetDir(InputID id);
	void Move(void);
	bool _runFlag;
private:

	Permit_Data _pData;

	void Init(void);
	std::unique_ptr<Controller> controller;
	void Camera(void);
};

