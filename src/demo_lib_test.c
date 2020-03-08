#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "demo_lib.h"

#define EXIT_IF_ERR(err) \
    do \
    { \
        int scoped_err = (err); \
        if (scoped_err != 0) \
        { \
            printf("...Failed! line %i!\n", __LINE__); \
            exit(scoped_err); \
        } \
    } while(0)

void
main(
    int argc,
    char** argv
    )
{
    int err = 0;

    // TODO: verify failures

    // the first arg is the executable name so there's always at least 1.
    assert(argc >= 1);
    printf("Testing... %s\n", argv[0]);

    uint32_t eventCount;
    DL_Event_List events;
    err = GetEvents(&eventCount, &events);
    EXIT_IF_ERR(err);

    for (uint32_t i = 0; i < eventCount; ++i)
    {
        const DL_Event* event = events[i];

        printf("Processing event of type %i\n", event->type);
        switch (event->type)
        {
            case DL_EventType_Created:
            {
                const DL_CreatedEvent* createdEvent = (const DL_CreatedEvent*)event;
                err = HandleCreatedEvent(createdEvent->creationString);
                EXIT_IF_ERR(err);
                break;
            }
            case DL_EventType_Destroyed:
            {
                const DL_DestroyedEvent* destroyedEvent = (const DL_DestroyedEvent*)event;
                err = HandleDestroyedEvent(destroyedEvent->destroyedByte);
                EXIT_IF_ERR(err);
                break;
            }
            case DL_EventType_Changed:
            {
                const DL_ChangedEvent* changedEvent = (const DL_ChangedEvent*)event;
                err = HandleChangedEvent(changedEvent->changedState);
                EXIT_IF_ERR(err);
                break;
            }
            default:
            {
                // Shouldn't ever hit
                assert(false);
                break;
            }
        }
    }

    err = ReturnEvents(eventCount, events);
    EXIT_IF_ERR(err);
    // TODO: call rest of APIs

    printf("...Succeeded!\n");
}
