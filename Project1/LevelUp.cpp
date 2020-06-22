#include "LevelUp.h"
#include <ImageMng.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>

LevelUp::LevelUp()
{

	Init();

}

LevelUp::LevelUp(UNIT_ID unitID, Vector2Dbl pos,Vector2Dbl size)
{
	_exrate = { 1.0f,1.0f };
	_size = { 250,150 };
	_unitID = unitID;

	//�v���C���[�̂̓��̏�
	_pos.x = pos.x-_size.x/2+size.x/2;
	_pos.y = pos.y-_size.y+20;

	// ���x���A�b�v�����v���C���[�̈ʒu���Ƃ�
	_posOld = _pos;

	Init();

}

LevelUp::~LevelUp()
{
}
//���x���A�b�v�摜�̏�����
void LevelUp::Init(void)
{
	_unitID = UNIT_ID::LevelUp;
	_alive = true;

	AnimVector data;
	data.reserve(1);
	
	for (int i = 0; i < 8; i++)
	{
		data.emplace_back(IMAGE_ID("UP1")[i], i*5);
	}
	data.emplace_back(-1, 40);

	SetAnim(STATE::NORMAL, data);

	data.emplace_back(-1, 40);
	SetAnim(STATE::DETH, data);

	stateDir(STATE::NORMAL,DIR_ID::DOWN);
}

void LevelUp::Update(sharedObj plObj)
{

	//TRACE("E:%d\n", Player::_level._statusUp[STATUS_UP::�c��{�[�i�X�|�C���g]);

	//�����m�F
	DestroyPrpc();
	//���x���A�b�v���āA�A�j�����I����ĂȂ��A�����ăv���C���[�̈ʒu���ύX�����ꍇ�̕␳
	if ((*plObj).posGet() != (*plObj).posOldGet())
	{
		_pos = (*plObj).posGet() - (*plObj).posOldGet() + _posOld;

	}


}

bool LevelUp::SetAlive(bool alive)
{
	if (!alive)
	{
		// ��ʗh�炵��QUE�𓊂���
		//IpSceneMng.AddActQue({ ACT_QUE::SHAKE, *this });
	}

	return Obj::SetAlive(alive);
}

bool LevelUp::DestroyPrpc(void)
{
	if (Obj::DestroyPrpc())
	{
		return true;
	}

	return false;
}
