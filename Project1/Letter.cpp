#include "Letter.h"
#include <ImageMng.h>
#include <SceneMng.h>



void Letter::LetterDraw(void)
{

	IpSceneMng.AddDrawQue({ IMAGE_ID("•¶Žš")[0], 0,0,0,0,0,0,LAYER::UI});


}

void Letter::Init(void)
{

	//AnimVector data;
	//data.reserve(1);
	//data.emplace_back(IMAGE_ID("•¶Žš")[0], 30);
	//SetAnim(STATE::NORMAL, data);



}



