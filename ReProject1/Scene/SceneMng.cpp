#include "SceneMng.h"
#include <Dxlib.h>
#include <algorithm>
#include <tuple>										//要素が三つ以上を管理する時を使う

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

		// clear：全ての要素を削除する
		_drawList.clear();

		(*_activeScene).RunActQue(std::move(_actList));

		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// moveはコピーしません、所有権を渡すだけ


		Draw();



		_frames++;
	}


	return true;
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	//static_cast<int>　はint型になる
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		//画像IDが不正なので、追加しない
		return false;
	}
	//Queを追加する
	//_drawList.push_back()

	//emplace_backは実引数がコンテナの要素型と異なるときに、push_backよりも動作が早くなり、
	//それ以外の場合ではほとんど変わりません。（実引数が単に変数のときなど）

	//emplace_back：	直接構築で新たな要素を末尾に追加する
	//再確保の可能性、イテレータの有効性への影響、例外発生時に副作用が発生しない保証はいずれもpush_back()と同様
	_drawList.emplace_back(dQue);
	return true;
}

bool SceneMng::AddDrawQue(TextQueT tQue)
{
	return false;
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
    ScreenSize{ 1280,800 }
{
    _blendCnt = 0;
    _frames = 0;
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	SetWindowText("失われた都 アトランティス");		// タイトルバー
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:フルスクリーン
	if (DxLib_Init() == -1)												// DXラリブラリの初期化
	{
		return false;
	}


	_chipNo.first = CHIP_TYPE::森1;
	_chipNo.second = false;

	// レイヤーの設定
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

	// スタックにたまっているQueを描画する
	// stdのベクターを調べて回る:範囲FOR
	for (auto dQue : _drawList)
	{

		double rad;
		int id;
		Vector2 pos;
		Vector2Dbl size;
		Vector2Dbl ExRate;
		LAYER layer_id;
		bool turnFlag;
		// いらないことを飛ばす
		// tie:同期する出力ストリームオブジェクトを取得・設定する
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
			// シン変更するときブレント用
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

	//std::sort(_textList.begin(), _textList.end(), [](TextQueT tQueA, TextQueT tQueB) {

	//	return	std::tie(std::get<static_cast<int>(TEXT_QUE::LAYER)>(tQueA), std::get<static_cast<int>(TEXT_QUE::ZODER)>(tQueA))
	//		<
	//		std::tie(std::get<static_cast<int>(TEXT_QUE::LAYER)>(tQueB), std::get<static_cast<int>(TEXT_QUE::ZODER)>(tQueB));
	//});

	//for (auto tQue : _textList)
	//{
	//	const char* key;
	//	Vector2Dbl pos;
	//	Vector2Dbl ExRate;

	//	LAYER layer_id;

	//	// いらないことを飛ばす
	//	// tie:同期する出力ストリームオブジェクトを取得・設定する
	//	std::tie(key, pos, ExRate, std::ignore, layer_id) = tQue;

	//	if (_screenID[layer_id] != GetDrawScreen())
	//	{
	//		SetDrawScreen(_screenID[layer_id]);
	//	}


	//	//DrawString(pos.x, pos.y, key, 0xFFFFFF);
	//	SetFontSize(40);

	//	switch (layer_id)
	//	{

	//	case LAYER::UI:

	//		DrawExtendString(pos.x, pos.y, ExRate.x, ExRate.y, key, 0xFFFFFF);
	//		break;
	//	default:
	//		break;
	//	}


	//}



	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();


	// 全部のレイヤー表示する
	for (auto layer_id : LAYER())
	{
		DrawRotaGraph(ScreenSize.x/2, ScreenSize.y/2, 1.0, 0, _screenID[layer_id], true);
	}

	for (int y = 0; y < 75; y++)
	{
		for (int x = 0; x < 75; x++)
		{
			//画面にマスを描画する
			DrawBox(-IpSceneMng.mapPos.x + x * 32, -IpSceneMng.mapPos.y + y * 32			//左上
				, -IpSceneMng.mapPos.x + (x + 1) * 32, -IpSceneMng.mapPos.y + (y + 1) * 32  //右下
				, GetColor(128, 128, 128)   //線の色
				, false);   //塗りつぶす？

			////画面にマスの番号を描画する
			//DrawFormatString(-IpSceneMng.mapPos.x + x * 32 + 1
			//	, -IpSceneMng.mapPos.y + y * 32
			//	, GetColor(0, 128, 0)
			//	, "%02X", x + y * 32);
		}
	}

	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);
	SetFontThickness(3);



	ScreenFlip();
}