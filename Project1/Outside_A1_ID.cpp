#include "Outside_A1_ID.h"
#include <type_traits>


Outside_A1_ID begin(Outside_A1_ID)
{
	return Outside_A1_ID::A1;
}

Outside_A1_ID end(Outside_A1_ID)
{
	return Outside_A1_ID::H16;
}

Outside_A1_ID operator*(Outside_A1_ID & key)
{
	return key;
}

Outside_A1_ID operator++(Outside_A1_ID & key)
{
	return key = static_cast<Outside_A1_ID>(std::underlying_type<Outside_A1_ID>::type(key) + 1);
}
