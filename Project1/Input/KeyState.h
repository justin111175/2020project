#pragma once
#include "InputState.h"
#include <vector>

class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void) override;
private:
	void RefKeyData(void);
	void SetKeyConfig(void);
	void (KeyState::*func)(void);				// �����o�[�֐��|�C���^:�����ƕԂ�l

	char _buf[256];								// �S���̃L�[���
	std::vector<int> _keyCon;					// INPUT�L�[���
	std::vector<int> _keyConDef;				// INPUT�L�[���̕ۑ�
	
	INPUT_ID _confID;							// �R���g���[����INPUT_ID���
	int modeKeyOld;								// �R���t�B�O���b�h�L�[�̃I���g
};

