#include "KeyState.h"
#include <Dxlib.h>
#include "_debug\_DeBugConOut.h"
#include "InputState.h"

KeyState::KeyState()
{
	// 先にreserveしたら、メモリがきれいに使える
	// size_t:
	//		オブジェクトのバイト数を表現できる程度に十分に大きい符号なし整数型

	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));

	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_C);
	_keyConDef.emplace_back(KEY_INPUT_V);

	FILE* file;
	fopen_s(&file, "data/key.dat", "rb");
	if (file==nullptr)
	{
		_keyCon = _keyConDef;
	}
	else
	{
		// resize：要素数を変更する
		_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));
		fread(_keyCon.data(), sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
		// 要素アクセス:operator[],data,書き方がいろいろある
		// fread(&_keyCon[0], sizeof(&_keyCon[0])*_keyCon.size(), 1, file);
		// 連続のデータしかできない
		// fread(&_keyCon[0], sizeof(&_keyCon[0]),_keyCon.size(), file);
		fclose(file);
	}
		
	//_keyCon = _keyConDef;

	//// データを読み込む
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
	// 全てのキー情報を_bufに入る
	GetHitKeyStateAll(_buf);
	
	// 自分自身のポインタ:func = &KeyState::RefKeyData; 最後RefKeyDataを実行する
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// 範囲FOR文で、INPUT_IDの順番にキー情報をセットする
	for(auto id: INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<size_t>(id)]]);
	}
	// 今のF1キーとオルトF1キーの設定
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		_confID = INPUT_ID::LEFT;
		func = &KeyState::SetKeyConfig;
		TRACE("キーコンフィグ開始\n");
		// SetKeyConfigの先頭に設定するなら、何回も出るので、RefKeyDataのmodeを切り替える時に設定する、先頭に一回出る
		TRACE("%d/%d番目のキー設定\n", static_cast<int>(_confID)+1,end(INPUT_ID()));
	}
}

void KeyState::SetKeyConfig(void)
{
	
	// 今のF1キーとオルトF1キーの設定
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		func = &KeyState::RefKeyData;
		TRACE("キーコンフィグ終了\n");
	}
	// 新しいINPUTキー情報を設定したいので、0にする
	for (auto key : INPUT_ID())
	{
		state(key, 0);
	}

	// キャプチャ：コピー、参照２つある
	// コピーキャプチャ：[=]
	//			安全性が高いけど、メモリを食うし、スピードが遅い
	//			[=,&...]単独に参照することができる
	// 参照キャプチャ：[&]
	//			スピードが速いし、値も書き換えるけど、デリート可能性もある
	auto checkKey=[&](int id) {
		// 8つキーの情報の先頭から最後まで
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
	// 256直接入力したら、変更したい場合は面倒なことになるので、
	// sizeofを使って_bufの要素数をとる
	for (int id = 0; id < sizeof(_buf); id++)
	{
		// キーIDが同じの場合：return false  下の次のif文に入る
		// キーIDが同じじゃない場合：return true  continueしてループ処理の先頭に戻ります
		if (!checkKey(id))
		{
			// continue:
			//		ループ処理の先頭に戻ります
			continue;
		}

		// F1キー以外のキーを押したら、中に入る
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			_keyCon[static_cast<int>(_confID)] = id;
			// イナムクラスのoperator++には前演算が必要
			++_confID;
			TRACE("%dを設定\n", id);

			// INPUT_ID end(INPUT_ID)に行く
			// end(INPUT_ID::MAX)形は正しいなら、何を入力してもいい
			if (_confID == end(_confID))
			{
				// データを保存
				FILE* file;
				fopen_s(&file, "data/key.dat", "wb");
				if (file != nullptr)
				{
					fwrite(_keyCon.data(), sizeof(_keyCon[0])*_keyCon.size(), 1, file);
					fclose(file);
				}

				TRACE("キーコンフィグ終了\n");
				func = &KeyState::RefKeyData;
				break;
			}
			TRACE("%d/%d番目のきー設定\n", static_cast<int>(_confID) + 1, end(INPUT_ID()));
		}
	}
}


