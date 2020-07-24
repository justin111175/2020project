#pragma once


enum class MeanID
{
	ステータス,
	保存,
	終了,
	MAX
};

MeanID begin(MeanID);
MeanID end(MeanID);
MeanID operator*(MeanID key);
MeanID operator++(MeanID& key);