#pragma once


enum class Status_ID														//強化ステータス
{
	HP,
	最大HP,
	MP,
	最大MP,
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