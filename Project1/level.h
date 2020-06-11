#pragma once



enum STATUS
{
	HP,
	MP,
	攻撃力,
	防御力,
	敏捷,
	回復,
	お金,
	MAX
};

enum STATUS_UP
{
	強化_攻撃力,
	強化_防御力,
	強化_敏捷,
	強化_回復,
	強化_最大HP,
	強化_最大MP,
	残るボーナスポイント,
	強化_MAX

};

#define LevelMax 99
#define BaseHP 100
#define BaseMP 100


struct Level
{
public:
	void Init(void);											// 初期化

	void Updata(void);



	//int vitality;			//活力
	int level;
	double experience[LevelMax];   //経験値

	double _status[STATUS::MAX];
	double _statusUp[STATUS_UP::強化_MAX];

};

