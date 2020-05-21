#include "level.h"




void level::Init(void)
{


	for (int x=1; x <= LevelMax; x++)
	{
		experience[x] = 100*x;
	}

	_status[STATUS::HP] = 100;
	_status[STATUS::MP] = 100;
	_status[STATUS::x] = 1;
	_status[STATUS::¨à] = 9999;
	_status[STATUS::UÍ] = 0;
	_status[STATUS::häÍ] = 0;
	_status[STATUS::q·] = 0;
	_status[STATUS::ñ] = 0;

	_statusUp[STATUS_UP::­»_ñ] = 10;
	_statusUp[STATUS_UP::­»_UÍ] =0;
	_statusUp[STATUS_UP::­»_ÅåHP] =0;
	_statusUp[STATUS_UP::­»_ÅåMP] = 0;
	_statusUp[STATUS_UP::­»_q·] = 0;
	_statusUp[STATUS_UP::­»_häÍ] = 0;
	_statusUp[STATUS_UP::cé{[iX|Cg] = 5;

}

void level::Updata(void)
{
	_status[STATUS::UÍ] = _statusUp[STATUS_UP::­»_UÍ]*1.3;
	_status[STATUS::häÍ] = _statusUp[STATUS_UP::­»_häÍ] * 1.3;
	

	_status[STATUS::HP] = BaseHP + ((_status[STATUS::x] * 100) * 3 / 10)+_statusUp[STATUS_UP::­»_ÅåHP] * 30;
	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::­»_ÅåMP] * 30;
	
	_status[STATUS::ñ] = _statusUp[STATUS_UP::­»_ñ] * 1.3;

	_status[STATUS::q·] = _statusUp[STATUS_UP::­»_q·] * 1.3;

}

