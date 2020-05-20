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

//動的シングルトン
SceneMng *SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 1280,720 }, GameScreenSize{ ScreenSize / 2 }					// 初期化
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

	// スタックにたまっているQueを描画する
	// stdのベクターを調べて回る:範囲FOR
	for (auto dQue : _drawList)
	{
		double x, y, rad;
		int id;
		Vector2Dbl size;
		LAYER layer_id;

		// いらないことを飛ばす
		// tie:同期する出力ストリームオブジェクトを取得・設定する
		std::tie(id, x, y, size.x,size.y, rad, std::ignore, layer_id) = dQue;

		if (_screenID[layer_id] != GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer_id]);
		}

		switch (layer_id)
		{

		case LAYER::PUTTOM:
			// ボタン描画表示するブレント
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, abs(250 * sin(_frames / 25.0)));
			DrawRotaGraph(static_cast<int>(x)/*+size.x/2*/ , static_cast<int>(y) /*+ size.y / 2*/, 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			break;
		case LAYER::EX:
			// シン変更するときブレント用
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, IpSceneMng._blendCnt);
			DrawRotaGraph(static_cast<int>(x)/*+size.x/2*/, static_cast<int>(y) /*+ size.y / 2*/, 1.0, rad, id, true);
			SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);
			break;
		default:
//			DrawRotaGraph(static_cast<int>(x)+size.x/2 , static_cast<int>(y) + size.y / 2, 1.0, rad, id, true);
			DrawRotaGraph3(static_cast<int>(x) , static_cast<int>(y),
				0,0,
				1.0,1.0, rad, id, true);
			break;
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	// 全部のレイヤー表示する
	for (auto layer_id : LAYER())
	{
		DrawRotaGraph(GameScreenSize.x, GameScreenSize.y, 1.0, 0, _screenID[layer_id], true);
	}
	_dbgDrawFPS();

	//DrawString(0, 0, "今日もいい天気だ", GetColor(255, 255, 255));

	//// 文字列の長さを取得
	//int StrLen = strlen("今日もいい天気だ");

	//// 描画時の文字列の幅を取得
	//int StrWidth = GetDrawStringWidth("今日もいい天気だ", StrLen);

	//// 「今日もいい天気だ」の直後に新たな文字列を描画
	//DrawString(StrWidth, 100, "明日も晴れると良いなあ", GetColor(255, 255, 255));


	//DrawBox(0, 0, 640, 480, GetColor(128, 128, 0), TRUE);

	// サイズを４０に変更
	SetFontSize(40);

	// 『ＤＸライブラリ』と描画
	DrawString(100, 100, "ＤＸライブラリ", GetColor(255, 255, 255));

	// フォントのタイプをエッジつきアンチエイリアスフォントに変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE);

	// 『ＤＸライブラリ』と描画
	DrawString(100, 160, "ＤＸライブラリ", GetColor(255, 255, 255), GetColor(0, 0, 0));

	ScreenFlip();
}



SceneMng::~SceneMng()
{

}

void SceneMng::Run(void)
{
	SysInit();

	//　スマートポインタ-代入演算子-タイトルシンへ行く
	_activeScene = std::make_unique<GameScene>();

	while (ProcessMessage() == 0 /*&& CheckHitKey(KEY_INPUT_ESCAPE) == 0*/)
	{
		// clear：全ての要素を削除する
		_drawList.clear();
		_dbgStartDraw();
		// _activeScene->
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		// moveはコピーしません、所有権を渡すだけ
		(*_activeScene).RunActQue(std::move(_actList));
		(*_input).Update();

		Draw();

		_frames++;
	}
}

// 描画を増加する
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

// 活動を増加する
bool SceneMng::AddActQue(ActQueT aQue)
{
	_actList.emplace_back(aQue);
	return true;
}

// フレーム数のゲット関数
const int SceneMng::frames(void) const
{
	return _frames;
}

// システム初期化
bool SceneMng::SysInit(void)
{
	// システム処理
	SetWindowText("失われた都 アトランティス");		// タイトルバー
	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);
	ChangeWindowMode(true);												// ture:window false:フルスクリーン
	if (DxLib_Init() == -1)												// DXラリブラリの初期化
	{
		return false;
	}
	
	_input = std::make_shared<KeyState>();


	// true:アルファチャンネルの透明
	_dbgSetup(215);														// debug用色の透明度


	// レイヤーの設定
	_screenID.try_emplace(LAYER::BG, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::CHAR, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::UI, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::PUTTOM, MakeScreen(ScreenSize.x, ScreenSize.y, true));
	_screenID.try_emplace(LAYER::EX, MakeScreen(ScreenSize.x, ScreenSize.y, true));

	_frames = 0;
	//testmode=false;


	return false;
}