/* gcdata.c 					-j k foderaro
 *
 *  This program analyzes the bitmaps produced when the lisp system is
 *  in gc debugging mode.  The analysis provides an insight into the
 *  distribution and lifetime of the lisp data elements.
 *
 *  To use this program you need to first make a lisp run.
 *  (gcstat 0) starts recording the information, it creates the file gc.out
 *		and writes out a header.
 *  you should then do a (gc) to start fresh and sync the lisp system and
 *  gcdata.
 *  Now you do what every computation you want, which should cause a gc or
 *  two (or three or four ...)
 *  Finally, do a (gcstat 1) and the typetable will be dumped out and the
 *  gc.out file closed.
 *
 *  now type
 *  % gcdata gc.out
 *  and the statistics will be printed.
 *  there are these switches
 *  -p    print page by page detailed description of the storage
 *  -iN   ignore data type N when printing histograms of load, life and death.
 *	  to find the correspondence of data type to number N, you should
 * 	  look in h/global.h
 *  -D    don't print distribution graphs.
 */
#include "h/gc.h"
#include <sys/types.h>
#include <sys/vtimes.h>
#define TRUE -1
#define FALSE 0
#define ROUNDUP(x) (((int)(x)+0x3ff) & ~0x3ff)

#define NBPG 512

#define ATOMSPP 25
#define STRSPP NBPG
#define INTSPP 128
#define DTPRSPP 64
#define DOUBSPP 64
#define ARRAYSPP 25
#define SDOTSPP 64
#define VALSPP 128
#define BCDSPP 64

#define HUNK2SPP 64		 /* hunk page sizes */
#define HUNK4SPP 32
#define HUNK8SPP 16
#define HUNK16SPP 8
#define HUNK32SPP 4
#define HUNK64SPP 2
#define HUNK128SPP 1

struct typedes
{    char *name;		/* symbolic character name */
     int   size;		/* size of each data element in bytes */
     int  gcable;		/* TRUE if this is recoverable	*/
     int  itemsperpage;		/* data elements per page	*/
     int  printinfo;		/* print information about	*/
};

/*
 * the data types, in order of type number
 *
 */
#define NUMTYPES 18
/* this data structure contains constants  */
struct typedes types[NUMTYPES] =
{
  { "string ", 1,   FALSE, STRSPP,     FALSE },
  { "atom   ", 5,   TRUE,  ATOMSPP,    FALSE },
  { "fixnum ", 1,   TRUE,  INTSPP,     FALSE }, 
  { "cons   ", 2,   TRUE,  DTPRSPP,    TRUE  },
  { "flonum ", 2,   TRUE,  DOUBSPP,    FALSE },
  { "binary ", 2,   FALSE, BCDSPP,     FALSE },
  { "port   ", 1,   FALSE, 0,          FALSE },
  { "array  ", 5,   TRUE,  ARRAYSPP,   FALSE },	
  { "other  ", 1,   FALSE, NBPG,       FALSE },	
  { "sdot   ", 2,   TRUE,  SDOTSPP,    TRUE  },
  { "value  ", 1,   TRUE,  VALSPP,     FALSE },
  { "hunk2  ", 2,   TRUE,  HUNK2SPP,   FALSE },
  { "hunk4  ", 4,   TRUE,  HUNK4SPP,   FALSE },
  { "hunk8  ", 8,   TRUE,  HUNK8SPP,   FALSE },
  { "hunk16 ", 16,  TRUE,  HUNK16SPP,  FALSE },
  { "hunk32 ", 32,  TRUE,  HUNK32SPP,  FALSE },
  { "hunk64 ", 64,  TRUE,  HUNK64SPP,  FALSE },
  { "hunk128", 128, TRUE,  HUNK128SPP, FALSE }
};

#define TIMMAX 80

/* this structure contains data which is gathers across all gc's */

struct trecd
{
	int acnt[TIMMAX+1],	/* number of cells alive a given amt of time */
	    dcnt[TIMMAX+1],
	    pages;		/* number of pages for this data type */
} typerecd[NUMTYPES];

/* in lifeexp  we maintain a count of the number of cells of each type
 *  which died after being alive for a certain amount of time.
 */  
 
