#include "Status_ID.h"
#include <type_traits>

Status_ID begin(Status_ID)
{
    return Status_ID::ƒŒƒxƒ‹;
}

Status_ID end(Status_ID)
{
    return Status_ID::MAX;
}

Status_ID operator*(Status_ID& key)
{
    return key;
}

Status_ID operator++(Status_ID& key)
{
    return key = static_cast<Status_ID>(std::underlying_type<Status_ID>::type(key) + 1);
}
