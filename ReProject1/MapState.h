#pragma once
#include "Player.h"
#include <memory>
#include "common/Vector2.h"


class MapState
{
public:

	MapState(Vector2 size);
	~MapState();
	int GetScreenId(void);

	void Draw(void);
	void Run(void);
private:
	int screenID;
	void Init(void);

	Vector2 _size;
};

