#include "_debug/_DeBugConOut.h"
#include "InputState.h"
#include "Dxlib.h"

//コンストラクタで初期化するのは一番安全
//例えInitの関数を作れば、ほかの関数を先に読む可能性がある
InputState::InputState()
{
	// try_emplace:
	//		引数と等価のキーを持つ要素が存在しない場合、コンテナに新しい要素を挿入する。
	//		要素は引数からコンテナ内に直接構築されるため、構築されたオブジェクトはコピーもムーブもされない。
	
	// enum classで範囲FOR文のやり方：INPUT_ID.cppとINPUT_ID.h
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
	// tryとcatch は if else あるいは　switchみたい
	// try：		
	//		エラーがあるかどうかわからないけどやってみる
	// catch：		
	//		もしtryして、エラーがある場合catchの部分を執行する
	
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
	//		指定したキーを持つ要素を取得する。要素を取り出す際にキーの存在チェックをする。
	// キーxに対応する値を返す。対応する要素が存在しないときは、out_of_range例外を投げる。

	// out_of_range:
	//		引数が許容範囲外であることを示す。

	// operator[]:	
	//		指定したキーを持つ要素を取得する。対応する要素が存在しない場合は生成して返す。
	// 今の状態にはconstがあるので、書き込むことはできない。つまり、生成できない。ですから,atを使う

	// 後ろのconstがあるので、書き込むことはできない。
	// ガイド行為ができない
	// なのでエラーが出る
	// return _state[id];
}

// 今のINPUTキー情報のセット関数
bool InputState::state(INPUT_ID id,int data)
{
	// データが存在している場合、更新する
	if (_state.find(id) != _state.end())
	{
		// キー今の情報
		_state[id].first = data;
		return true;
	}
	return false;
}

// オルトのINPUTキー情報のセット関数
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

