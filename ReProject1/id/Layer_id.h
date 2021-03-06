#pragma once

enum class LAYER
{		
	BG,											// 背景
	CHAR,										// キャラクター
	UI,											// UI
	MEAN,										//メニュー
	NUMBER,										//数字
	LETTER,										//文字
	EX,											// 一番前用
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER& key);
LAYER operator++(LAYER& key);
