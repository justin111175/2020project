#pragma once

struct Number
{
public:
	void Init(void);								// ������
	void Draw(int pos_x, int pos_y, int score, bool size);		// �`��
private:
	int numberImage[10];							// �����摜�̕ۑ��p
	int numLen;										// ����
};

