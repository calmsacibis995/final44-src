#include <sys/param.h>
#include <sys/time.h>
#include "proc.h"

main()
{
	printf("sizeof proc %d\n", sizeof(struct proc));
}
