#pragma once



enum STATUS														//�����X�e�[�^�X
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

enum STATUS_UP													//�����X�e�[�^�X
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

	void Updata(void);											//�X�e�[�^�X�̍X�V
	int level;													//���x��
	int experience[LevelMax];									//�K�v�Ȍo���l

	int _status[STATUS::MAX];									//�X�e�[�^�X
	int _statusUp[STATUS_UP::����_MAX];							//�����X�e�[�^�X

};

