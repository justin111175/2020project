#pragma once


enum class Status_ID														//強化ステータス
{
	HP,
	最大HP,
	MP,
	最大MP,
	攻撃力,
	防御力,
	敏捷,
	回復,
	お金,
	MAX
};



Status_ID begin(Status_ID);
Status_ID end(Status_ID);
Status_ID operator*(Status_ID& key);
Status_ID operator++(Status_ID& key);