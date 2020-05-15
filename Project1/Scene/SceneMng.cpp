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

//���I�V���O���g��
SceneMng *SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 }, GameScreenSize{ ScreenSize / 2 }					// ������
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
		double x, y, rad;
		int id;
		Vector2 size;
		LAYER layer_id;

		// ����Ȃ����Ƃ��΂�
		// tie:��������o�̓X�g���[���I�u�W�F�N�g���擾�E�ݒ肷��
		std::tie(id, x, y, size.x,size.y, rad, std::ignore, layer_id) = dQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}

		switch (layer_id)
		{

		case LAYER::PUTTOM:
			// �{�^���`��\������u�����g
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(250 * sin(_frames / 25.0)));
			DrawRotaGraph(static_cast<int>(x)/*+size.x/2*/ , static_cast<int>(y) /*+ size.y / 2*/, 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case LAYER::EX:
			// �V���ύX����Ƃ��u�����g�p
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, IpSceneMng._blendCnt);
			DrawRotaGraph(static_cast<int>(x)/*+size.x/2*/, static_cast<int>(y) /*+ size.y / 2*/, 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			break;
		default:
			//DrawRotaGraph(static_cast<int>(x)+size.x/2 , static_cast<int>(y) + size.y / 2, 1.0, rad, id, true);
			DrawRotaGraph3(static_cast<int>(x) , static_cast<int>(y),
				0,0,
				1.0,1.0, rad, id, true);
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
	ScreenFlip();
}



SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();

	//�@�X�}�[�g�|�C���^-������Z�q-�^�C�g���V���֍s��
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// clear�F�S�Ă̗v�f���폜����
		_drawList.clear();
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

// �����𑝉�����
bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

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

	_frames = 0;
	//testmode=false;


	return false;
}