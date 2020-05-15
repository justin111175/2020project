#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>

#define PLSPEED 4												// �v���C���[�̍ő�l�X�s�[�h�i���E�j

class Player :
	public Obj
{	
public:
	Player();
	Player(Vector2Dbl pos, Vector2 size);
	void Update(sharedObj plObj) override;									// �X�V
	~Player();

private:
	bool SetAlive(bool alive);
	int _treadCnt;												
	ACT playerAct;												// �v���C���[�̓���

	void PlayerMove(void);										// �v���C���[�̈ړ�
	void Init(void);											// ������
	std::shared_ptr<InputState>_input;				// ���߯Ă��ư��߲���錾


	int levelCnt;


	int level[10];
	int a[9];
	int HP;
};

