#pragma once
#include <common\Vector2.h>
#include <vector>
#include <memory>
#include "BaseScene.h"
#include <tuple>										//�v�f���O�ȏ���Ǘ����鎞���g��
#include "Layer_id.h"
#include <map>
#include <InputState.h>
#include <level.h>
#include <Select.h>


enum class DRAW_QUE
{
	IMAGE,										// �C���[�W
	X,											// ���WX
	Y,											// ���WY
	SIZE_X,										// �T�C�YX
	SIZE_Y,										// �T�C�YY
	EXRATE_X,
	EXRATE_Y,
	RAD,										// �p�x
	ZODER,										// Z�I�[�_�[�i���C���[�̑O�㏇��-���l�̒Ⴂ�������j
	LAYER,										// ���C���[ID�i���l�̒Ⴂ�������j
};


class Obj;

using DrawQueT = std::tuple<int, double, double, int,int,double,double, double, int, LAYER>;

// �f�t�@�C��
#define IpSceneMng SceneMng::GetInstance()

//#define _mapPos SceneMng::GetInstance().MapPos
//#define _mapSize SceneMng::GetInstance().MapSize
#define _Input SceneMng::GetInstance()._input

#define _select SceneMng::GetInstance().select



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
	
	int mapNow[50][50];


	bool AddDrawQue(DrawQueT dQue);								// �`��𑝉�����
	bool AddActQue(ActQueT aQue);								// �����𑝉�����

	const Vector2 ScreenSize;									// �S��ʃT�C�Y
	const Vector2 GameScreenSize;								// �S��ʃT�C�Y��4���̂P
	
	std::shared_ptr<InputState> _input;							// �V�F�A�|�C���^-�L�[���

	Select select;

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



