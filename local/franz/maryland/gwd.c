#include <stdio.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include "ldefs.h"
/*
 * Find working (current) directory
 */

#ifndef	lint
static char *sccsid="@(#)gwd1.c	1.0 (U of M) ACT 3/11/82";
#endif

char *gwd1()
{
	register int	file,rdev,rino,off=BUFSIZ;
	static char	name[BUFSIZ];
	struct stat	d,dd;
	struct direct	dir;

	name[--off]=0;
	stat("/",&d);
	rdev=d.st_dev;
	rino=d.st_ino;
	for(;;)
	{
		stat(".",&d);
		if(d.st_ino==rino&&d.st_dev==rdev)
		{
			chdir(name+off);
			return name+off;
		}
		if((file=open("..",0))<0)
		{
			fprintf(stderr,"gwd: cannot open ..\n");
			return 0;
		}
		fstat(file,&dd);
		chdir("..");
		if(d.st_dev==dd.st_dev)
		{
			if(d.st_ino==dd.st_ino)
			{
				chdir(name+off);
				return name+off;
			}
			do
				if(read(file,(char *)&dir,sizeof(dir))
				<sizeof(dir))
				{
					fprintf(stderr,
					"read error in ..\n");
					return 0;
				}
			while(dir.d_ino!=d.st_ino);
		}
		else do
		{
				if(read(file,(char *)&dir,sizeof(dir))
				<sizeof(dir))
				{
					fprintf(stderr,
					"read error in ..\n");
					return 0;
				}
				stat(dir.d_name,&dd);
		} while(dd.st_ino!=d.st_ino||dd.st_dev!=d.st_dev);
		close(file);
		for(file=14;!(dir.d_name[--file]););
		for(++file;file;)name[--off]=dir.d_name[--file];
		name[--off]='/';
	}
}

extern lispval mstr();
lispval gwd()
   {
   return(mstr(gwd1()));
   }

#ifdef	TEST
main(){printf("%s\n",gwd());}
#endif

