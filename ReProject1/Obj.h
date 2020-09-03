#pragma once
#include <string>
#include <vector>
#include "common/Vector2.h"
#include <map>
#include <memory>
#include "..\ReProject1\id\DIR_ID.h"
#include "id/Status_ID.h"
#define PI 3.1415926f
#define DEG (PI/180.0)

// ��ԊǗ�
enum class STATE
{	
	STAY,						// �~�܂�
	NORMAL,						// ����
	DETH,						// ����(���S)
	MAX
};

enum class UNIT_ID
{
	NON,						// �����Ȃ�
	PLAYER,						// �v���C���[
	ENEMY,						// �G
	PLaS,						// �v���C���[�ߋ����U��
	PLaB,						// �v���C���[�̒e
	EyB,
	�����蔻��,					// ��
	�`��,
	��,
	�X�E�B�b�`,
	�{�X,
	�h���S����,
	//LevelUp,						// ���x���A�b�v
	���j���[
};


struct DirBit
{
	unsigned int UP : 1;
	unsigned int RIGHT : 1;
	unsigned int DOWN : 1;
	unsigned int LEFT : 1;

};

union Permit_Data
{
	DirBit _bit;
	unsigned int _flag;
};

enum class EnemyMode
{
	�~�܂�,
	�v���C���[����,
	���R�ړ�,
	MAX
};
class Obj;
class Player;
class Floor;

using AnimVector = std::vector<std::pair<int, unsigned int>>;
using sharedObj = std::shared_ptr<Obj>;									// shared_ptr �������R�r�[�ł��܂�



class Obj
{
public:
	Obj();
	virtual void Update(sharedObj &plObj) = 0;								// �������z�֐�
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool stateDir(const STATE state, const DIR_ID dir);					// �Q�b�g�֐�-�ǂ̃A�j���V�������Đ����邩�w�肷��
	bool stateDir(const STATE state);									// �Q�b�g�֐�-�ǂ̃A�j���V�������Đ����邩�w�肷��

	virtual bool SetAlive(bool alive);									// �����Ă��邩�ǂ����ݒ�
	virtual bool SetRepel(bool repel);									//���ނ��邩�ǂ����Ǘ�

	bool SetAnim(const STATE state, AnimVector& data);					// �A�j���̐ݒ�
	bool SetAnim(const STATE state, const DIR_ID _dir, AnimVector& data);					// �A�j���̐ݒ�

	bool isAlive(void) { return _alive; }								// �����Ă���Ǘ�
	bool isDead(void) { return _dead; }									// ����ł���Ǘ�
	bool isAnimEnd(void);												// �A�j��������������ǂ���

	//�Q�b�g�֐�
	Vector2 Pos(void);											//���̍��W
	bool Pos(Vector2 pos);

	const STATE GetState(void);
	const double GetRad(void);
	bool SetRad(double rad);

	Vector2 posOldGet(void);											//�̂̍��W
	Vector2 sizeGet(void);											//�傫��
	DIR_ID DIR(void);
	bool DIR(DIR_ID dir);
	bool RunFlag(bool flag);

	UNIT_ID _unitID;													// ���j�b�gID

	std::map<int, int> _experience;
	std::map<Status_ID, int> _status;									//�X�e�[�^�X�p
	std::map<Status_ID, int> _statusOld;									//�X�e�[�^�X�p


	int BCnt;
	std::map < DIR_ID, bool> _dirFlag;									// true:�ړ��Afalse�F��~
	
	const DIR_ID GetDir(void);														

	Vector2 _speed;											//�ړ����x

	EnemyMode enemyMode_;
	Vector2 _funcPos;

	double funcRad_;
	double gekitaiFlag_;
	int _cnt;
	bool tateFlag_;
private:


	std::map <STATE, AnimVector> _animMap[static_cast<int>(DIR_ID::MAX)];								// �L�[�A�A�j���t���[��


	unsigned int _animFrame;											// �t���[��
	unsigned int _animCount;											// �A�j���J���g

protected:

	bool DestroyPrpc(void);												// �����A�j�����I��������ǂ����m�F�A�I�������A���ł���
	bool _alive;														// �A���C�u�[�������Ă��邩�O���t
	bool _dead;															// ���S�|������ł��邩�O���t
	double _rad;														// �p�x
	int _zorder;														// �`��D��x�p
	Vector2 _pos;														// ���̍��W

	Vector2 _posOld;													// �̂̍��W
	Vector2 _size;													// �T�C�Y
	Vector2Dbl _exrate;													// X��Y�̊g��k����
	DIR_ID _dir;														// ����

	Permit_Data _pData;
	bool _runFlag;

	bool _turnFlag;
	
	bool _repelFlag;//���ޗp
	STATE _state;														// ���

};

