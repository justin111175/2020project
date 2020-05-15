#pragma once

// �C���v�b�gID
// enum class �̌��Ɍ^��ݒ肷�邱�Ƃ��ł���
enum class INPUT_ID		//INPUT_ID:int
{
	LEFT,				// ��
	RIGHT,				// �E
	UP,					// ��
	DOWN,				// ��
	BTN_1,				// �{�^���P
	BTN_2,				// �{�^���Q
	BTN_3,				// �{�^���R
	BTN_4,				// �{�^���S
	MAX
};

INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator*(INPUT_ID& key);
INPUT_ID operator++(INPUT_ID& key);
