#include "Number.h"
#include "ImageMng.h"
#include "..\SceneMng.h"
// ������
void Number::Init(void)
{
	IpImageMng.GetID("����1", "image/Number/Number2.png", { 90,100 }, { 10,1 });
	numLen = 1;
}

// �`��
void Number::Draw(Vector2Dbl pos,Vector2Dbl exrate, int score)
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
		//IpSceneMng.AddDrawQue({ IMAGE_ID("����1")[score % 10], {pos.x - 90 * exrate.x * i,pos.y} ,{0,0},{exrate.x,exrate.y},0,false,0,LAYER::NUMBER });

		score /= 10;
	}

	// score�̒l�Ŏ��O�`�F�b�N
	if (score <= 0)
	{
		return;
	}

}