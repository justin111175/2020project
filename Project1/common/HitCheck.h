#pragma once
#include "Vector2.h"

enum class TYPE
{
	¶ã,
	S
};

bool CheckBox(Vector2Dbl pos1, Vector2Dbl size1, Vector2Dbl pos2, Vector2Dbl size2, TYPE type);//posÍ`ÊÌ¶ã[p
bool CheckBox(Vector2Dbl pos1, Vector2Dbl size1,Vector2Dbl speed, Vector2Dbl pos2, Vector2Dbl size2, TYPE type);//posÍ`ÊÌ¶ã[p

bool CheckCircle(Vector2Dbl pos1, double rang1, Vector2Dbl pos2, double rang2);		//posÍ`ÊÌSp


