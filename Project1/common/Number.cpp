#include "Number.h"
#include <ImageMng.h>
#include <SceneMng.h>

// 初期化
void Number::Init(void)
{
	IpImageMng.GetID("数字1", "image/Number/Number1.png", { 27,30 }, { 10,1 });
	IpImageMng.GetID("数字2", "image/Number/Number2.png", { 45,50 }, { 10,1 });
	numLen = 1;
}

// 描画
void Number::Draw(int pos_x, int pos_y, int score,bool size)
{
	// 初期値1桁目
	numLen = 1;

	//桁数チェック
	for (int i = 10; score >= i; i *= 10)
	{
		numLen++;
	}

	//数字描画
	if (size)
	{
		for (int i = 0; i < numLen; i++)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("数字1")[score % 10], pos_x - 27 * i,pos_y ,0,0,0,0,LAYER::NUMBER });
			score /= 10;
		}
	}
	else
	{
		for (int i = 0; i < numLen; i++)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("数字2")[score % 10], pos_x - 45 * i,pos_y ,0,0,0,0,LAYER::NUMBER });
			score /= 10;
		}
	}


	// scoreの値で事前チェック
	if (score <= 0)
	{
		return;
	}

}