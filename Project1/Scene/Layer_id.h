#pragma once

enum class LAYER
{		
	BG,											// 背景
	CHIP,
	CHAR,										// キャラクター
	UI,											// UI
	NUMBER,
	LETTER,
	PUTTOM,										// パタン
	EX,											// 一番前用
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER& key);
LAYER operator++(LAYER& key);
