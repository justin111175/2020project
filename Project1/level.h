#pragma once



enum STATUS
{
	HP,
	MP,
	�U����,
	�h���,
	�q��,
	��,
	����,
	MAX
};

enum STATUS_UP
{
	����_�U����,
	����_�h���,
	����_�q��,
	����_��,
	����_�ő�HP,
	����_�ő�MP,
	�c��{�[�i�X�|�C���g,
	����_MAX

};

#define LevelMax 99
#define BaseHP 100
#define BaseMP 100


struct Level
{
public:
	void Init(void);											// ������

	void Updata(void);



	//int vitality;			//����
	int level;
	double experience[LevelMax];   //�o���l

	double _status[STATUS::MAX];
	double _statusUp[STATUS_UP::����_MAX];

};

