#include "SceneMng.h"
#include <Dxlib.h>
#include <algorithm>
#include <tuple>										//�v�f���O�ȏ���Ǘ����鎞���g��
#include "..\common\_debug\_DebugDispOut.h"
#include "..\common\_debug\_DeBugConOut.h"
#include "..\common\TimeCount.h"

SceneMng* SceneMng::sInstance = nullptr;



bool SceneMng::Run(void)
{
	if (!SysInit())
	{
		return false;
	}

	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{		

		// clear�F�S�Ă̗v�f���폜����
		_drawList.clear();
		_textList.clear();

		_dbgStartDraw();

		(*_activeScene).RunActQue(std::move(_actList));

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// move�̓R�s�[���܂���A���L����n������


		Draw();


		_timeCount.Run();
		_frames++;
	}


	return true;
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	//static_cast<int>�@��int�^�ɂȂ�
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		//�摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}
	//Que��ǉ�����
	//_drawList.push_back()

	//emplace_back�͎��������R���e�i�̗v�f�^�ƈقȂ�Ƃ��ɁApush_back�������삪�����Ȃ�A
	//����ȊO�̏ꍇ�ł͂قƂ�Ǖς��܂���B�i���������P�ɕϐ��̂Ƃ��Ȃǁj

	//emplace_back�F	���ڍ\�z�ŐV���ȗv�f�𖖔��ɒǉ�����
	//�Ċm�ۂ̉\���A�C�e���[�^�̗L�����ւ̉e���A��O�������ɕ���p���������Ȃ��ۏ؂͂������push_back()�Ɠ��l
	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::AddDrawQue(TextQueT tQue)
{
	if (std::get<static_cast<int>(TEXT_QUE::STRING)>(tQue) <= 0)
	{
		//�摜ID���s���Ȃ̂ŁA�ǉ����Ȃ�
		return false;
	}

	_textList.emplace_back(tQue);
	return true;
}

bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;

}

const int SceneMng::frames(void) const
{
    return _frames;
}



SceneMng::SceneMng():
    ScreenSize{ 800,600 }
{
    _blendCnt = 0;
    _frames = 0;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetWindowText("����ꂽ�s �A�g�����e�B�X");		// �^�C�g���o�[
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:�t���X�N���[��
	if (DxLib_Init() == -1)												// DX�����u�����̏�����
	{
		return false;
	}


	_chipNo.first = CHIP_TYPE::�n�}1;
	_chipNo.second = _chipNo.first;
	_changeFlag = false;
	
	_dbgSetup(215);														// debug�p�F�̓����x

	// ���C���[�̐ݒ�
	_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::MEAN, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::NUMBER, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::LETTER, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	return true;
}


void SceneMng::Draw(void)
{

	_dbgAddDraw();
	//ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);


	std::sort(_drawList.begin(), _drawList.end(), [](DrawQueT dQueA, DrawQueT dQueB) {

		return	std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZODER)>(dQueA))
			<
			std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZODER)>(dQueB));
	});


	for (auto layer : LAYER())
	{
		SetDrawScreen(_screenID[layer]);
		ClsDrawScreen();
	}

	// �X�^�b�N�ɂ��܂��Ă���Que��`�悷��
	// std�̃x�N�^�[�𒲂ׂĉ��:�͈�FOR
	for (auto dQue : _drawList)
	{

		double rad;
		int id;
		Vector2 pos;
		Vector2Dbl size;
		Vector2Dbl ExRate;
		LAYER layer_id;
		bool turnFlag;
		// ����Ȃ����Ƃ��΂�
		// tie:��������o�̓X�g���[���I�u�W�F�N�g���擾�E�ݒ肷��
		std::tie(id, pos, size, ExRate, rad, turnFlag, std::ignore, layer_id) = dQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}

		switch (layer_id)
		{
		case LAYER::MEAN:
			DrawRotaGraph3(static_cast<int>(pos.x), static_cast<int>(pos.y),
				0, 0,
				ExRate.x, ExRate.y, rad, id, true, turnFlag);
			break;
		case LAYER::UI:
			DrawRotaGraph3(static_cast<int>(pos.x), static_cast<int>(pos.y),
				0, 0,
				ExRate.x, ExRate.y, rad, id, true, turnFlag);
			break;
		case LAYER::NUMBER:
			DrawRotaGraph3(static_cast<int>(pos.x), static_cast<int>(pos.y),
				0, 0,
				ExRate.x, ExRate.y, rad, id, true, turnFlag);
			break;

		case LAYER::EX:
			// �V���ύX����Ƃ��u�����g�p
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blendCnt);
			DrawRotaGraph(pos.x, pos.y, 1.0, rad, id, true, turnFlag);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			break;
		default:
			DrawRotaGraph3(pos.x - mapPos.x, pos.y - mapPos.y,
				0,0,
				ExRate.x, ExRate.y, rad, id, true, turnFlag);
			break;
		}
	}


	std::sort(_textList.begin(), _textList.end(), [](TextQueT tQueA, TextQueT tQueB) {

		return	std::tie(std::get<static_cast<int>(TEXT_QUE::LAYER)>(tQueA), std::get<static_cast<int>(TEXT_QUE::ZODER)>(tQueA))
			<
			std::tie(std::get<static_cast<int>(TEXT_QUE::LAYER)>(tQueB), std::get<static_cast<int>(TEXT_QUE::ZODER)>(tQueB));
	});

	for (auto tQue : _textList)
	{
		const char* key;
		Vector2 pos;
		Vector2Dbl ExRate;

		LAYER layer_id;
		int size;
		// ����Ȃ����Ƃ��΂�
		// tie:��������o�̓X�g���[���I�u�W�F�N�g���擾�E�ݒ肷��
		std::tie(key, pos, ExRate,size, std::ignore, layer_id) = tQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}


		SetFontSize(size);

		switch (layer_id)
		{

		case LAYER::UI:

			DrawExtendString(pos.x, pos.y, ExRate.x, ExRate.y, key, 0xFFFFFF);
			break;
		default:
			break;
		}


	}



	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();


	// �S���̃��C���[�\������
	for (auto layer_id : LAYER())
	{
		DrawRotaGraph(ScreenSize.x/2, ScreenSize.y/2, 1.0, 0, _screenID[layer_id], true);
	}

	for (int y = 0; y < 75; y++)
	{
		for (int x = 0; x < 75; x++)
		{
			//��ʂɃ}�X��`�悷��
			DrawBox(-IpSceneMng.mapPos.x + x * 32, -IpSceneMng.mapPos.y + y * 32			//����
				, -IpSceneMng.mapPos.x + (x + 1) * 32, -IpSceneMng.mapPos.y + (y + 1) * 32  //�E��
				, GetColor(128, 128, 128)   //���̐F
				, false);   //�h��Ԃ��H

			////��ʂɃ}�X�̔ԍ���`�悷��
			//DrawFormatString(-IpSceneMng.mapPos.x + x * 32 + 1
			//	, -IpSceneMng.mapPos.y + y * 32
			//	, GetColor(0, 128, 0)
			//	, "%02X", x + y * 32);
		}
	}
	

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontSize(20);

	_dbgDrawFPS();


	ScreenFlip();
}