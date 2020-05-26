#include "BaseScene.h"
#include "SceneMng.h"
#include "ImageMng.h"
#include "DxLib.h"

BaseScene::BaseScene()
{
	IpImageMng.GetID("black", "image/black.png");							//�g:�킭- ���̗֊s��͈�
	IpImageMng.GetID("white", "image/white.png");							
	_fadeScrID = MakeScreen(IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, false);
	FadeInit("white");
}

BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	actList.clear();
}

// Fade������
void BaseScene::FadeInit(std::string fadeType)
{

	GetDrawScreenGraph(0, 0, IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, _fadeScrID);
	IpSceneMng._blendCnt = 250;
	_fadeType = fadeType;

}

// Fade�X�V
bool BaseScene::FadeUpdate(void)
{
	if (IpSceneMng._blendCnt)
	{		
		IpSceneMng.AddDrawQue({ IpImageMng.GetID(_fadeType)[0], IpSceneMng.ScreenSize.x / 2, IpSceneMng.ScreenSize.y / 2,0,0 ,0,0,0, 3, LAYER::EX});
		IpSceneMng._blendCnt -=5;
	}

	return IpSceneMng._blendCnt;
}

