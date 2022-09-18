/*
 * Basic output filter for the 4.2 spooling system
 * 
 * Write out the banner (the input) into .banner for the input filter.
 * The input filter can then print it out if it wants.
 *
 * Note: Do a sigstop on self when we see ^Y^A which denotes end of job.
 * exiting is the WRONG thing to do at this point.
 *
 * Copyright (c) 1985, 1987 by The Trustees of Columbia University in the City
 *  of New York
 *
 * Author: Charlie C. Kim
*/

#include <stdio.h>
#include <signal.h>

#ifdef BANNERFIRST
# ifndef BANNER
#  define BANNER
# endif
#endif

#ifdef BANNERLAST
# ifndef BANNER
#  define BANNER
# endif
#endif

#ifdef CHARGEBANNER
# ifndef BANNER
#  define BANNER
# endif
#endif

#ifdef BANNERFILE
# ifndef BANNER
#  define BANNER
# endif
#endif
#ifndef BANNERFILE
# define BANNERFILE ".banner"
#endif

FILE *bannerfile;

char buf[BUFSIZ];

main()
{
  int c, cl, i;
  int dosusp;

  while (1) {
#ifdef BANNER
    if ((bannerfile = fopen(BANNERFILE, "w")) < 0) {
      perror("Can't open .banner");
      exit(8);
    }
    psbannerstart(bannerfile);
#endif
    cl = -1, c = -1, dosusp = 0;
    do {
#ifdef BANNER
      for ( i = 0; i < BUFSIZ ; i++) {
#endif
	cl = c;
	c = getchar();
#ifdef BANNER
	buf[i] = c;
#endif
	if (cl == '\031' && c == '\01') {
	  dosusp = 1;
	  break;
	}
#ifdef BANNER
	if (c == EOF)
	  break;
	if (c == '\n')
	  break;
      }
      buf[i] = '\0';
      if (dosusp) 
	break;
      if (c != EOF || i != 0)
	psbannerline(bannerfile,buf);
#endif
    } while (c != EOF && !dosusp);
#ifdef BANNER
    psbannerend(bannerfile);
    fclose(bannerfile);	/* close off file here - end of job */
#endif
    if (c == EOF)
      break;
#ifdef DEBUG
    fprintf(stderr,"Waiting for next job...");
#endif DEBUG
    kill(getpid(), SIGSTOP);
  }
}

#ifdef BANNER
psbannerstart(fd)
FILE *fd;
{
  fputs("%!\n", fd);
  fputs("/fs 8 def\n", fd);
  fputs("/Courier findfont fs scalefont setfont\n", fd);
  fputs("/vpos 72 10 mul def\n", fd); /*  at 10 inches .5 inch margin */
  fputs("/LS {36 vpos moveto show /vpos vpos fs sub def} def\n", fd);
}

psbannerline(fd,line)
FILE *fd;
unsigned char *line;
{
  int l = strlen(line);
  static char spaces[] = "        ";
  int i, pos;
  unsigned char c;

  if (line[0] == '\f')
    return;
  putc('(', fd);
  for (i = 0,pos=0; i < l ; pos++, i++) {
    c = *line++;
    if (c != '\t')
      if (c < ' ' || c > '\177')
	c = '\267';
    switch (c) {
    case '(':
      fputs("\\(",fd);
      break;
    case ')':
      fputs("\\)",fd);
      break;
    case '\\':
      fputs("\\\\",fd);
      break;
    case '\t':
      fputs((pos%8) ? spaces+(pos % 8) : spaces, fd);
      pos += (8 - (pos % 8)) - 1;
      break;
    default:
      putc(c, fd);
      break;
    }
  }
  fputs(") LS\n", fd);
}

psbannerend(fd)
FILE *fd;
{
  fputs("showpage\n", fd);  
}

#endif
