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

#define s1 (STATUS::MAX)(STATUS::MAX-1)

struct level
{
public:
	void Init(void);											// ������

	void Updata(void);



	//int vitality;			//����
	int level;
	int experience[LevelMax];   //�o���l

	int _status[STATUS::MAX];
	int _statusUp[STATUS_UP::�c��{�[�i�X�|�C���g];

};

