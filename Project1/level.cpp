#include "level.h"




void Level::Init(void)
{


	level = 1;

	_status[STATUS::HP] = 100;
	_status[STATUS::MP] = 100;
	_status[STATUS::‚¨‹à] = 9999;
	_status[STATUS::UŒ‚—Í] = 0;
	_status[STATUS::–hŒä—Í] = 0;
	_status[STATUS::•q·] = 0;
	_status[STATUS::‰ñ•œ] = 0;

	_statusUp[STATUS_UP::‹­‰»_‰ñ•œ] = 10;
	_statusUp[STATUS_UP::‹­‰»_UŒ‚—Í] =0;
	_statusUp[STATUS_UP::‹­‰»_Å‘åHP] =0;
	_statusUp[STATUS_UP::‹­‰»_Å‘åMP] = 0;
	_statusUp[STATUS_UP::‹­‰»_•q·] = 0;
	_statusUp[STATUS_UP::‹­‰»_–hŒä—Í] = 0;
	_statusUp[STATUS_UP::c‚éƒ{[ƒiƒXƒ|ƒCƒ“ƒg] = 5;


}

void Level::Updata(void)
{
	_status[STATUS::UŒ‚—Í] = _statusUp[STATUS_UP::‹­‰»_UŒ‚—Í]*1.3;
	_status[STATUS::–hŒä—Í] = _statusUp[STATUS_UP::‹­‰»_–hŒä—Í] * 1.3;
	

	_status[STATUS::HP] = BaseHP + ((level * 100) * 3 / 10)+_statusUp[STATUS_UP::‹­‰»_Å‘åHP] * 30;
	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::‹­‰»_Å‘åMP] * 30;
	
	_status[STATUS::‰ñ•œ] = _statusUp[STATUS_UP::‹­‰»_‰ñ•œ] * 1.3;

	_status[STATUS::•q·] = _statusUp[STATUS_UP::‹­‰»_•q·] * 1.3;

}

