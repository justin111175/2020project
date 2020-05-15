#pragma once
#include <string>
#include <vector>
#include <Vector2.h>
#include <map>
#include <memory>
#include <level.h>


enum class MOVE_TYPE
{
	DOWN,
	LEFT,						// ��
	RIGHT,						// �E
	UP,
};

// ��ԊǗ�
enum class STATE
{	
	DOWN,
	LEFT,						// ��
	RIGHT,						// �E
	UP,
	
	STAY,						// �~�܂�
	NORMAL,
	DETH,						// ����(���S)
	MAX
};




enum class UNIT_ID
{
	NON,						// �����Ȃ�
	PLAYER,						// �v���C���[
	ENEMY,						// �G
	PLaS,						// �v���C���[�ߋ����U��
	PLaB
};

enum class ACT
{
	STAY,						// �~�܂�
	RIGHT,						// �E
	LEFT,						// ��
	MAX
};

class Obj;
class Player;
class Enemy;
class iteam;
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

	bool state(const STATE state);										// �Q�b�g�֐�-�ǂ̃A�j���V�������Đ����邩�w�肷��
	UNIT_ID _unitID;													// ���j�b�gID
	MOVE_TYPE movetype;
	virtual bool SetAlive(bool alive);									// �����Ă��邩�ǂ����ݒ�

	bool SetAnim(const STATE state,AnimVector& data);					// �A�j���̐ݒ�
	bool isAlive(void) { return _alive; }								// �����Ă���Ǘ�
	bool isDead(void) { return _dead; }									// ����ł���Ǘ�
	bool isAnimEnd(void);												// �A�j��������������ǂ���
	Vector2Dbl _pos;													// ���W
	Vector2Dbl _posOld;
	Vector2 _size;														// �T�C�Y
	level _level;

private:

	std::map <STATE, AnimVector> _animMap;								// �L�[�A�A�j���t���[��
	STATE _state;														// ���
	unsigned int _animFrame;											// �t���[��
	unsigned int _animCount;											// �A�j���J���g

protected:

	bool DestroyPrpc(void);												// �����A�j�����I��������ǂ����m�F�A�I�������A���ł���
	bool _alive;														// �A���C�u�[�������Ă��邩�O���t
	bool _dead;															// ���S�|������ł��邩�O���t
	double _rad;														// �p�x
	int _zorder;														// �`��D��x�p
};