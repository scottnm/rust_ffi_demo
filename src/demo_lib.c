#include "demo_lib.h"

#define UNUSED(x) do { (void)(x); } while(0)

int
GetEvents(
    _Out_ uint32_t* count,
    _Out_ DL_Event_List* events
    )
{
    // TODO: C11 support - use C11 initializers
    static const DL_CreatedEvent createEvent =
    {
        { DL_EventType_Created },
        "Creation",
    };

    static const DL_DestroyedEvent destroyEvent =
    {
        { DL_EventType_Destroyed },
        'D',
    };

    static const DL_ChangedEvent changeEvent =
    {
        { DL_EventType_Changed },
        ChangedEvent_StateB,
    };

    static const DL_Event* eventList[] =
    {
        (const DL_Event*)&changeEvent,
        (const DL_Event*)&createEvent,
        (const DL_Event*)&destroyEvent,
    };

    *count = sizeof(eventList)/sizeof(eventList[0]);
    *events = eventList;
    return 0;
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
