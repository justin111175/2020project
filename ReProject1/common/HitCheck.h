#pragma once
#include "Vector2.h"

enum class TYPE
{
	����,
	���S
};

bool CheckBox(Vector2Dbl pos1, Vector2Dbl size1, Vector2Dbl pos2, Vector2Dbl size2, TYPE type);//pos�͕`�ʂ̍���[�p
bool CheckBox(Vector2Dbl pos1, Vector2Dbl size1,Vector2Dbl speed, Vector2Dbl pos2, Vector2Dbl size2, TYPE type);//pos�͕`�ʂ̍���[�p

bool CheckCircle(Vector2Dbl pos1, double rang1, Vector2Dbl pos2, double rang2);		//pos�͕`�ʂ̒��S�p


