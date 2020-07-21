#include "HitCheck.h"


bool CheckBox(Vector2 pos1, Vector2Dbl size1, Vector2 pos2, Vector2Dbl size2, TYPE type)
{
	switch (type)
	{
	case TYPE::¶ã:
		if (pos1.x + size1.x	>	pos2.x				&&
			pos1.x				<	pos2.x + size2.x	&&
			pos1.y				<	pos2.y + size2.y	&&
			pos1.y + size1.y	>	pos2.y)
		{
			return true;;
		}
		return false;
	case TYPE::’†S:
		if (pos1.x + size1.x / 2 > pos2.x - size2.x / 2 &&
			pos1.x - size1.x / 2 < pos2.x + size2.x / 2 &&
			pos1.y - size1.y / 2 < pos2.y + size2.y / 2 &&
			pos1.y + size1.y / 2 > pos2.y - size2.y / 2)
		{
			return true;
		}
		return false;

	default:
		break;
	}

}

//bool CheckBox(Vector2Dbl pos1, Vector2Dbl size1, Vector2Dbl speed, Vector2Dbl pos2, Vector2Dbl size2, TYPE type)
//{
//	if (pos1.x + size1.x+speed.x > pos2.x- size1.x &&
//		pos1.x + speed.x < pos2.x + size2.x &&
//		pos1.y	+speed.y			<	pos2.y + size2.y &&
//		pos1.y + size1.y+speed.y	>	pos2.y- size1.y)
//	{
//		return true;;
//	}
//	return false;
//}

bool CheckCircle(Vector2Dbl pos1, double rang1, Vector2Dbl pos2, double rang2)
{
	Vector2Dbl Long = { pos1.x - pos2.x	,pos1.y - pos2.y };
	double rangLong = rang1 + rang2;
	if (((Long.x * Long.x)+ (Long.y * Long.y)) < (rangLong * rangLong))
	{
		return true;
	}
    return false;
}


