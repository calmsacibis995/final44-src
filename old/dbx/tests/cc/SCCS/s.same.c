h40302
s 00017/00000/00000
d D 5.1 90/06/25 15:30:05 bostic 1 0
c date and time created 90/06/25 15:30:05 by bostic
e
u
U
t
T
I 1
/*
 * The purpose of this test case is to make sure that dbx interprets
 * the command "stop in same" at the top level to mean stop in the
 * routine same.  Originally, dbx complained since "same" in the initial
 * context refers to the module named "same" (since this file is "same.c").
 */

same ()
{
    printf("same function and module names\n");
}

main ()
{
    same();
    exit(0);
}
E 1
