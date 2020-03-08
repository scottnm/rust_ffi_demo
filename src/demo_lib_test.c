#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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
    }

    err = ReturnEvents(eventCount, events);
    EXIT_IF_ERR(err);
    // TODO: call rest of APIs

    printf("...Succeeded!\n");
}
