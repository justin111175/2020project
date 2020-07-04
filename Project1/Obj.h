#pragma once
#include <string>
#include <vector>
#include <Vector2.h>
#include <map>
#include <memory>
#include "DIR_ID.h"
#include "Status_ID.h"
#include "Status_Up_ID.h"


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
	FLOOR,						// ��
	LevelUp						// ���x���A�b�v
};





class Obj;
class Player;
class Enemy;
class Floor;
using AnimVector = std::vector<std::pair<int, unsigned int>>;
//shared_ptr�F		�w�肳�ꂽ���\�[�X�ւ̏��L��(ownership)�����L(share)����X�}�[�g�|�C���^�ł���B
using sharedObj = std::shared_ptr<Obj>;									// shared_ptr �������R�r�[�ł��܂�

class Obj
{
public:
	Obj();
	virtual void Update(sharedObj plObj)=0;								// �������z�֐�
	void Draw(void);
	void Draw(int id);
	virtual ~Obj();

	bool stateDir(const STATE state,const DIR_ID dir);										// �Q�b�g�֐�-�ǂ̃A�j���V�������Đ����邩�w�肷��
	bool stateDir(const STATE state);										// �Q�b�g�֐�-�ǂ̃A�j���V�������Đ����邩�w�肷��

	UNIT_ID _unitID;													// ���j�b�gID
	virtual bool SetAlive(bool alive);									// �����Ă��邩�ǂ����ݒ�
	virtual bool SetRepel(bool repel);						//���ނ��邩�ǂ����Ǘ�

	bool SetAnim(const STATE state, AnimVector& data);					// �A�j���̐ݒ�
	bool SetAnim(const STATE state, const DIR_ID _dir, AnimVector& data);					// �A�j���̐ݒ�

	bool isAlive(void) { return _alive; }								// �����Ă���Ǘ�
	bool isDead(void) { return _dead; }									// ����ł���Ǘ�
	bool isAnimEnd(void);												// �A�j��������������ǂ���
	const Vector2Dbl funcPos(Vector2Dbl pos);
	const DIR_ID funcDir(DIR_ID dir);

	//�Q�b�g�֐�
	Vector2Dbl posGet(void);											//���̍��W
	Vector2Dbl posOldGet(void);											//�̂̍��W
	Vector2Dbl sizeGet(void);											//�傫��
	
	const DIR_ID dirGet(void)const;
	const bool repelFlagGet(void)const;
	
	
	std::map<Status_ID, int> _status;									//�X�e�[�^�X�p
	std::map<Status_Up_ID, int> _statusUp;								//�X�e�[�^�X�����p
	std::map<int, int> _experience;
	
	std::map < DIR_ID, bool> _dirFlag;									// true:�ړ��Afalse�F��~
	int _level;															//���x��
	
	Vector2Dbl speed;											//�ړ����x


private:


	std::map <STATE, AnimVector> _animMap[static_cast<int>(DIR_ID::MAX)];								// �L�[�A�A�j���t���[��

	STATE _state;														// ���

	unsigned int _animFrame;											// �t���[��
	unsigned int _animCount;											// �A�j���J���g

protected:

	bool DestroyPrpc(void);												// �����A�j�����I��������ǂ����m�F�A�I�������A���ł���
	bool _alive;														// �A���C�u�[�������Ă��邩�O���t
	bool _dead;															// ���S�|������ł��邩�O���t
	double _rad;														// �p�x
	int _zorder;														// �`��D��x�p
	Vector2Dbl _pos;													// ���̍��W

	Vector2Dbl _posOld;													// �̂̍��W
	Vector2Dbl _size;													// �T�C�Y
	Vector2Dbl _exrate;													// X��Y�̊g��k����
	DIR_ID _dir;														// ����
	bool _turnFlag;
	bool _repelFlag;//���ޗp
	
	Vector2Dbl _funcPos;
	DIR_ID _funcDir;

};

