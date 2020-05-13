#pragma once
#include <common\Vector2.h>
#include <vector>
#include <memory>
#include "BaseScene.h"
#include <tuple>										//�v�f���O�ȏ���Ǘ����鎞���g��
#include "Layer_id.h"
#include <map>

enum class DRAW_QUE
{
	IMAGE,										// �C���[�W
	X,											// ���WX
	Y,											// ���WY
	SIZE_X,										// �T�C�YX
	SIZE_Y,										// �T�C�YY
	RAD,										// �p�x
	ZODER,										// Z�I�[�_�[�i���C���[�̑O�㏇��-���l�̒Ⴂ�������j
	LAYER,										// ���C���[ID�i���l�̒Ⴂ�������j
};

//enum TRG
//{
//	TRG_NOW,									// ����
//	TRG_OLD,									// �P�t���[���O
//	TRG_MAX
//};

//struct Key										// �L�[���Z�b�g
//{
//	bool up[TRG_MAX];
//	bool right[TRG_MAX];
//	bool down[TRG_MAX];
//	bool left[TRG_MAX];
//	bool Y[TRG_MAX];
//	bool B[TRG_MAX];
//	bool A[TRG_MAX];
//	bool X[TRG_MAX];
//};

class Obj;

using DrawQueT = std::tuple<int, double, double, int,int, double, int, LAYER>;

// �f�t�@�C��
#define IpSceneMng SceneMng::GetInstance()

//#define _mapPos SceneMng::GetInstance().MapPos
//#define _mapSize SceneMng::GetInstance().MapSize
//#define _Input SceneMng::GetInstance()._input


class SceneMng
{
public:
	// ���I�V���O���g��
	static SceneMng &GetInstance(void)							// �Q�b�g-�C���X�^���X
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
	void Run(void);


	bool AddDrawQue(DrawQueT dQue);								// �`��𑝉�����
	bool AddActQue(ActQueT aQue);								// �����𑝉�����

	const Vector2 ScreenSize;									// �S��ʃT�C�Y
	const Vector2 GameScreenSize;								// �S��ʃT�C�Y��4���̂P


	int _blendCnt;												// �u�����h�p�J���g

	const int frames(void)const;								// �t���[�����̃Q�b�g�֐�

private:
	static SceneMng* sInstance;									// �C���X�^���X
	// �X�}�[�g�|�C���^
	unique_Base _activeScene;									// ��Scene�̈ʒu

	void Draw(void);											// �`��
	int _frames;												// �t���[����
	int _layerGID;												// ���C���[ID

	std::map<LAYER, int> _screenID;								// 
	std::vector<DrawQueT> _drawList;							// �`�惊�X�g
	std::vector<ActQueT> _actList;								// �������X�g

	~SceneMng();
	SceneMng();
	bool SysInit(void);											// �V�X�e��������
};



