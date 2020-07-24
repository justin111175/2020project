#pragma once
#include "common/Vector2.h"
#include "common/Input/InputID.h"
#include"common/Input/Controller.h"
#include <memory>
#include "Obj.h"
#include "id/MeanID.h"
#include "common/Number.h"
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

enum class MeanState
{
	中,
	外
};

#define mean_size_Y 40

class Player:
	public Obj
{
public:
	Player();
	Player(Vector2&& pos, Vector2Dbl&& size, Vector2Dbl&& exrate);
	~Player();
	void Update(void) override;									// 更新


	void SetDir(InputID id);
	void MeanCtl(InputID id);

	bool _runFlag;
	bool _meanFlag;
private:

	Permit_Data _pData;

	void Move(void);
	void Init(void);
	std::unique_ptr<Controller> controller;
	void Camera(void);

	std::vector<std::string> meanType;									// 支払い手法
	MeanID meanID_;
	Status_ID status_;
	MeanState meanState_;

	Number number;												//数字用

	void StateInit(void);
};

