#include "Number.h"
#include "ImageMng.h"
#include "..\Scene\SceneMng.h"

// ������
void Number::Init(void)
{
	IpImageMng.GetID("����0", "image/Number/number.png", { 90,100 }, { 10,1 });
	IpImageMng.GetID("����1", "image/Number/number1.png", { 90,100 }, { 10,1 });
	numLen = 1;
}

// �`��
void Number::Draw(Vector2 pos,Vector2Dbl exrate, int score,int no)
{
	// �����l1����
	numLen = 1;

	//�����`�F�b�N
	for (int i = 10; score >= i; i *= 10)
	{
		numLen++;
	}

	//�����`��
	for (int i = 0; i < numLen; i++)
	{
		auto Pos = Vector2(pos.x - 90 * exrate.x * i, pos.y);
		if (no == 0)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("����0")[score % 10], Pos ,{0,0},{exrate.x,exrate.y},0,false,0,LAYER::NUMBER });

		}
		else
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("����1")[score % 10], Pos ,{0,0},{exrate.x,exrate.y},0,false,0,LAYER::NUMBER });

		}

		score /= 10;
	}

	// score�̒l�Ŏ��O�`�F�b�N
	if (score <= 0)
	{
		return;
	}

}