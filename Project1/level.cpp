#include "level.h"




void level::Init(void)
{
	levelCnt = 1;


	for (int x=1; x <= 10; x++)
	{
		experience[x] = 100*x;
	}

	//vitality = 0;

	_sutetasu[sutetasu::HP] = 100;
	

}

