#include "demo_lib.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) do { (void)(x); } while(0)

// Mock state
static const DL_CreatedEvent CREATED_EVENT =
{
    { DL_EventType_Created },
    "Creation",
};

static const DL_DestroyedEvent DESTROYED_EVENT =
{
    { DL_EventType_Destroyed },
    'D',
};

static const DL_ChangedEvent CHANGED_EVENT =
{
    { DL_EventType_Changed },
    ChangedEvent_StateB,
};

static DL_Event const * const EVENT_LIST[] =
{
    (const DL_Event*)&CHANGED_EVENT,
    (const DL_Event*)&CREATED_EVENT,
    (const DL_Event*)&DESTROYED_EVENT,
};

static uint32_t G_currentEventCount = 0;
static DL_Event_List G_currentEvents = NULL;

static
bool
streq(
    const char* str1,
    const char* str2
    )
{
    return strcmp(str1, str2) == 0;
}

int
GetEvents(
    _Out_ uint32_t* count,
    _Out_ DL_Event_List* events
    )
{
    // TODO: C11 support - use C11 initializers
    if (G_currentEvents != NULL)
    {
        return 1;
    }

    G_currentEventCount = sizeof(EVENT_LIST)/sizeof(EVENT_LIST[0]);
    G_currentEvents = EVENT_LIST;

    *count = G_currentEventCount;
    *events = G_currentEvents;
    return 0;
}

int
ReturnEvents(
    uint32_t count,
    DL_Event_List events
    )
{
    if (count != G_currentEventCount ||
        events != G_currentEvents)
    {
        return 1;
    }

    G_currentEventCount = 0;
    G_currentEvents = NULL;
    return 0;
}

int
HandleCreatedEvent(
    const char* creationString
    )
{
    return !streq(creationString, CREATED_EVENT.creationString);
}

int
HandleDestroyedEvent(
    uint8_t destroyedByte
    )
{
    return destroyedByte != DESTROYED_EVENT.destroyedByte;
}

int
HandleChangedEvent(
    ChangedState changedState
    )
{
    return changedState != CHANGED_EVENT.changedState;
}
