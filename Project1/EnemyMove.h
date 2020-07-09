#pragma once
#include "Obj.h"
#include <Vector2.h>
#include <vector>


//�ړ���ށA�S�[���n�_
using MoveState = std::vector<std::pair<DIR_ID, Vector2Dbl>>;

class EnemyMove :
	public Obj
{
public:
	EnemyMove(Vector2Dbl& pos, double& rad, Vector2Dbl& size, DIR_ID& _movetype);
	~EnemyMove();

	bool SetMoveState(MoveState& state, bool newFlag);	// �ړ���ސݒ�F�V�����ړ�������ΌÂ��ړ�������
	void Update(void) override;				// �X�V
private:
	void SetMovePrg(void);								// �Z�b�g���[�u�v���O����
	void (EnemyMove::*_move)(void);						// ���[�u�p�֐��|�C���^

	// �ړ��p�֐�
	void MoveNormal(void);								
	void MoveUp(void);
	void MoveRight(void);
	void MoveLeft(void);
	void MoveDown(void);




	MoveState _aim;										// �ړ���ށA�S�[���n�_
	int _aimCnt;										// �ړ���ނ̌v�Z

	Vector2Dbl _startPos;								// �e�ړ��֐��̃X�^�[�g�n�_
	Vector2Dbl _endPos;									// �e�ړ��֐��̃G���h�n�_

	Vector2Dbl& _pos;									// �S�[���n�_
	Vector2Dbl& _size;									// �T�C�Y
	DIR_ID& movetype;								//�ړ��̃^�C�v


	double & _rad;										// �p�x
	int cnt;											// �p�x�p�v�Z
	int _limit;											// LR�ړ��̈ړ��ʐ���
};

