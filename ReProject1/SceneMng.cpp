#include "SceneMng.h"
#include <Dxlib.h>
#include "GameScene.h"
#include "common/TimeCount.h"

SceneMng* SceneMng::sInstance = nullptr;



bool SceneMng::Run(void)
{
	if (!SysInit())
	{
		return false;
	}

	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{
		// clear�F�S�Ă̗v�f���폜����

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// move�̓R�s�[���܂���A���L����n������

		//Draw();




		_frames++;
		_timeCount.Run();
	}


	return true;
}

const int SceneMng::frames(void) const
{
    return _frames;
}



SceneMng::SceneMng():
    ScreenSize{ 1280,800 }
{
    _blendCnt = 0;
    _frames = 0;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetWindowText("����ꂽ�s �A�g�����e�B�X");		// �^�C�g���o�[
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:�t���X�N���[��
	if (DxLib_Init() == -1)												// DX�����u�����̏�����
	{
		return false;
	}





	// ���C���[�̐ݒ�
	//_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::MEAN, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::NUMBER, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	//_screenID.try_emplace(LAYER::LETTER, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	//_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	return true;
}


void SceneMng::Draw(void)
{
}