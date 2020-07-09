#pragma once
#include "Obj.h"


#include <SceneMng.h>


class SceneMng;

class Slash :
	public Obj
{
public:
	Slash();
	Slash(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size, DIR_ID movetype);
	~Slash();

private:
	void Init(void);
	void Update(void) override;
	bool SetAlive(bool alive);										// ê∂Ç´ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©

	bool DestroyPrpc(void);
	bool Cntbool;
	double cnt;
};
