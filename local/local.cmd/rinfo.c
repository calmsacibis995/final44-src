static char *rcsident =
  "$Header: /na/doe/jkf/src/RCS/rinfo.c,v 1.2 83/03/09 15:12:07 jkf Exp $";
  
/*
 * rinfo
 *  look for locked rcs files and print out the info about them
 * use:
 *  rinfo [file ...]
 *  if no files are given print all info about files in RCS subdir
 *  if files are given, then print only info about those files.
 *  the working or RCS file may be specified.
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/dir.h>

int tell = 0;

main(argc,argv)
int argc;
char **argv;
{
    int do_if_rcs();
    char *filename, *pgmname;
    char buff[1024];
    char *rindex();

    if ((pgmname = rindex(argv[0],'/')) != 0)
    	pgmname++;	/* to past slash */
    else pgmname = argv[0];
    
    if(strcmp(pgmname,"rtell") == 0) tell = 1;
    
    if(argc > 1)
    {
	while(argc-- > 1)
	{
	    ++argv;
	    /* process each file given */
	    filename = argv[0];
	    if (rcsfilep(filename))
	    {
		/* given an RCS filename */
		doit(filename);
		continue;
	    }
	    /* given a working file name, convert to rcs.
	     * try the RCS directory first
	     */
	    strcpy(buff,"RCS/");
	    strcat(buff,filename);
	    strcat(buff,",v");
	    if((access(buff,4) == 0))
	    {
		doit(buff);
		continue;
	    }
	    /* try the current directory */
	    strcpy(buff,filename);
	    strcat(buff,",v");
	    if((access(buff,4) == 0))
	    {
		doit(buff);
		continue;
	    }
	    fprintf(stderr,"Can't find RCS file for %s\n",filename);
	}
	exit(0);
    }

    /* we haven't been given a list of files. We must find our own list
     * by looking at the current directory
     */
    mapoverdir("RCS",do_if_rcs);
    exit(0);
}

	    
do_if_rcs(filename)
char *filename;
{
    char buff[1024];
    
    if(rcsfilep(filename))
    {
	strcpy(buff,"RCS/");
	strcat(buff,filename);
	doit(buff);
    }
}


doit(name)
{
    char buff[1024];
    FILE *fp;
    char *cp, *cpp;
    
    if((fp = fopen(name,"r")) == NULL)
    {
	perror(name);
	return(0);
    }
    
    while(1)
    {
	if(fgets(buff,1024,fp) == NULL)
	{
	    fprintf(stderr,"%s: can't find lock field\n",name);
	    fclose(fp);
	    return(0);
	}
	if(strncmp(buff,"locks",5) == 0)
	{
	    /* see if there is a name before the semicolon */
	    cp = &buff[4];
	    while (*++cp)
	    {
		if(isspace(*cp)) continue;
		if(*cp == ';')  /* no lock */
		{
		    fclose(fp);
		    return(0);
		}
		/* end the string at the semicolon */
		if(cpp = (char *)index(cp,';'))
		{
		    *cpp = '\n';
		    *(cpp+1) = '\0';
		}
		if(!tell) printf("%s: %s",name,cp);
		else printf("%s\n",name);
		fclose(fp);
		return(0);
	    }
	}
    }
}
    

/*
 * mapoverdir(dirname,fcn)
 * char *dirname;
 * int fcn();
 *
 *  open the directory and apply the fcn to all entries
 *  die if the directory can't be opened
 */
mapoverdir(dirname,fcn)
char *dirname;
int (*fcn)();
{
    DIR *dirp;
    struct direct *dir, *readdir();

    if((dirp = opendir(dirname)) == NULL)
    {
	perror(dirname);
	exit(1);
    }
    while((dir = readdir(dirp)) != NULL)
    {
	(fcn)(dir->d_name);
    }
}
/*
 * rcsfilep(filename)
 * char *filename;
 *
 * return TRUE (-1) iff the filename is a valid RCS file (ends with ,v)
 *
 */
rcsfilep(filename)
char *filename;
{
    int len;

    len = strlen(filename);
    if((len > 2) && (filename[len-1] == 'v') && (filename[len-2] == ','))
       return(1);
    else return(0);
}
