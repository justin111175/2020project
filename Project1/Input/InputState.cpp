#include "_debug/_DeBugConOut.h"
#include "InputState.h"
#include "Dxlib.h"

//�R���X�g���N�^�ŏ���������͈̂�Ԉ��S
//�ႦInit�̊֐������΁A�ق��̊֐����ɓǂމ\��������
InputState::InputState()
{
	// try_emplace:
	//		�����Ɠ����̃L�[�����v�f�����݂��Ȃ��ꍇ�A�R���e�i�ɐV�����v�f��}������B
	//		�v�f�͈�������R���e�i���ɒ��ڍ\�z����邽�߁A�\�z���ꂽ�I�u�W�F�N�g�̓R�s�[�����[�u������Ȃ��B
	
	// enum class�Ŕ͈�FOR���̂����FINPUT_ID.cpp��INPUT_ID.h
	for (auto id : INPUT_ID())
	{
		_state.try_emplace(id, KeyPair{ 0,1 });
	}
}

InputState::~InputState()
{
}

const KeyMap & InputState::state(void) const
{
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const
{
	// try��catch �� if else ���邢�́@switch�݂���
	// try�F		
	//		�G���[�����邩�ǂ����킩��Ȃ����ǂ���Ă݂�
	// catch�F		
	//		����try���āA�G���[������ꍇcatch�̕��������s����
	
	static KeyPair defData = { 0,0 };
	try
	{
		return _state.at(id);
	}
	catch (...)
	{
		AST();
		
		//return { 0,0 };
		return defData;
	}

	// at:
	//		�w�肵���L�[�����v�f���擾����B�v�f�����o���ۂɃL�[�̑��݃`�F�b�N������B
	// �L�[x�ɑΉ�����l��Ԃ��B�Ή�����v�f�����݂��Ȃ��Ƃ��́Aout_of_range��O�𓊂���B

	// out_of_range:
	//		���������e�͈͊O�ł��邱�Ƃ������B

	// operator[]:	
	//		�w�肵���L�[�����v�f���擾����B�Ή�����v�f�����݂��Ȃ��ꍇ�͐������ĕԂ��B
	// ���̏�Ԃɂ�const������̂ŁA�������ނ��Ƃ͂ł��Ȃ��B�܂�A�����ł��Ȃ��B�ł�����,at���g��

	// ����const������̂ŁA�������ނ��Ƃ͂ł��Ȃ��B
	// �K�C�h�s�ׂ��ł��Ȃ�
	// �Ȃ̂ŃG���[���o��
	// return _state[id];
}

// ����INPUT�L�[���̃Z�b�g�֐�
bool InputState::state(INPUT_ID id,int data)
{
	// �f�[�^�����݂��Ă���ꍇ�A�X�V����
	if (_state.find(id) != _state.end())
	{
		// �L�[���̏��
		_state[id].first = data;
		return true;
	}
	return false;
}

// �I���g��INPUT�L�[���̃Z�b�g�֐�
void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}

