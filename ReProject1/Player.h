#pragma once
#include "common/Vector2.h"
#include "common/Input/InputID.h"
#include"common/Input/Controller.h"
#include <memory>
#include "Obj.h"
#include "id/MeanID.h"
#include "common/Number.h"
#include <functional>


enum class MeanState
{
	��,
	�O
};
enum class ModeState
{
	����,
	�����ړ�,
	���j���[,
	MAX
};

#define mean_size_Y 40

class Player:
	public Obj
{
public:
	Player();
	Player(Vector2&& pos, Vector2&& size, Vector2Dbl&& exrate);
	~Player();
	void Update(void) override;									// �X�V


	void SetDir(InputID id);
	void MeanCtl(InputID id);

	bool _meanFlag;
private:

	void ModeInit(void);
	ModeState modeState_;
	
	void Move(void);
	void Init(void);
	std::unique_ptr<Controller> controller;
	void Camera(void);

	MeanID meanID_;
	Status_ID status_;
	
	MeanState meanState_;

	Number number;												//�����p
	std::map<ModeState, std::function<void(void)>> ModeInit_;

	void StateInit(void);
};

