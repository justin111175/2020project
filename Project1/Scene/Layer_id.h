#pragma once

enum class LAYER
{		
	BG,											// �w�i
	CHAR,										// �L�����N�^�[
	UI,											// UI
	PUTTOM,										// �p�^��
	EX,											// ��ԑO�p
	MAX
};

LAYER begin(LAYER);
LAYER end(LAYER);
LAYER operator*(LAYER& key);
LAYER operator++(LAYER& key);