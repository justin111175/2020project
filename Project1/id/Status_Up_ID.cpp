#include "Status_Up_ID.h"
#include <type_traits>

Status_Up_ID begin(Status_Up_ID)
{
    return Status_Up_ID::UŒ‚—Í;
}

Status_Up_ID end(Status_Up_ID)
{
    return Status_Up_ID::MAX;
}

Status_Up_ID operator*(Status_Up_ID& key)
{
    return key;
}

Status_Up_ID operator++(Status_Up_ID& key)
{
    return key = static_cast<Status_Up_ID>(std::underlying_type<Status_Up_ID>::type(key) + 1);
}
