#include "level.h"



//�X�e�[�^�X�̏�����
void Level::Init(void)
{
	level = 1;

	_status[STATUS::HP] = 100;
	_status[STATUS::MP] = 100;
	_status[STATUS::����] = 9999;
	_status[STATUS::�U����] = 0;
	_status[STATUS::�h���] = 0;
	_status[STATUS::�q��] = 0;
	_status[STATUS::��] = 0;

	_statusUp[STATUS_UP::����_��] = 10;
	_statusUp[STATUS_UP::����_�U����] =0;
	_statusUp[STATUS_UP::����_�ő�HP] =0;
	_statusUp[STATUS_UP::����_�ő�MP] = 0;
	_statusUp[STATUS_UP::����_�q��] = 0;
	_statusUp[STATUS_UP::����_�h���] = 0;
	_statusUp[STATUS_UP::�c��{�[�i�X�|�C���g] = 5;


}

//�X�e�[�^�X�̍X�V
void Level::Updata(void)
{
	_status[STATUS::�U����] = static_cast<int>(_statusUp[STATUS_UP::����_�U����]*1.3);
	_status[STATUS::�h���] = static_cast<int>(_statusUp[STATUS_UP::����_�h���] * 1.3);
	

	_status[STATUS::HP] = BaseHP + ((level * 100) * 3 / 10)+_statusUp[static_cast<int>(STATUS_UP::����_�ő�HP)] * 30;
	_status[STATUS::MP] = BaseMP + _statusUp[STATUS_UP::����_�ő�MP] * 30;
	
	_status[STATUS::��] = static_cast<int>(_statusUp[STATUS_UP::����_��] * 1.3);

	_status[STATUS::�q��] = static_cast<int>(_statusUp[STATUS_UP::����_�q��] * 1.3);

}

