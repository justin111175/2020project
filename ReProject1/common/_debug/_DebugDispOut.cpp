#ifdef _DEBUG
#include <windows.h>
#include <DxLib.h>
#include "..\..\Scene\SceneMng.h"
#include "_DebugDispOut.h"

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeleter> _DebugDispOut::s_Instance(new _DebugDispOut);
_DebugDispOut::_DebugDispOut()
{
	_DbgScreen = -1;
	_waitTime  = 0;
	clsFlag = true;
	StartFPS();
}

_DebugDispOut::~_DebugDispOut()
{
}

void _DebugDispOut::SetScreen(void)
{
	ghBefor = GetDrawScreen();
	SetDrawScreen(_DbgScreen);
	//SetFontSize(30);
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
}

void _DebugDispOut::RevScreen(void)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
}

void _DebugDispOut::WaitMode(void)
{
	if (CheckHitKey(KEY_INPUT_ADD))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime+=100;
		}
		else
		{
			_waitTime++;
		}
	}
	if (CheckHitKey(KEY_INPUT_SUBTRACT))
	{
		if (CheckHitKey(KEY_INPUT_MULTIPLY))
		{
			_waitTime -= 100;
		}
		else
		{
			_waitTime--;
		}
		if (_waitTime < 0.0)
		{
			_waitTime = 0.0;
		}
	}
	if (CheckHitKey(KEY_INPUT_DIVIDE))
	{
		_waitTime = 0.0;
	}
	if (_waitTime)
	{
		_startTime = std::chrono::system_clock::now();
		do {
			if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			{
				break;
			}
			_endTime = std::chrono::system_clock::now();
		} while (std::chrono::duration_cast<std::chrono::milliseconds>(_endTime - _startTime).count() < _waitTime);
	}
	endKey[1] = endKey[0];
	endKey[0] = CheckHitKey(KEY_INPUT_END);
	if (endKey[0] && !endKey[1])
	{
		clsFlag ^= 1;
	}
}



int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawGraph(x , y , GrHandle, TransFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawBox(x1 , y1 , x2 , y2 , Color, FillFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawString(int x, int y, char* String, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawString(x, y, String, Color);
	RevScreen();
	return rtnFlag;
}

//int _DebugDispOut::DrawFormatString(int x, int y, unsigned int Color, const char* FormatString, ...)
//{
//	DrawFormatString(x, y, Color, FormatString, ...);
//}

//int _DebugDispOut::DrawFormatString(int x, int y, unsigned int Color,const char* FormatString, ...)
//{
//	SetScreen();
//
//	int rtnFlag = DxLib::DrawFormatString(x, y, Color, FormatString);
//	RevScreen();
//
//	return rtnFlag;
//
//}





int _DebugDispOut::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawLine(x1 , y1 , x2 , y2 , Color);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag)
{
	SetScreen();
	int rtnFlag = DxLib::DrawCircle(x , y , r, Color, FillFlag);
	RevScreen();
	return rtnFlag;
}

int _DebugDispOut::DrawPixel(int x, int y, unsigned int Color)
{
	SetScreen();
	int rtnFlag = DxLib::DrawPixel(x , y , Color);
	RevScreen();
	return rtnFlag;
}

void _DebugDispOut::StartFPS(void)
{
	_fpsStartTime = std::chrono::system_clock::now();
	_fpsCount = 0;
}

void _DebugDispOut::DrawFPS(void)
{
	_fpsEndTime = std::chrono::system_clock::now();
	if (std::chrono::duration_cast<std::chrono::milliseconds>(_fpsEndTime - _fpsStartTime).count() < 1000)
	{
		_fpsCount++;
	}
	else
	{
		_fps = _fpsCount;
		StartFPS();
	}
	DrawFormatString(0, 0, 0xffff, "FPS:%d", _fps);
}

bool _DebugDispOut::StartDrawDebug(void)
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_DbgScreen);
	if (clsFlag)
	{
		ClsDrawScreen();
	}
	SetDrawScreen(ghBefor);
	return true;
}

bool _DebugDispOut::AddDrawDebug(void)
{
	if (CheckHitKey(KEY_INPUT_PGUP))
	{
		dispFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_PGDN))
	{
		dispFlag = false;
	}
	if (dispFlag)
	{
		IpSceneMng.AddDrawQue({ _DbgScreen,{0,0},{0,0},{1.0f,1.0f},false,0,INT_MAX,LAYER::UI });
	}
	WaitMode();
	return true;
}

bool _DebugDispOut::SetAlpha(int alpha)
{
	_alpha = alpha;

	return true;
}

bool _DebugDispOut::Setup(int alpha)
{
	if (_DbgScreen == -1)
	{
		_DbgScreen = MakeScreen(IpSceneMng.ScreenSize.x, IpSceneMng.ScreenSize.y, true);
	}
	SetAlpha(alpha);
	return false;
}

bool _DebugDispOut::SetWait(double timeCnt)
{
	_waitTime = timeCnt;
	return true;
}

#endif	// _DEBUG
