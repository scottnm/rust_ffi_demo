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

struct DL_Event
{
    DL_EventType type;
};

#endif // DEMO_LIB_H
