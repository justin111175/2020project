#include <Dxlib.h>
#include <SceneMng.h>
#include <GameScene.h>
#include <Obj.h>
#include <time.h>
#include <_DeBugConOut.h>
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>
#include <KeyState.h>
#include <TitleScene.h>
#include <Floor.h>
#include <GameOverScene.h>

//���I�V���O���g��
SceneMng *SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 1280,720 }, GameScreenSize{ ScreenSize / 2 }				// ������
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();

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
		Vector2Dbl pos;
		Vector2Dbl size;
		Vector2Dbl ExRate;
		LAYER layer_id;
		
		// ����Ȃ����Ƃ��΂�
		// tie:��������o�̓X�g���[���I�u�W�F�N�g���擾�E�ݒ肷��
		std::tie(id, pos, size,ExRate, rad, std::ignore, layer_id) = dQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}

		switch (layer_id)
		{
		case LAYER::MEAN:
			DrawRotaGraph3(static_cast<int>(pos.x) , static_cast<int>(pos.y) ,
				0, 0,
				ExRate.x, ExRate.y, rad, id, true);
			break;
		case LAYER::UI:
			DrawRotaGraph3(static_cast<int>(pos.x), static_cast<int>(pos.y),
				0, 0,
				ExRate.x, ExRate.y, rad, id, true);
			break;
		case LAYER::NUMBER:
			DrawRotaGraph3(static_cast<int>(pos.x), static_cast<int>(pos.y),
				0, 0,
				ExRate.x, ExRate.y, rad, id, true);
			break;
		case LAYER::PUTTOM:
			//// �{�^���`��\������u�����g
			//SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(250 * sin(_frames / 25.0)));
			//DrawRotaGraph(static_cast<int>(x)/*+size.x/2*/ , static_cast<int>(y) /*+ size.y / 2*/, 1.0, rad, id, true);
			//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case LAYER::EX:
			// �V���ύX����Ƃ��u�����g�p
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, IpSceneMng._blendCnt);
			DrawRotaGraph(pos.x, pos.y , 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			break;
		default:
			DrawRotaGraph3(pos.x+mapPos.x, pos.y+mapPos.y,
				0,0,
				ExRate.x, ExRate.y, rad, id, true);
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
		Vector2Dbl pos;
		Vector2Dbl ExRate;

		LAYER layer_id;

		// ����Ȃ����Ƃ��΂�
		// tie:��������o�̓X�g���[���I�u�W�F�N�g���擾�E�ݒ肷��
		std::tie(key, pos, ExRate, std::ignore, layer_id) = tQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}
		

		//DrawString(pos.x, pos.y, key, 0xFFFFFF);
		SetFontSize(40);

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
		DrawRotaGraph(GameScreenSize.x, GameScreenSize.y, 1.0, 0, _screenID[layer_id], true);
	}
	_dbgDrawFPS();


	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontThickness(3);



	ScreenFlip();
}



SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();

	//�@�X�}�[�g�|�C���^-������Z�q-�^�C�g���V���֍s��
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{
		// clear�F�S�Ă̗v�f���폜����
		_drawList.clear();
		_textList.clear();
		_dbgStartDraw();
		// _activeScene->
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// move�̓R�s�[���܂���A���L����n������
		(*_activeScene).RunActQue(std::move(_actList));

		(*_input).Update();

		Draw();
		
		_frames++;
	}
}

// �`��𑝉�����
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



// �����𑝉�����
bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

//void SceneMng::_DrawFormatString(int x, int y, unsigned int Color,const char* FormatString, ...)
//{
//	DrawFormatString(x, y, Color, FormatString);
//}

// �t���[�����̃Q�b�g�֐�
const int SceneMng::frames(void) const
{
	return _frames;
}

// �V�X�e��������
bool SceneMng::SysInit(void)
{
	// �V�X�e������
	SetWindowText("����ꂽ�s �A�g�����e�B�X");		// �^�C�g���o�[
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:�t���X�N���[��
	if (DxLib_Init() == -1)												// DX�����u�����̏�����
	{
		return false;
	}
	
	_input = std::make_shared<KeyState>();


	// true:�A���t�@�`�����l���̓���
	_dbgSetup(215);														// debug�p�F�̓����x


	// ���C���[�̐ݒ�
	_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::PUTTOM, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));



	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 50; x++)
		{
			IpSceneMng.mapNow[y][x] = 0;
		}
	}

	_frames = 0;


	return false;
}