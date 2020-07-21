#pragma once
#include "Vector2.h"

enum class TYPE
{
	左上,
	中心
};

bool CheckBox(Vector2 pos1, Vector2Dbl size1, Vector2 pos2, Vector2Dbl size2, TYPE type);//posは描写の左上端用

bool CheckCircle(Vector2Dbl pos1, double rang1, Vector2Dbl pos2, double rang2);		//posは描写の中心用


