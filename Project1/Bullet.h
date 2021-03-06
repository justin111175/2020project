#pragma once
#include "Obj.h"

#include <SceneMng.h>

#define BulletSpeed 3.0

class SceneMng;

class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(UNIT_ID unitID, Vector2Dbl pos, DIR_ID movetype, Vector2Dbl size);
	~Bullet();

private:
	void Init(void);
	void Update(void) override;
	bool DestroyPrpc(void);

};


