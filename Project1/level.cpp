#include "level.h"




void level::Init(void)
{


	for (int x=1; x <= LevelMax; x++)
	{
		experience[x] = 100*x;
	}

	_status[STATUS::HP] = 100;
	_status[STATUS::���x��] = 1;
	_status[STATUS::����] = 999999;
	_status[STATUS::�U����] = 0;
	_status[STATUS::�h���] = 0;
	_status[STATUS::�q��] = 0;
	_status[STATUS::��] = 0;

	_statusUp[STATUS_UP::����_��] = 99;
	_statusUp[STATUS_UP::����_�U����] =99;
	_statusUp[STATUS_UP::����_�ő�HP] =99;
	_statusUp[STATUS_UP::����_�ő�MP] = 99;
	_statusUp[STATUS_UP::����_�q��] = 99;
	_statusUp[STATUS_UP::����_�h���] = 99;
	_statusUp[STATUS_UP::�c��{�[�i�X�|�C���g] = 99;

}