/*
 * DEAD and ALIVE are the last index in the lifeexp array.
 */
#define DEAD 0
#define ALIVE 1

int lifeexp[NUMTYPES] [TIMMAX+1] [2];
#define USCALE 20

/* this data structure contains counts which are zeroed before each
 * gc is checked
 */
struct stypeinfo
{
    int pages, 		/* number of pages allocated	*/
        used,		/* cells used			*/
	free,		/* cells free			*/
	births,		/* cells born			*/
	deaths,		/* cells which died		*/
	alive,		/* cells which remained alive	*/
	dead,		/* cells which remained dead	*/
	allfree;	/* totally free pages		*/
    int aused[USCALE]; /* histogram of % used		*/
    int age[TIMMAX+1];	/* number of cells by age	*/
} typeinfo[NUMTYPES];

struct stypeinfo cleartypeinfo;	/* a zeroed structure */

struct celldata 
{
	int used;	/* TRUE if this cell is used */
	int time;	/* length of time the cell has been in this state */
	int age;	/* number of gcs this datum has been through	*/
};

char *malloc();
char *zmalloc();
char *typetab;
int ttsize;
struct celldata **celldataptr;  /* corresponds with typetab  */

int births,deaths,alive,dead;

int gctime;
int *ipntr;
int user_u,user_s;
int last_maj,last_min;
int thisgctime_u,thisgctime_s,thisusefultime_u,totalgctime_u,totalusefultime_u;
int totalgctime_s;
int thisusefultime_s,totalusefultime_s;
int totalmarktime_u,totalmarktime_s,totalsweeptime_u,totalsweeptime_s;
int gensymcount,markdpcount;
int psc, ppsc;
int conssame, consdiff, consnil;
int sweep_pages,mark_items,sweep_time_u,mark_time_u,sweep_time_s,mark_time_s;

int last_idsrss, last_ixrss;

