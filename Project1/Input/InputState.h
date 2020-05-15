#pragma once
#include <map>
#include "INPUT_ID.h"


using KeyPair = std::pair<int, int>;				// �L�[���̏��A�I���g���
using KeyMap = std::map<INPUT_ID, KeyPair>;			// �C���v�b�gID�A�i�L�[���̏��A�I���g�̏��j

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update(void) =0;

	const KeyMap& state(void)const;					// �Q�b�g�֐�
	const KeyPair& state(INPUT_ID id)const;
	bool state(INPUT_ID id, int data);				// ����INPUT�L�[���̃Z�b�g�֐�
	void SetOld(void);								// �I���g��INPUT�L�[���̃Z�b�g�֐�
private:
	KeyMap _state;
};

