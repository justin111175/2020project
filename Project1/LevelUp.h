#pragma once
#include "Obj.h"


class LevelUp :
	public Obj
{
public:
	LevelUp();
	LevelUp(UNIT_ID unitID, Vector2Dbl pos, Vector2Dbl size);
	~LevelUp();

private:
	void Init(void);
	void Update(sharedObj plObj) override;
	bool SetAlive(bool alive);										// ê∂Ç´ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©

	bool DestroyPrpc(void);

};