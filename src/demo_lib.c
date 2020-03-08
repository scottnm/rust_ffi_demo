#include "demo_lib.h"

#define UNUSED(x) do { (void)(x); } while(0)

int
GetEvents(
    _Out_ uint32_t* count,
    _Out_ DL_Event_List* events
    )
{
    // TODO: impl
    UNUSED(count);
    UNUSED(events);
    return 1;
}

int
ReturnEvents(
    uint32_t count,
    DL_Event_List events
    )
{
    // TODO: impl
    UNUSED(count);
    UNUSED(events);
    return 1;
}

int
HandleCreatedEvent(
    const char* creationString
    )
{
    // TODO: impl
    UNUSED(creationString);
    return 1;
}

int
HandleDestroyedEvent(
    uint8_t destroyedByte
    )
{
    // TODO: impl
    UNUSED(destroyedByte);
    return 1;
}

int
HandleChangedEvent(
    ChangedState changedState
    )
{
    // TODO: impl
    UNUSED(changedState);
    return 1;
}
