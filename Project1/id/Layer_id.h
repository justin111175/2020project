#pragma once

enum class LAYER
{		
	BG,											// �w�i
	CHIP,										//�`�b�v�i���j
	CHAR,										// �L�����N�^�[
	UI,											// UI
	MEAN,										//���j���[
	NUMBER,										//����
	LETTER,										//����
	PUTTOM,										// �p�^��
	EX,											// ��ԑO�p
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER& key);
LAYER operator++(LAYER& key);