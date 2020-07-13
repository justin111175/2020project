#include "BaseScene.h"

BaseScene::BaseScene()
{
}

BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	actList.clear();

}

void BaseScene::FadeInit(std::string fadeType)
{
}

bool BaseScene::FadeUpdate(void)
{
	return false;
}
