#pragma once
#include "Vector2.h"

enum class TYPE
{
	����,
	���S
};

bool CheckBox(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2, TYPE type);//pos�͕`�ʂ̍���[�p

bool CheckCircle(Vector2 pos1, double rang1, Vector2 pos2, double rang2);		//pos�͕`�ʂ̒��S�p


