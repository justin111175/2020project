#pragma once


enum class Status_ID														//強化ステータス
{
	レベル,
	HP,
	//最大HP,
	スタミナ,
	攻撃力,
	防御力,
	//最大スタミナ,
	体力,
	持久力,
	筋力,
	敏捷,
	回復,
	MAX
};


Status_ID begin(Status_ID);
Status_ID end(Status_ID);
Status_ID operator*(Status_ID& key);
Status_ID operator++(Status_ID& key);