main(argc,argv)
char **argv;
{
    int fp,i,j,maxv,timelist;
    int recsize,bitmapsize,maxpage,type,used,free;
    int collectablepages;
    int igntype;
    char *recd,*bitmap,*cp;
    char *filetoread = "gc.out";
    double tottime;
    struct vtimes premark,presweep,alldone,*tpnt;
    int opt1;
    struct gchead headr;
    int nodist = 0;

    while(argc-- > 1)
    {
	if(*(cp = argv[1]) == '-')
	while(*++cp)
	{
	    switch(*cp)
	    {
	     case 'p': opt1 = TRUE;
		       break;

	     case 'i':  	/* form is -inumber, ignore type number */
		       igntype = atoi(cp+1);
		       if(igntype < 0 || igntype > 18) 
			 printf("bad number %d", igntype);
		       else 
		       {  printf("ignoring %d\n",igntype);
			  types[igntype].printinfo = FALSE;
		       }
		       cp = "X";  
		       break;
	    case 'D':  nodist = 1;	/* don't print dist stuff */
		       break;
			

		       
	     default: printf("Bad option %c \n",*cp);
	    }
	}
	else filetoread = argv[1];
	argv++;
    }


    if((fp = open(filetoread,0)) < 0)
    {
	perror(filetoread);
	exit(1);
    }

    read(fp,&headr,sizeof(headr));
    printf("file %s, v:%d, base:0x%x (page %d)\n",
		 filetoread,headr.version,headr.lowdata,
		  headr.lowdata >> 9);

    if(headr.version < 4) 
    {
	printf("I only understand version 2 dumps, sorry\n");
	exit(1);
    }
    /* read in type table */
    lseek(fp,-sizeof(ttsize),2);	/* locate size of table */
    read(fp,&ttsize,sizeof(ttsize));
    printf("type table is %d bytes long\n",ttsize);

    typetab = (char *)malloc(ttsize);
    celldataptr = (struct celldata **)zmalloc(ttsize*sizeof(struct celldata *));
    lseek(fp,-(sizeof(ttsize) + ttsize),2);	/* locate beginning of table */
    read(fp,typetab,ttsize);

    lseek(fp,sizeof(headr),0);	/* return to spot after header */
    for(gctime = 1; ; gctime++)
    {
	/* clear counters */
	for(i = 0; i < NUMTYPES ; i++)
	  typeinfo[i] = cleartypeinfo;

	/* process each record */
	read(fp,&recsize,sizeof(recsize));
	printf("record size %d\n",recsize);
	if(recsize == 0) break;
	recd = malloc(ROUNDUP(recsize));
	read(fp,recd,recsize);
	/* the first thing in the record are three tbuffer structures */
	tpnt = (struct vtimes *)recd;

	premark  = *tpnt++;
	presweep = *tpnt++;
	alldone  = *tpnt++;

	ipntr = (int *)tpnt; /* now read some integers */
	gensymcount = *ipntr++;
	if(headr.version > 4) 
	{
	    conssame = *ipntr++;
	    consdiff = *ipntr++;
	    consnil  = *ipntr++;
	}
	markdpcount = *ipntr++;
	/* first thing in record is bit map record which has a size followed
	   by the bit map, 16 bytes per page
	 */
	bitmapsize = *ipntr++;
	printf("GC number %d, bitmapsize = %d, pages = %d\n",gctime,bitmapsize,
			   maxpage = bitmapsize/16);
	printf(" gensyms = %d, calls to marker = %d\n",gensymcount,markdpcount);
	tottime = (float) (alldone.vm_utime + alldone.vm_stime);
	printf(" after gc rss: text %f , d+s %f , max %d\n",
		 alldone.vm_ixrss/tottime,
		 alldone.vm_idsrss/tottime,
		 alldone.vm_maxrss);
	last_ixrss = alldone.vm_ixrss;
	last_idsrss = alldone.vm_idsrss;
	printf("  state          times                   faults\n");
	printf("            user        sys         major         minor       \n");
	printf(" initial %5d (%4d) %5d (%4d) %5d (%4d) %5d (%4d)\n",
		 premark.vm_utime,premark.vm_utime-user_u,
		 premark.vm_stime,premark.vm_stime-user_s,
		 premark.vm_majflt, premark.vm_majflt - last_maj,
		 premark.vm_minflt, premark.vm_minflt - last_min
		 );
	printf(" mark    %5d (%4d) %5d (%4d) %5d (%4d) %5d (%4d)\n sweep   %5d (%4d) %5d (%4d) %5d (%4d) %5d (%4d)\n\n",
		 presweep.vm_utime, 
   mark_time_u = presweep.vm_utime-premark.vm_utime,
		 presweep.vm_stime,
   mark_time_s = presweep.vm_stime-premark.vm_stime,
		 presweep.vm_majflt,
		 presweep.vm_majflt-premark.vm_majflt,
		 presweep.vm_minflt,
		 presweep.vm_minflt-premark.vm_minflt,
		 alldone.vm_utime,
  sweep_time_u = alldone.vm_utime-presweep.vm_utime,
		 alldone.vm_stime,
  sweep_time_s = alldone.vm_stime-presweep.vm_stime,
		 alldone.vm_majflt,
		 alldone.vm_majflt-presweep.vm_majflt,
		 alldone.vm_minflt,
		 alldone.vm_minflt-presweep.vm_minflt
		 );

	/* calculate useful time */
	if(gctime == 1)
	{
	    user_u = alldone.vm_utime;
	    user_s = alldone.vm_stime;
	    thisgctime_u = alldone.vm_utime - premark.vm_utime;
	    thisgctime_s = alldone.vm_stime - premark.vm_stime;
	    printf(" Initial gc time: %du+%ds\n",thisgctime_u,thisgctime_s);
	}
	else
	{
	    thisusefultime_u = premark.vm_utime - user_u;
	    thisusefultime_s  = premark.vm_stime - user_s;
	    thisgctime_u = alldone.vm_utime - premark.vm_utime;
	    thisgctime_s = alldone.vm_stime - premark.vm_stime;
	    user_u = alldone.vm_utime;
	    user_s = alldone.vm_stime;

	    totalusefultime_u += thisusefultime_u;
	    totalusefultime_s += thisusefultime_s;
	    totalgctime_u     += thisgctime_u;
	    totalgctime_s     += thisgctime_s;
	    totalmarktime_u   += mark_time_u;
	    totalmarktime_s   += mark_time_s;
	    totalsweeptime_u   += sweep_time_u;
	    totalsweeptime_s   += sweep_time_s;

	    printf(" for this segment: useful time: %du+%ds, gc time: %du+%ds, pct gc: %d%%\n",
		     thisusefultime_u,thisusefultime_s,
		     thisgctime_u,thisgctime_s,
		     (100 * (thisgctime_u + thisgctime_s) 
			  / (thisusefultime_u + thisusefultime_s  + 
					      thisgctime_u + thisgctime_s)));
	   printf(" In total: useful time %du+%ds, gc time %du+%ds, pct gc: %d%%\n",
		    totalusefultime_u,totalusefultime_s,
		    totalgctime_u,totalgctime_s,
		    100*(totalgctime_u + totalgctime_s)
		    /(totalusefultime_u + totalusefultime_s +
					totalgctime_u + totalgctime_s));
	   printf(" 	   mark time %du+%ds, sweep time %du+%ds\n",
			   totalmarktime_u,totalmarktime_s,
			   totalsweeptime_u,totalsweeptime_s);

	}

	if(headr.version > 4) 
	   printf(" cons cdr to same page: %d, to different page: %d, to nil: %d\n",
		    conssame, consdiff, consnil);

	last_maj = alldone.vm_majflt;
	last_min = alldone.vm_minflt;
	collectablepages = 0;

	for(i=0, bitmap = (char *)ipntr; 
		 i < maxpage ; i++, bitmap += 16)
	{
	   type = typetab[i];
	   typeinfo[type].pages++;
	   used = free = -1;
	   if(types[type].gcable)
	   {
	     collectablepages++;
	     if(!celldataptr[i])
	       celldataptr[i] = (struct celldata *)
				zmalloc(types[type].itemsperpage *
						sizeof(struct celldata));
	     births = deaths = alive = dead = 0;
	     analbitmap(bitmap,i,&used,&free);
	     typeinfo[type].used += used;
	     typeinfo[type].free += free;
	     typeinfo[type].births += births;
	     typeinfo[type].deaths += deaths;
	     typeinfo[type].alive += alive;
	     typeinfo[type].dead += dead;
	     typeinfo[type].aused[(int)((USCALE - 1.0)*used/(used+free))]++;
	     if(used == 0) typeinfo[type].allfree++;
	     if(opt1) 
	     {
		printf("[%3d] %s ",i,types[type].name);
		printf(" uf:%2d %2d bd:%2d %2d ad:%2d %2d ",
			 used,free,births,deaths,alive,dead);
	        histogram(used,used+free);
	    }
	   }
	}

	printf(" == there are %d collectable pages ==\n",collectablepages);
	printf("Summary by type\n");
	sweep_pages = mark_items = 0;
	for(i=0; i < NUMTYPES ; i++)
	{
	    if(typeinfo[i].pages > 0)
	    {
		printf("  %s %3d pages (+%3d)",
			  types[i].name,typeinfo[i].pages,
			  typeinfo[i].pages - typerecd[i].pages);
		if(types[i].gcable)
		{
		    sweep_pages += typeinfo[i].pages;
		    mark_items  += typeinfo[i].used;
		    printf("  uf:%5d %5d bd:%5d %5d ad:%5d %5d",
				  typeinfo[i].used,
				  typeinfo[i].free,
				  typeinfo[i].births,
				  typeinfo[i].deaths,
				  typeinfo[i].alive,
				  typeinfo[i].dead);
		}
		putchar('\n');
		psc = typeinfo[i].pages - typeinfo[i].allfree
		       - ( (typeinfo[i].used + types[i].itemsperpage - 1)/
			     types[i].itemsperpage);
		ppsc = 100 * psc / (1.0 * typeinfo[i].pages);
		printf("     %s psc = %d, = %d%%\n", types[i].name, psc, ppsc);
		typerecd[i].pages = typeinfo[i].pages;
	    }
	}
	/* 
	 * calculate the time taken for sweep and marking
	 */

	printf(" mark cost: %f secs/item,  sweep cost %f secs/page\n",
		 (mark_time_u / 60.0)/mark_items,
		 (sweep_time_u / 60.0)/sweep_pages
		 );

	/* print out life expectencies */
	for(i=0; i < NUMTYPES ; i++)
	{
	   if(types[i].printinfo)
	   {
	       int j, lim;
	       for( lim = TIMMAX ; lim >= 0; lim--)
	       {
		   if(lifeexp[i][lim][ALIVE] || lifeexp[i][lim][DEAD])
		      break;
	       }
	       if(lim >= 0)
	       {
		   printf("life expectency: %s\n",types[i].name);
		   printf("age | died  -- alive\n");
		   for( j = 0; j <= lim ; j++)
		   {
		       printf("%2d  | %5d    %5d   %f %% alive\n",
		           j,lifeexp[i][j][DEAD],
		           lifeexp[i][j][ALIVE],
		           lifeexp[i][j][ALIVE]* 100.0/
			   max(lifeexp[i][j][ALIVE]+lifeexp[i][j][DEAD],1));
		   }
		   printf(" ------------------\n\n");
	       }
	   }
	}
	    

	if(nodist) goto skipdist;
	/* 
	 * we print out next a histogram of the number of pages 
	 * which are a given percent full.  Only those pages which
	 * have a significant number of pages allocated are listed.
	 * significant in this case means more than 80
	 */
	printf("\n   === distribution of load ===\n");
	for(i=0; i < NUMTYPES ; i++)
	{
	    if(types[i].printinfo && (typeinfo[i].pages > 10))
	    {
		maxv = maxvector(&typeinfo[i].aused[0],USCALE);
		printf("\n %%used  Type %s --------------------\n",
			   types[i].name);
		for(j=0 ; j < USCALE ; j++)
		{
		    printf("%2d [%3dpg] ",100*j/USCALE,typeinfo[i].aused[j]);
		    histogram(typeinfo[i].aused[j],maxv);
		}
		printf("-----------------------------------------\n");
	    }
	}

	timelist = (gctime < TIMMAX ? gctime : TIMMAX);

	printf("\n   === distribution of age ===\n");
	for(i=0; i < NUMTYPES ; i++)
	{
	    if(types[i].printinfo && (typeinfo[i].pages > 40))
	    {
		maxv = maxvector(&typeinfo[i].age[0],TIMMAX+1);
		printf("\n age [count] Type %s --------------------\n",
			   types[i].name);
		for(j=0 ; j <= timelist ; j++)
		{
		    printf("%2d [%5d] ",j,typeinfo[i].age[j]);
		    histogram(typeinfo[i].age[j],maxv);
		}
		printf("-----------------------------------------\n");
	    }
	}
	printf("\n   === distribution of life ===\n");
	for(i=0; i < NUMTYPES ; i++)
	{
	    if(types[i].printinfo && (typeinfo[i].pages > 40))
	    {
		maxv = maxvector(&typerecd[i].acnt[1],TIMMAX);
		if(maxv == 0) continue;		/* no data */
		printf("\n time [count]  Type %s --------------------\n",
			   types[i].name);
		for(j=1 ; j <= timelist ; j++)
		{
		    printf("%2d [%5d] ",j,typerecd[i].acnt[j]);
		    histogram(typerecd[i].acnt[j],maxv);
		}
		printf("-----------------------------------------\n");
	    }
	}

	printf("\n   === distribution of death ===\n");
	for(i=0; i < NUMTYPES ; i++)
	{
	    if(types[i].printinfo && (typeinfo[i].pages > 40))
	    {
		maxv = maxvector(&typerecd[i].dcnt[1],TIMMAX);
		if(maxv == 0) continue;		/* no data */
		printf("\n time [count]  Type %s --------------------\n",
			   types[i].name);
		for(j=1 ; j <= timelist ; j++)
		{
		    printf("%2d [%5d] ",j,typerecd[i].dcnt[j]);
		    histogram(typerecd[i].dcnt[j],maxv);
		}
		printf("-----------------------------------------\n");
	    }
	}
	skipdist: ;
    /* free(recd); */
    }

}


