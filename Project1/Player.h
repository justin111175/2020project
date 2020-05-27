#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>
#include <Number.h>
#include <Letter.h>
#define PLSPEED 4												// �v���C���[�̍ő�l�X�s�[�h�i���E�j

enum MEAN_ID
{
	�X�e�[�^�X,
	����,
	�ۑ�,
	�I�v�V����,
	�Q�[���I��
};

enum ME_ST
{
	MEAN_OUT,
	MEAN_IN,

};



class Player :
	public Obj
{	
public:
	Player();
	Player(Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate);
	void Update(sharedObj plObj) override;									// �X�V
	~Player();

private:
	bool SetAlive(bool alive);
	int _treadCnt;												
	ACT playerAct;												// �v���C���[�̓���

	void PlayerMove(void);										// �v���C���[�̈ړ�
	void Init(void);											// ������
	std::shared_ptr<InputState>_input;							// ���߯Ă��ư��߲���錾

	MEAN_ID meanId;
	ME_ST MeanState;

	STATUS_UP statusupId;
	void MeanDraw(void);
	void StatusUpdate(void);
	bool meanFlag;
	bool LetterFlag;
	
	Number number;
	Letter letter;


};

