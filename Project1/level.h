#pragma once


enum sutetasu
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

	int _sutetasu[sutetasu::MAX];


};

