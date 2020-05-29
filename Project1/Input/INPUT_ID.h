#pragma once

// インプットID
// enum class の後ろに型を設定することができる
enum class INPUT_ID		//INPUT_ID:int
{
	LEFT,				// 左
	RIGHT,				// 右
	UP,					// 上
	DOWN,				// 下
	BTN_1,				// ボタン１
	BTN_2,				// ボタン２
	BTN_3,				// ボタン３
	BTN_4,				// ボタン４
	P,
	ESC,
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID& key);
INPUT_ID operator++(INPUT_ID& key);
