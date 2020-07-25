#include "Number.h"
#include "ImageMng.h"
#include "..\Scene\SceneMng.h"

// 初期化
void Number::Init(void)
{
	IpImageMng.GetID("数字0", "image/Number/number.png", { 90,100 }, { 10,1 });
	IpImageMng.GetID("数字1", "image/Number/number1.png", { 90,100 }, { 10,1 });
	numLen = 1;
}

// 描画
void Number::Draw(Vector2 pos,Vector2Dbl exrate, int score,int no)
{
	// 初期値1桁目
	numLen = 1;

	//桁数チェック
	for (int i = 10; score >= i; i *= 10)
	{
		numLen++;
	}

	//数字描画
	for (int i = 0; i < numLen; i++)
	{
		auto Pos = Vector2(pos.x - 90 * exrate.x * i, pos.y);
		if (no == 0)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("数字0")[score % 10], Pos ,{0,0},{exrate.x,exrate.y},0,false,0,LAYER::NUMBER });

		}
		else
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("数字1")[score % 10], Pos ,{0,0},{exrate.x,exrate.y},0,false,0,LAYER::NUMBER });

		}

		score /= 10;
	}

	// scoreの値で事前チェック
	if (score <= 0)
	{
		return;
	}

}