/* analyze the bitmap given which is associated with page pagenum
   and return  the number of free and used cells.
 */
analbitmap(bitmap,pagenum,usedval,freeval)
int bitmap[];
int *usedval,*freeval;
{
	int bvalue,bits,freecnt,usedcnt,type,itemstogo,len,Age;
	struct celldata *cdptr;
    
	bits = 32;			/* number of bits per word */
	freecnt = usedcnt = 0;
	len = types[type = typetab[pagenum]].size;
	itemstogo = types[type].itemsperpage;
	cdptr = celldataptr[pagenum];

	bvalue = *bitmap++;
	/* printf("bv:%x ",bvalue); */
	while(TRUE)
	{
		if((Age = cdptr->age) >= TIMMAX) Age = TIMMAX;
		typeinfo[type].age[Age]++;
		(cdptr->age)++;
		  
		if(!(bvalue & 1))	/* if data element is not marked */
		{
		    freecnt++;
		    if(cdptr->used)
		    { 
		      lifeexp[type][1+cdptr->time][DEAD]++; /* alive 2 dead */
		      deaths++;
		      cdptr->used = FALSE;
		      cdptr->time = 0;  /* freshly dead			*/
		    }
		    else 
		    {  
			dead++;
			if(gctime != 1)	  /* remove possibility for false
					     dead counts on the first gc */
			{
		            lifeexp[type][0][DEAD]++;	/* dead 2 dead */
			    (cdptr->time)++;
			    if(cdptr->time >= TIMMAX)
			       typerecd[type].dcnt[TIMMAX]++;
			    else typerecd[type].dcnt[cdptr->time]++;

			    typerecd[type].dcnt[(cdptr->time)-1]--;
			}
		    }
		}
		else 			/* if data element is marked */
		{
		    usedcnt++;
		    if(!cdptr->used)
		    {
		        if(gctime != 1)	/* don't count initial gc */
			  lifeexp[type][0][ALIVE]++;
			births++;
			cdptr->used = TRUE;
			cdptr->time = 0;	/* just was born */
		    }
		    else 
		    {
			/* alive 2 alive */
			lifeexp[type][1+cdptr->time][ALIVE]++;
			alive++;
			(cdptr->time)++;
			if(cdptr->time >= TIMMAX)
			   typerecd[type].acnt[TIMMAX]++;
			else typerecd[type].acnt[cdptr->time]++;

			typerecd[type].acnt[(cdptr->time)-1]--;
		    }
		}
		cdptr++;

		if( --itemstogo <= 0 ) 
		{    
		     break;
		}

		/* shift over mask by number of words in data type */

		if( (bits -= len) > 0)
		{  bvalue = bvalue >> len;
		} 
		else if( bits == 0 ) 
		{  bvalue = *bitmap++;
		/* printf("bv:%x ",bvalue); */
		   bits = 32;
		}
		else
		{  bits = -bits;
		   while( bits >= 32) { bitmap++;
					bits -= 32;
				      }
		   bvalue = *bitmap++;
		   /* printf("bv:%x ",bvalue);  */
		   bvalue = bvalue >> bits;
		   bits = 32 - bits;;
		}
	}

	*freeval = freecnt;
	*usedval = usedcnt;
}

/*
 * zmalloc
 *  allocate a section of memory and zero it 
 */
char *
zmalloc(size)
{
    char *retval, *cp;
    int i;
    cp =  retval = (char *)malloc(size);
    for( i = 0; i < size; i++)
      *cp++ = '\0';
    return(retval);
}

/*
 *   histogram
 * given two integers, it prints a list of stars corresponding to the
 * magnitude of the quotient of the two integers.  
 */
char *stars = "******************************";
histogram(amt,total)
{
    int scaled;

    scaled = (int)( (30.0 * amt) / total);
    printf("|%s\n",stars+(30-scaled));
}

/* maxvector
 *  given an array of ints, and the length of that array, it returns
 * the maximum value
 */
maxvector(arr,numb)
int *arr;
{
    int i,max = 0;
    for(i=0 ; i < numb ; i++)
    {
	if(arr[i] > max) max = arr[i];
    }
    return(max);
}

max(a,b)
int a,b;
{
    if (a > b) return(a); else return(b);
}