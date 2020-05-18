#include "KeyState.h"
#include <Dxlib.h>
#include "_debug\_DeBugConOut.h"
#include "InputState.h"

KeyState::KeyState()
{
	// ���reserve������A�����������ꂢ�Ɏg����
	// size_t:
	//		�I�u�W�F�N�g�̃o�C�g����\���ł�����x�ɏ\���ɑ傫�������Ȃ������^

	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));

	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_C);
	_keyConDef.emplace_back(KEY_INPUT_V);
	_keyConDef.emplace_back(KEY_INPUT_ESCAPE);



	FILE* file;
	fopen_s(&file, "data/key.dat", "rb");
	if (file==nullptr)
	{
		_keyCon = _keyConDef;
	}
	else
	{
		// resize�F�v�f����ύX����
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
		// �v�f�A�N�Z�X:operator[],data,�����������낢�날��
		// fread(&_keyCon[0], sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
		// �A���̃f�[�^�����ł��Ȃ�
		// fread(&_keyCon[0], sizeof(&_keyCon[0]),_keyCon.size(), file);
		fclose(file);
	}
		
	//_keyCon = _keyConDef;

	//// �f�[�^��ǂݍ���
	//FILE* file;
	//fopen_s(&file, "data/key.dat", "rb");
	//if (file != nullptr)
	//{
	//	fread(_keyCon.data(), sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
	//	fclose(file);
	//}

	modeKeyOld = 1;
	func = &KeyState::RefKeyData;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	SetOld();
	modeKeyOld = _buf[KEY_INPUT_F1];
	// �S�ẴL�[����_buf�ɓ���
	GetHitKeyStateAll(_buf);
	
	// �������g�̃|�C���^:func = &KeyState::RefKeyData; �Ō�RefKeyData�����s����
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// �͈�FOR���ŁAINPUT_ID�̏��ԂɃL�[�����Z�b�g����
	for(auto id: INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<size_t>(id)]]);
	}
	// ����F1�L�[�ƃI���gF1�L�[�̐ݒ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::LEFT;
		func = &KeyState::SetKeyConfig;
		TRACE("�L�[�R���t�B�O�J�n\n");
		// SetKeyConfig�̐擪�ɐݒ肷��Ȃ�A������o��̂ŁARefKeyData��mode��؂�ւ��鎞�ɐݒ肷��A�擪�Ɉ��o��
		TRACE("%d/%d�Ԗڂ̃L�[�ݒ�\n", static_cast<int>(_confID)+1,end(INPUT_ID()));
	}
}

void KeyState::SetKeyConfig(void)
{
	
	// ����F1�L�[�ƃI���gF1�L�[�̐ݒ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::RefKeyData;
		TRACE("�L�[�R���t�B�O�I��\n");
	}
	// �V����INPUT�L�[����ݒ肵�����̂ŁA0�ɂ���
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	// �L���v�`���F�R�s�[�A�Q�ƂQ����
	// �R�s�[�L���v�`���F[=]
	//			���S�����������ǁA��������H�����A�X�s�[�h���x��
	//			[=,&...]�P�ƂɎQ�Ƃ��邱�Ƃ��ł���
	// �Q�ƃL���v�`���F[&]
	//			�X�s�[�h���������A�l�����������邯�ǁA�f���[�g�\��������
	auto checkKey=[&](int id) {
		// 8�L�[�̏��̐擪����Ō�܂�
		for (auto ckID = INPUT_ID::LEFT; ckID < _confID; ++ckID)
		{
			if (_keyCon[static_cast<int>(ckID)] == id)
			{
				return false;
			}
		}
		return true;
	};

	// for (int id = 0; id < 256; id++)
	// 256���ړ��͂�����A�ύX�������ꍇ�͖ʓ|�Ȃ��ƂɂȂ�̂ŁA
	// sizeof���g����_buf�̗v�f�����Ƃ�
	for (int id = 0; id < sizeof(_buf); id++)
	{
		// �L�[ID�������̏ꍇ�Freturn false  ���̎���if���ɓ���
		// �L�[ID����������Ȃ��ꍇ�Freturn true  continue���ă��[�v�����̐擪�ɖ߂�܂�
		if (!checkKey(id))
		{
			// continue:
			//		���[�v�����̐擪�ɖ߂�܂�
			continue;
		}

		// F1�L�[�ȊO�̃L�[����������A���ɓ���
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			_keyCon[static_cast<int>(_confID)] = id;
			// �C�i���N���X��operator++�ɂ͑O���Z���K�v
			++_confID;
			TRACE("%d��ݒ�\n", id);

			// INPUT_ID end(INPUT_ID)�ɍs��
			// end(INPUT_ID::MAX)�`�͐������Ȃ�A������͂��Ă�����
			if (_confID == end(_confID))
			{
				// �f�[�^��ۑ�
				FILE* file;
				fopen_s(&file, "data/key.dat", "wb");
				if (file != nullptr)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0])*_keyCon.size(), 1, file);
					fclose(file);
				}

				TRACE("�L�[�R���t�B�O�I��\n");
				func = &KeyState::RefKeyData;
				break;
			}
			TRACE("%d/%d�Ԗڂ̂��[�ݒ�\n", static_cast<int>(_confID) + 1, end(INPUT_ID()));
		}
	}
}


