/*
 *  Author: cck    Date: 88/03/28 17:24:12  
 *  Header: afpudb.c,v 1.9 88/03/28 17:24:12 cck Rel  
 *  Revision: 1.9  
*/

/*
 * afpudb.c - Appletalk Filing Protocol Unix Finder Information
 *  database.
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  August 1987     CCKim	Created.
 *
 */
#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>
#endif
#include <sys/file.h>
#include <sys/stat.h>
#include <netat/appletalk.h>
#include "afpudb.h"
#ifdef NEEDFCNTLDOTH
# include <fcntl.h>
#endif

#ifdef bsd
# define BSDSYSTEM
#endif

#ifdef bsd4_2
# define BSDSYSTEM
#endif

/*
 * Deal with unix file types
 *
*/

/* This is the "file" icon - generic for unix files */
private byte unix_text[] = {
  0x0f,0xff,0xfc,0x00,		/*     XXXXXXXXXXXXXXXXXX           */
  0x08,0x00,0x06,0x00,		/*     X                XX          */
  0x08,0x00,0x05,0x00,		/*     X                X X         */
  0x08,0x00,0x04,0x80,		/*     X                X  X        */
  0x08,0x00,0x04,0x40,		/*     X                X   X       */
  0x08,0x0c,0x04,0x20,		/*     X       XX       X    X      */
  0x09,0xf8,0x87,0xf0,		/*     X  XXXXXX   X    XXXXXXX     */
  0x0b,0xf9,0xc0,0x10,		/*     X XXXXXXX  XXX         X     */
  0x08,0x9b,0xe0,0x10,		/*     X   X  XX XXXXX        X     */
  0x09,0x29,0x84,0x50,		/*     X  X  X X  XX    X   X X     */
  0x0b,0x29,0x84,0x50,		/*     X XX  X X  XX    X   X X     */
  0x0b,0x29,0x85,0x50,		/*     X XX  X X  XX    X X X X     */
  0x0b,0x69,0x85,0x50,		/*     X XX XX X  XX    X X X X     */
  0x0b,0x69,0x85,0x50,		/*     X XX XX X  XX    X X X X     */
  0x0b,0x49,0x85,0x50,		/*     X XX X  X  XX    X X X X     */
  0x0b,0x89,0x85,0x50,		/*     X XXX   X  XX    X X X X     */
  0x09,0x8b,0xa5,0x10,		/*     X  XX   X XXX X  X X   X     */
  0x09,0xfe,0xc5,0x50,		/*     X  XXXXXXXX XX   X X X X     */
  0x08,0x7c,0xc0,0x10,		/*     X    XXXXX  XX         X     */
  0x08,0x00,0x00,0x10,		/*     X                      X     */
  0x08,0x40,0x44,0x50,		/*     X    X       X   X   X X     */
  0x09,0x54,0x45,0x50,		/*     X  X X X X   X   X X X X     */
  0x09,0x55,0x55,0x50,		/*     X  X X X X X X X X X X X     */
  0x09,0x51,0x55,0x50,		/*     X  X X X   X X X X X X X     */
  0x09,0x55,0x55,0x50,		/*     X  X X X X X X X X X X X     */
  0x09,0x55,0x55,0x50,		/*     X  X X X X X X X X X X X     */
  0x09,0x15,0x14,0x50,		/*     X  X   X X X   X X   X X     */
  0x09,0x55,0x54,0x10,		/*     X  X X X X X X X X     X     */
  0x09,0x41,0x50,0x10,		/*     X  X X     X X X       X     */
  0x08,0x00,0x00,0x10,		/*     X                      X     */
  0x08,0x00,0x00,0x10,		/*     X                      X     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  /* mask */
  0x0f,0xff,0xfc,0x00,		/*     XXXXXXXXXXXXXXXXXX           */
  0x0f,0xff,0xfe,0x00,		/*     XXXXXXXXXXXXXXXXXXX          */
  0x0f,0xff,0xff,0x00,		/*     XXXXXXXXXXXXXXXXXXXX         */
  0x0f,0xff,0xff,0x80,		/*     XXXXXXXXXXXXXXXXXXXXX        */
  0x0f,0xff,0xff,0xc0,		/*     XXXXXXXXXXXXXXXXXXXXXX       */
  0x0f,0xff,0xff,0xe0,		/*     XXXXXXXXXXXXXXXXXXXXXXX      */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0,		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
  0x0f,0xff,0xff,0xf0		/*     XXXXXXXXXXXXXXXXXXXXXXXX     */
};

