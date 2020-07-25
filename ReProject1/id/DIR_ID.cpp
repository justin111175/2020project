#include "DIR_ID.h"
#include <type_traits>

DIR_ID begin(DIR_ID)
{
    return DIR_ID::DOWN;
}

DIR_ID end(DIR_ID)
{
    return DIR_ID::MAX;
}

DIR_ID operator*(DIR_ID& key)
{
    return key;
}

DIR_ID operator++(DIR_ID& key)
{
    return key = static_cast<DIR_ID>(std::underlying_type<DIR_ID>::type(key) + 1);
}
