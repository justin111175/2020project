#pragma once
#include "Obj.h"


#include <SceneMng.h>


class SceneMng;

class Slash :
	public Obj
{
public:
	Slash();
	Slash(UNIT_ID unitID, Vector2Dbl pos,Vector2 size, MOVE_TYPE movetype);
	~Slash();

private:
	void Init(void);
	void Update(sharedObj plObj) override;
	bool DestroyPrpc(void);
	bool Cntbool;
	double cnt;
};
