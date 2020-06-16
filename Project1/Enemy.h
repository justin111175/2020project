#pragma once
#include "Obj.h"
#include <EnemyMove.h>
#include "Player.h"

enum class ENEMY_TYPE		//�G�^�C�v
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
	EXRATE,					//�g��k����
	AIM,					// �ړ����
	MAX
};


// ��ށA���W�A�T�C�Y�A�g��k�����A�ړ����@
using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, Vector2Dbl,Vector2Dbl, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState& state);										// Enemy�I�[�o�[���[�h
	void Update(sharedObj plObj) override;							// �X�V
	~Enemy();
private:
	friend Player;
	EnemyMove _moveCtl{ _pos,_rad,_size,movetype };					// ���[�u�R���g���[���o���W�A�p�x�A�T�C�Y�A�ړ���ށp
	bool SetAlive(bool alive);										// �����Ă��邩�ǂ���
	void Init(void);												// ������
	ENEMY_TYPE _type;												// �G���
};
