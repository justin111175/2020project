#include "MeanID.h"
#include <type_traits>

MeanID begin(MeanID)
{
    return MeanID::ステータス;
}

MeanID end(MeanID)
{
    return MeanID::MAX;
}

MeanID operator*(MeanID key)
{
   return key;
}

MeanID operator++(MeanID& key)
{
    return key = MeanID(std::underlying_type<MeanID>::type(key) + 1);
}
