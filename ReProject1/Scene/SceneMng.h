#pragma once
#include "BaseScene.h"
#include "..\id\Layer_id.h"
#include "..\common\Vector2.h"
#include <map>
#include <vector>
#include "GameScene.h"

enum class DRAW_QUE
{
	IMAGE,										// �C���[�W
	POS,										// ���W
	SIZE,										// �T�C�Y
	EXRATE,										// �g��k����
	RAD,										// �p�x
	TURN,
	ZODER,										// Z�I�[�_�[�i���C���[�̑O�㏇��-���l�̒Ⴂ�������j
	LAYER,										// ���C���[ID�i���l�̒Ⴂ�������j
};

enum class TEXT_QUE
{
	STRING,										// �C���[�W
	POS,										// ���W
	EXRATE,										// �g��k����
	SIZE,
	ZODER,										// Z�I�[�_�[�i���C���[�̑O�㏇��-���l�̒Ⴂ�������j
	LAYER										// ���C���[ID�i���l�̒Ⴂ�������j

};


class Obj;

using DrawQueT = std::tuple<int, Vector2, Vector2Dbl, Vector2Dbl, double, bool, int, LAYER>;

using TextQueT = std::tuple<const char*, Vector2, Vector2Dbl,int, int, LAYER>;

#define IpSceneMng SceneMng::GetInstance()


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



	bool AddDrawQue(DrawQueT dQue);								// �`��𑝉�����
	bool AddDrawQue(TextQueT tQue);								// �`��𑝉�����
	bool AddActQue(ActQueT aQue);								// �����𑝉�����

	std::pair<CHIP_TYPE, CHIP_TYPE> _chipNo;
	bool _changeFlag;

	Vector2Dbl mapPos;
	Vector2 mapSize;
	std::map<int, int> _mapNow;


	std::vector<int> _dataBase;
	std::vector<int*> _data;


	int _blendCnt;												// �u�����h�p�J���g
	const int frames(void)const;								// �t���[�����̃Q�b�g�֐�
	const Vector2 ScreenSize;									// �S��ʃT�C�Y

private:
	static SceneMng* sInstance;									// �C���X�^���X
	
	std::vector<DrawQueT> _drawList;							// �`�惊�X�g

	std::vector<TextQueT> _textList;							// �������X�g

	std::vector<ActQueT> _actList;								// �������X�g


	std::map<LAYER, int> _screenID;


	void Draw(void);											// �`��

	// �X�}�[�g�|�C���^
	unique_Base _activeScene;									// ��Scene�̈ʒu
	int _frames;												// �t���[����


	SceneMng();
	~SceneMng();
	
	bool SysInit(void);											// �V�X�e��������

};

