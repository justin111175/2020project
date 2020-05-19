#pragma once


enum STATUS
{
	レベル,
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

};

#define LevelMax 99

struct level
{
public:
	void Init(void);											// 初期化





	//int vitality;			//活力

	int experience[LevelMax];   //経験値

	int _status[STATUS::MAX];
	int _statusUp[STATUS_UP::残るボーナスポイント];

};

