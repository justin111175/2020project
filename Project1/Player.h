#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>

#define PLSPEED 4												// �v���C���[�̍ő�l�X�s�[�h�i���E�j

class Player :
	public Obj
{	
public:
	Player();
	Player(Vector2Dbl pos, Vector2 size);
	void Update(void) override;									// �X�V
	~Player();

private:
	bool SetAlive(bool alive);
	int _treadCnt;												
	ACT playerAct;												// �v���C���[�̓���

	void PlayerMove(void);										// �v���C���[�̈ړ�
	void Init(void);											// ������
};

