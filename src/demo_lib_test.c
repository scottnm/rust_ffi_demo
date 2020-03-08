#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "demo_lib.h"

#define EXPECT_SUCCESS(err) \
    do \
    { \
        int scoped_err = (err); \
        if (scoped_err != 0) \
        { \
            printf("...Failed! line %i!\n", __LINE__); \
            exit(scoped_err); \
        } \
    } while(0)

#define EXPECT_FAILURE(err) \
    do \
    { \
        int scoped_err = (err); \
        if (scoped_err == 0) \
        { \
            printf("...Unexpected success! line %i!\n", __LINE__); \
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

    // the first arg is the executable name so there's always at least 1.
    assert(argc >= 1);
    printf("Testing... %s\n", argv[0]);

    //
    // Verify golden-path basic API usage
    //

    uint32_t eventCount;
    DL_Event_List events;
    err = GetEvents(&eventCount, &events);
    EXPECT_SUCCESS(err);

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
                EXPECT_SUCCESS(err);
                break;
            }
            case DL_EventType_Destroyed:
            {
                const DL_DestroyedEvent* destroyedEvent = (const DL_DestroyedEvent*)event;
                err = HandleDestroyedEvent(destroyedEvent->destroyedByte);
                EXPECT_SUCCESS(err);
                break;
            }
            case DL_EventType_Changed:
            {
                const DL_ChangedEvent* changedEvent = (const DL_ChangedEvent*)event;
                err = HandleChangedEvent(changedEvent->changedState);
                EXPECT_SUCCESS(err);
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
    EXPECT_SUCCESS(err);

    //
    // Verify golden-path basic API failures
    //

    // Can't call ReturnEvents before calling GetEvents
    EXPECT_FAILURE(ReturnEvents(eventCount, events));

    // Can't call GetEvents multiple times without calling ReturnEvents in between
    EXPECT_SUCCESS(GetEvents(&eventCount, &events));
    {
        uint32_t unusedEventCount;
        DL_Event_List unusedEvents;
        EXPECT_FAILURE(GetEvents(&unusedEventCount, &unusedEvents));
    }
    EXPECT_SUCCESS(ReturnEvents(eventCount, events));

    // Must call ReturnEvents with the events returned from GetEvents
    EXPECT_SUCCESS(GetEvents(&eventCount, &events));
    EXPECT_FAILURE(ReturnEvents(eventCount - 1, events + 1));
    EXPECT_SUCCESS(ReturnEvents(eventCount, events));

    // Basic handle-function failure validation. Must pass in the expected parameters.
    EXPECT_SUCCESS(GetEvents(&eventCount, &events));
    for (uint32_t i = 0; i < eventCount; ++i)
    {
        const DL_Event* event = events[i];
        switch (event->type)
        {
            case DL_EventType_Created:
            {
                const DL_CreatedEvent* createdEvent = (const DL_CreatedEvent*)event;
                char copy[1024];
                errno_t copyError = strcpy_s(
                    copy,
                    sizeof(copy) / sizeof(copy[0]),
                    createdEvent->creationString);
                EXPECT_SUCCESS(copyError);
                EXPECT_FAILURE(HandleCreatedEvent(createdEvent->creationString + 1));
                EXPECT_SUCCESS(HandleCreatedEvent(copy));
                break;
            }
            case DL_EventType_Destroyed:
            {
                const DL_DestroyedEvent* destroyedEvent = (const DL_DestroyedEvent*)event;
                EXPECT_FAILURE(HandleDestroyedEvent(destroyedEvent->destroyedByte + 1));
                break;
            }
            case DL_EventType_Changed:
            {
                const DL_ChangedEvent* changedEvent = (const DL_ChangedEvent*)event;
                EXPECT_FAILURE(HandleChangedEvent(changedEvent->changedState + 1));
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
    EXPECT_SUCCESS(ReturnEvents(eventCount, events));

    printf("...Succeeded!\n");
}
