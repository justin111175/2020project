#pragma once
#include "Obj.h"
#include <memory>
#include <Vector2.h>
#include <InputState.h>
#include <Number.h>
#include <Letter.h>

#define BulletCost 30
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

private:

	bool SetAlive(bool alive);

	void PlayerState(void);
	void CameraUpdata(void);
	void PlayerMove(void);										// �v���C���[�̈ړ�
	void Init(void);											// ������
	void Save(void);
	void Read(void);

	void StatusData(void);
	void StatusInit(void);
	void StatusUpData(void);									//�X�e�[�^�X�X�V

	void Repel(bool& repel);
	ME_ST MeanState;											//���j���[�̏��

	Status_Up_ID statusupId;										//�X�e�[�^�X��ID
	void UIDraw(void);											//�Q�[����ʕ`��
	void MeanDraw(void);										//���j���[�`��

	bool meanFlag;												//���j���[�J�������ǂ����t���O
	bool LetterFlag;
	
	Number number;												//�����p
	Letter letter;												//�����p
	


	float HpRatio;
	float MpRatio;
	
};

