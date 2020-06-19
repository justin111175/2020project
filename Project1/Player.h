#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>
#include <Number.h>
#include <Letter.h>

#define PLSPEED 4												// �v���C���[�̍ő�l�X�s�[�h�i���E�j

enum MEAN_ID													//���j���[��ID
{
	�X�e�[�^�X,
	����,
	�ۑ�,
	�I�v�V����,
	�Q�[���I��
};

enum class ME_ST												//���j���[�̏��	
{
	MEAN_OUT,													// ���j���[�̊O
	MEAN_IN,													// ���j���[�̒�

};


class Player :
	public Obj
{	
public:
	Player();													//�R���X�g���N�^
	Player(Vector2Dbl pos, Vector2Dbl size, Vector2Dbl exrate);
	void Update(sharedObj plObj) override;									// �X�V
	~Player();													//�f�X�g���N�^
	//Level _level;														//���x��


private:
	bool SetAlive(bool alive);

	void PlayerMove(void);										// �v���C���[�̈ړ�
	void Init(void);											// ������
	void Save(void);
	void Read(void);

	void StatusInit(void);
	void StatusUpdate(void);									//�X�e�[�^�X�X�V

	ME_ST MeanState;											//���j���[�̏��

	STATUS_UP statusupId;										//�X�e�[�^�X��ID
	void UIDraw(void);											//�Q�[����ʕ`��
	void MeanDraw(void);										//���j���[�`��

	bool meanFlag;												//���j���[�J�������ǂ����t���O
	bool LetterFlag;
	
	Number number;												//�����p
	Letter letter;												//�����p
	int Bmax;													//�e�̍ő�l
	
	Vector2Dbl speed;											//�ړ����x


	double HpRatio;
	double MpRatio;
};