#ifdef SMART_UNIX_FINDERINFO
/* other icons */
#endif

#define FNDR_NOFNDR 0
#define FNDR_DEF 1
#define FNDR_DEVICE 2
#define FNDR_SOCKET 3
#ifdef SMART_UNIX_FINDERINFO
#define FNDR_BIN 4
#define FNDR_UPGM 5
#define FNDR_UOBJ 6
#define FNDR_ARCHIVE 7
#define FNDR_CPIO 8
#define FNDR_LOCKED 9
#endif

struct ufinderdb uf[] = {
#define deffinfo(c1,c2,c3,c4,com,icon) {{(c1),(c2),(c3),(c4)}, \
					  (com), sizeof(com)-1, \
					  (icon), sizeof((icon))}
  {{0, 0, 0, 0}, ""},
  deffinfo('T','E','X','T', "This is a Unix\252 created file", unix_text),
  deffinfo('D','E','V',' ', "This is a Unix\252 device", NULL),
  deffinfo('S','K','T',' ', "This is a Unix\252 socket", NULL),
#ifdef SMART_UNIX_FINDERINFO
  deffinfo('D','A','T','A', "This is a Unix\252 binary file", NULL),
  deffinfo('P','G','R','M', "This is a Unix\252 program", NULL),
  deffinfo('O','B','J',' ', "This is a Unix\252 object file", NULL),
  deffinfo('A','R',' ',' ', "This is a Unix\252 archive file", NULL),
  deffinfo('C','P','I','O', "This is a Unix\252 cpio file", NULL),
  deffinfo('L','C','K','D', "This file is not readable", NULL)
#endif
};

export int uf_len = sizeof(uf)/sizeof(struct ufinderdb);

int
os_getunixtype(path, stb)
char *path;
struct stat *stb;
{
#ifdef SMART_UNIX_FINDERINFO
  char buf[BUFSIZ];
  int i, fd;
#endif

  if ((stb->st_mode & S_IFMT) == S_IFDIR) /* a directory? */
    return(FNDR_NOFNDR);

  switch (stb->st_mode & S_IFMT) {
  case S_IFCHR:
  case S_IFBLK:
    /* super wanky thing to do would be to return an type */
    /* based upon the device type */
    return(FNDR_DEVICE);
    break;
  case S_IFSOCK:
    return(FNDR_SOCKET);
    break;
  }

#ifdef SMART_UNIX_FINDERINFO
  if ((fd=open(path,O_RDONLY)) < 0)
    return(FNDR_DEF);
  if ((i = read(fd, buf, BUFSIZ)) <= 0) {
    (void)close(fd);		/* ignore error here */
    return(FNDR_DEF);
  }
  (void)close(fd);		/* ignore error here */
  switch (*(int *)buf) {
#ifdef BSDSYSTEM
  case 0413:
  case 0410:
  case 0411:
  case 0407:
    return(FNDR_UPGM);
  case 0177555:
  case 0177545:
    return(FNDR_ARCHIVE);
#endif
  case 070707:
    return(FNDR_CPIO);
  }
#ifdef BSDSYSTEM
  if (strncmp(buf, "!<arch>\n", sizeof("!<arch>\n")-1) == 0)
    return(FNDR_ARCHIVE);
#endif
#ifndef BIN_FUZZ
# define BIN_FUZZ BUFSIZ/2
#endif
  for (i = 0; i < BIN_FUZZ; i++)
    if (buf[i] & 0x80)
      return(FNDR_BIN);
#endif
  return(FNDR_DEF);
}

int
os_issmartunixfi()
{
#ifdef SMART_UNIX_FINDERINFO
  return(1);
#else
  return(0);
#endif
}
