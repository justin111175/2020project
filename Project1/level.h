#pragma once


enum STATUS
{
	���x��,
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

};

#define LevelMax 99

struct level
{
public:
	void Init(void);											// ������





	//int vitality;			//����

	int experience[LevelMax];   //�o���l

	int _status[STATUS::MAX];
	int _statusUp[STATUS_UP::�c��{�[�i�X�|�C���g];

};

