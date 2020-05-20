#pragma once
#include "Obj.h"


#include <SceneMng.h>


class SceneMng;

class Slash :
	public Obj
{
public:
	Slash();
	Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size, MOVE_TYPE movetype);
	~Slash();

private:
	void Init(void);
	void Update(sharedObj plObj) override;
	bool SetAlive(bool alive);										// �����Ă��邩�ǂ���

	bool DestroyPrpc(void);
	bool Cntbool;
	double cnt;
};
