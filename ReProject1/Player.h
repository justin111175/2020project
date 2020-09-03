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
	中,
	外
};
enum class ModeState
{
	普通,
	強制移動,
	メニュー,
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
	void Update(sharedObj& plObj) override;									// 更新


	void SetDir(InputID id);
	void MeanCtl(InputID id);
	void UIDraw(void);
	void Gekitai(double rad);
	bool _meanFlag;
private:
	void Save(void);
	void Read(void);
	void StatusUpdata(void);
	void ModeInit(void);
	ModeState modeState_;
	
	void Move(void);
	void Init(void);
	std::unique_ptr<Controller> controller;
	void Camera(void);

	MeanID meanID_;

	Status_ID status_;
	
	MeanState meanState_;

	Number number;												//数字用
	std::map<ModeState, std::function<void(void)>> ModeInit_;

	void StateInit(void);
	float HpRatio;
	float MpRatio;

};

