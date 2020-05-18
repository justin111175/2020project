#pragma once


enum STATUS
{
	HP,
	MP,
	UŒ‚—Í,
	–hŒä—Í,
	MAX
};



struct level
{
public:
	void Init(void);											// ‰Šú‰»




	int levelCnt;

	//int vitality;			//Šˆ—Í

	int experience[10];   //ŒoŒ±’l

	int _status[STATUS::MAX];


};

