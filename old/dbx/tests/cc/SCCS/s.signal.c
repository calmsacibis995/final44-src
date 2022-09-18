h40521
s 00029/00000/00000
d D 5.1 90/06/25 15:30:08 bostic 1 0
c date and time created 90/06/25 15:30:08 by bostic
e
u
U
t
T
I 1
/*
 * Test of tracebacks from signal handlers.
 */

#include <stdio.h>
#include <signal.h>

int catch(), secondcatch();

main()
{
    signal(SIGQUIT, catch);
    kill(getpid(), SIGQUIT);
    printf("back in main\n");
}

catch()
{
    printf("in catch\n");
    sigsetmask(0);
    signal(SIGQUIT, secondcatch);
    kill(getpid(), SIGQUIT);
    printf("back in catch\n");
}

secondcatch()
{
    printf("in secondcatch\n");
}
E 1
