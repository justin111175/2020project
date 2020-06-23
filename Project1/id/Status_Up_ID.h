#pragma once


enum class Status_Up_ID													//強化ステータス
{
	攻撃力,
	防御力,
	敏捷,
	回復,
	最大HP,
	最大MP,
	残るボーナスポイント,
	MAX

};
Status_Up_ID begin(Status_Up_ID);
Status_Up_ID end(Status_Up_ID);
Status_Up_ID operator*(Status_Up_ID& key);
Status_Up_ID operator++(Status_Up_ID& key);