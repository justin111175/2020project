#pragma once
#include "Obj.h"
#include"common/Vector2.h"
#include <vector>

enum class MOVE_TYPE
{
	Normal,
	Stay,
	RetPos,
	Act1,
	Boss,
	MAX
};

//�ړ���ށA�S�[���n�_
using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2>>;

class EnemyMove :
	public Obj
{
public:
	EnemyMove(Vector2& pos, double& rad, Vector2& size, DIR_ID& dir, bool& runFlag);
	~EnemyMove();

	bool SetMoveState(MoveState& state, bool newFlag);	// �ړ���ސݒ�F�V�����ړ�������ΌÂ��ړ�������
	void Update(sharedObj& plObj) override;				// �X�V

	bool actFlag;
private:
	sharedObj plObj_;
	
	void SetMovePrg(void);								// �Z�b�g���[�u�v���O����
	void (EnemyMove::*_move)(void);						// ���[�u�p�֐��|�C���^

	// �ړ��p�֐�
	void Normal(void);								
	void Saty(void);								
	void RetPos(void);
	void Actack1(void);
	void BossMove(void);



	MoveState _aim;										// �ړ���ށA�S�[���n�_
	int _aimCnt;										// �ړ���ނ̌v�Z

	Vector2 _startPos;								// �e�ړ��֐��̃X�^�[�g�n�_
	Vector2 _endPos;									// �e�ړ��֐��̃G���h�n�_

	Vector2& _pos;									// �S�[���n�_
	Vector2& _size;									// �T�C�Y
	DIR_ID& _dir;								//�ړ��̃^�C�v
	
	bool& _runFlag;

	double & _rad;										// �p�x
	int cnt;											// �p�x�p�v�Z
	int _limit;											// LR�ړ��̈ړ��ʐ���
};

