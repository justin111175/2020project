#pragma once

struct Number
{
public:
	void Init(void);								// 初期化
	void Draw(int pos_x, int pos_y, int score/*, bool size*/);		// 描画
private:
	int numberImage[10];							// 数字画像の保存用
	int numLen;										// 桁数
};

