#ifndef DEMO_LIB_H
#define DEMO_LIB_H

#include <stdint.h>

enum E_DL_EventType
{
    DL_EventType_Created,
    DL_EventType_Destroyed,
    DL_EventType_Changed,
};

// TODO: C11 support - see if I can drop the enum prefix
typedef enum E_DL_EventType DL_EventType;

struct S_DL_Event
{
    DL_EventType type;
};

// TODO: C11 support - see if I can drop the struct prefix
typedef struct S_DL_Event DL_Event;

struct S_DL_CreatedEvent
{
    DL_Event baseEvent;
    const char* creationString;
};

// TODO: C11 support - see if I can drop the struct prefix
typedef struct S_DL_CreatedEvent DL_CreatedEvent;

struct S_DL_DestroyedEvent
{
    DL_Event baseEvent;
    uint8_t destroyedByte;
};

// TODO: C11 support - see if I can drop the struct prefix
typedef struct S_DL_DestroyedEvent DL_DestroyedEvent;

enum E_ChangedState
{
    ChangedEvent_StateA,
    ChangedEvent_StateB,
};

// TODO: C11 support - see if I can drop the enum prefix
typedef enum E_ChangedState ChangedState;

struct S_DL_ChangedEvent
{
    DL_Event baseEvent;
    ChangedState changedState;
};

// TODO: C11 support - see if I can drop the struct prefix
typedef struct S_DL_ChangedEvent DL_ChangedEvent;

typedef const DL_Event * DL_Event_List;

int
GetEvents(
    _Out_ uint32_t* count,
    _Out_ DL_Event_List* events
    );

int
ReturnEvents(
    uint32_t count,
    DL_Event_List events
    );

int
HandleCreatedEvent(
    const char* creationString
    );

int
HandleDestroyedEvent(
    uint8_t destroyedByte
    );

int
HandleChangedEvent(
    ChangedState changedState
    );

#endif // DEMO_LIB_H
