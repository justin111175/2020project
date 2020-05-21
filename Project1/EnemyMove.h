#pragma once
#include "Obj.h"
#include <Vector2.h>
#include <vector>

//enum class MOVE_TYPE
//{
//	WAIT,			// �ړ���~
//	SIGMOID,		// �V�O���C�h�ړ�
//	SPIRAL,			// �X�p�C�����ړ�
//	PITIN,			// �w�肵���Ƃ���֍s���ړ�
//	LR,				// ���E�ړ�
//	EXPAND,			// �g��k��
//	ATTACK			// �U��
//};


//�ړ���ށA�S�[���n�_
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2Dbl>>;

class EnemyMove :
	public Obj
{
public:
	EnemyMove(Vector2Dbl& pos, double& rad, Vector2Dbl& size, MOVE_TYPE& _movetype);
	~EnemyMove();

	bool SetMoveState(MoveState& state, bool newFlag);	// �ړ���ސݒ�F�V�����ړ�������ΌÂ��ړ�������
	void Update(sharedObj plObj) override;				// �X�V
private:
	void SetMovePrg(void);								// �Z�b�g���[�u�v���O����
	void (EnemyMove::*_move)(void);						// ���[�u�p�֐��|�C���^

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
	Vector2Dbl& _size;										// �T�C�Y
	MOVE_TYPE& movetype;


	double & _rad;										// �p�x
	int cnt;											// �p�x�p�v�Z
	int _limit;											// LR�ړ��̈ړ��ʐ���
};
