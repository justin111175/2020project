#pragma once
#include "Obj.h"

#include "Scene/SceneMng.h"

#define BulletSpeed 3.0

class SceneMng;

class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID, Vector2 pos, DIR_ID movetype, Vector2 size);
	Bullet(UNIT_ID unitID, Vector2 pos, double rad);
	~Bullet();

private:
	void Init(void);
	void Update(sharedObj& plObj) override;
	bool DestroyPrpc(void);
	DIR_ID movetype_;
};


