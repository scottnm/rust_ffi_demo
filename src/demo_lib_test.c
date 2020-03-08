#include <assert.h>
#include <stdio.h>
#include "demo_lib.h"

void
main(
    int argc,
    char** argv
    )
{
    // the first arg is the executable name so there's always at least 1.
    assert(argc >= 1);
    printf("Testing... %s\n", argv[0]);
}
