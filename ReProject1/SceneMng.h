#pragma once
#include "BaseScene.h"


class SceneMng
{
public:
	// ���I�V���O���g��
	static SceneMng& GetInstance(void)							// �Q�b�g-�C���X�^���X
	{
		Create();
		return *sInstance;
	}
	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SceneMng();
		}
	}
	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}
	
	bool Run(void);





	int _blendCnt;												// �u�����h�p�J���g
	const int frames(void)const;								// �t���[�����̃Q�b�g�֐�
	const Vector2 ScreenSize;									// �S��ʃT�C�Y

private:
	static SceneMng* sInstance;									// �C���X�^���X
	
	void Draw(void);											// �`��
															// �X�}�[�g�|�C���^
	unique_Base _activeScene;									// ��Scene�̈ʒu
	int _frames;												// �t���[����


	SceneMng();
	~SceneMng();
	
	bool SysInit(void);											// �V�X�e��������

};

