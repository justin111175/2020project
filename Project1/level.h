#pragma once


enum STATUS
{
	HP,
	MP,
	�U����,
	�h���,
	MAX
};



struct level
{
public:
	void Init(void);											// ������




	int levelCnt;

	//int vitality;			//����

	int experience[10];   //�o���l

	int _status[STATUS::MAX];


};

