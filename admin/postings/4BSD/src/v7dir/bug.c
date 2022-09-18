#include <sys/types.h>
#include <ndir.h>

main()
{
	DIR	*one,*two;
	struct direct	*e_one;

	one = opendir(".");
	two = opendir(".");
	(void)readdir(one);
	(void)readdir(one);
	do {
		e_one = readdir(one);
	}
	while (!e_one->d_ino);
	printf("one -- %ld %s\n",e_one->d_ino,e_one->d_name);
	(void)readdir(two);
	puts("should be identical to the last print...");
	printf("one -- %ld %s\n",e_one->d_ino,e_one->d_name);
}
