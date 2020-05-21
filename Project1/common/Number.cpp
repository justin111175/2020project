#include "Number.h"
#include <ImageMng.h>
#include <SceneMng.h>

// ������
void Number::Init(void)
{
	IpImageMng.GetID("����1", "image/Number/Number1.png", { 27,30 }, { 10,1 });
	IpImageMng.GetID("����2", "image/Number/Number2.png", { 45,50 }, { 10,1 });
	numLen = 1;
}

// �`��
void Number::Draw(int pos_x, int pos_y, int score,bool size)
{
	// �����l1����
	numLen = 1;

	//�����`�F�b�N
	for (int i = 10; score >= i; i *= 10)
	{
		numLen++;
	}

	//�����`��
	if (size)
	{
		for (int i = 0; i < numLen; i++)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("����1")[score % 10], pos_x - 27 * i,pos_y ,0,0,0,0,LAYER::UI });
			score /= 10;
		}
	}
	else
	{
		for (int i = 0; i < numLen; i++)
		{
			IpSceneMng.AddDrawQue({ IMAGE_ID("����2")[score % 10], pos_x - 45 * i,pos_y ,0,0,0,0,LAYER::UI });
			score /= 10;
		}
	}


	// score�̒l�Ŏ��O�`�F�b�N
	if (score <= 0)
	{
		return;
	}

}