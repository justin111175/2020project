#include "level.h"




void level::Init(void)
{


	for (int x=1; x <= LevelMax; x++)
	{
		experience[x] = 100*x;
	}

	_status[STATUS::HP] = 100;
	_status[STATUS::ƒŒƒxƒ‹] = 1;
	_status[STATUS::‚¨‹à] = 999999;
	_status[STATUS::UŒ‚—Í] = 0;
	_status[STATUS::–hŒä—Í] = 0;
	_status[STATUS::•q·] = 0;
	_status[STATUS::‰ñ•œ] = 0;

	_statusUp[STATUS_UP::‹­‰»_‰ñ•œ] = 10;
	_statusUp[STATUS_UP::‹­‰»_UŒ‚—Í] =99;
	_statusUp[STATUS_UP::‹­‰»_Å‘åHP] =99;
	_statusUp[STATUS_UP::‹­‰»_Å‘åMP] = 99;
	_statusUp[STATUS_UP::‹­‰»_•q·] = 99;
	_statusUp[STATUS_UP::‹­‰»_–hŒä—Í] = 99;
	_statusUp[STATUS_UP::Žc‚éƒ{[ƒiƒXƒ|ƒCƒ“ƒg] = 99;

}

