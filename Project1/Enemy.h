#pragma once
#include "Obj.h"

enum class ENEMY_TYPE
{
	�R�E����,
	�X���C��,
	�I�[�N,
	�~�m�^�E���X,
	������,
	�X�J���}��,
	�S�[�X�g,
	����,
	MAX
};


// �@�\�Ǘ�
enum class ENEMY_STATE
{
	TYPE,					// ���
	VECTOR,					// ���W
	SIZE,					// �傫��
	MAX
};


// ��ށA���W�A�T�C�Y�A�ړ����@
using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, Vector2>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);										// Enemy�I�[�o�[���[�h
	void Update(sharedObj plObj) override;							// �X�V
	~Enemy();
private:
	bool SetAlive(bool alive);										// �����Ă��邩�ǂ���
	ACT act;														// �ړ����
	void Init(void);												// ������
	ENEMY_TYPE _type;												// �G���
};