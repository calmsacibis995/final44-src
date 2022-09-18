/*
 *  Author: cck    Date: 88/05/13 09:19:18  
 *  Header: afpos.c,v 1.81 88/05/13 09:19:18 cck Rel  
 *  Revision: 1.81  
*/

/*
 * afpos.c - Appletalk Filing Protocol OS Interface. 
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1987     Schilit	Created.
 *  March 1988     CCKIM cleanup
 *
 */

/*
 * POSSIBLE DEFINES:
 *
 *  NONLXLATE
 *   Define to turn off translation of \n to \r on line at a time
 *    reads
 *  USECHOWN
 *   System allows user to use chown to give away file ownership
 * Following are used to get volume information
 *  USEGETMNT - DECs getmnt call.  Works for either Ultrix 1.2, 2.0 or
 *   2.2 (to be verified).  Call differs from 2.0 to 2.2
 *  USEQUOTA - base volume information on quota for user on file
 *   system if it exists (messed up by symlinks off the structure).
 *   This is for the "Melbourne" quota system as usually found in BSD
 *   systems.
 *  USESUNQUOTA - running with sun quota system.  Basically, just turns on 
 *   emulation of the Melbourne quota call
 *  USEUSTAT - not recommended.  returns information about file, but
 *   information doesn't tell us how much space is there -- only
 *   how much is free and we need both
 *  USESTATFS - statfs is the Sun NFS solution to volume information.
 *
 *  aux has a couple of "ifdefs".
 *   - one to set full BSD compatibility
 *   - one to protect against rename("file1","file1"): it will
 *     incorrectly unlink "file1" (period - nothing left afterwards)
 *
 *  OTHER: GGTYPE
 *   Some versions of unix return a gid_t array in getgroups instead of
 *    an int array.  For those, define GGTYPE to gid_t.  In particular,
 *    this is a problem with (at least some version of) "MORE/BSD"
 *    from Mt. Xinu. 
 *
 * System V defines
 *  NOLSTAT - no lstat call - don't try to figure out things with symlinks
 *  USERAND - use sysv rand call not bsd random
*/

#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>		/* assume included by param.h */
#endif
#include <sys/file.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <netat/appletalk.h>
#include <sys/time.h>
#ifdef aux
# include <compat.h>
#endif

#ifdef USESUNQUOTA
# ifndef USEQUOTA
#  define USEQUOTA
# endif
#endif

#ifdef NEEDFCNTLDOTH
# include <fcntl.h>
#endif
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif

#ifdef USEUSTAT
# include <ustat.h>
#endif

#ifdef USESTATFS
# include <sys/vfs.h>
#endif


#ifdef USEQUOTA
# ifndef USESUNQUOTA
#  include <sys/quota.h>
/* NOTE: If there is not sys/quota.h and there is a ufs/quota.h */
/* then you should probably define SUN_QUOTA -- especially if your */
/* NFS is based on the sun model */
# else
#  include <mntent.h>
#  include <ufs/quota.h>
# endif
# ifndef Q_GETDLIM
#  ifdef Q_GETQUOTA
#   define Q_GETDLIM Q_GETQUOTA
#  else
    You have turned on quotas and aren't using the bsd or sun quota system
#  endif /*Q_GETQUOTA*/
# endif /* Q_GETDLIM */
#endif /* USEQUOTA */

/* assumes that ultrix 1.1 doesn't have getmnt or if it does, then it */
/* has limits.h and uname */
#ifdef USEGETMNT
# include <sys/mount.h>
/* the following assumes ultrix 1.2 or above */
/* well, do you really think dec would license their code to another */
/* vendor :-) */
# include <limits.h>
# include <sys/utsname.h>
#endif

#include <netat/afp.h>
#include <netat/afpcmd.h>		/* flags should be in misc  */
#include "afps.h"			/* common includes */
#include "afpvols.h"
#include "afppasswd.h"			/* in case we are using privates */
#include "afposncs.h"
#include "afpgc.h"

#ifdef MAXBSIZE
# define IOBSIZE MAXBSIZE	/* set to max buf entry size by if there */
#else
# ifdef BLKDEV_IOSIZE
#  define IOBSIZE BLKDEV_IOSIZE	/* set to std block device read size */
# else
#  define IOBSIZE BUFSIZ	/* use stdio bufsiz */
# endif
#endif

#define NILPWD ((struct passwd *) 0)

/* macro to test for directory file */

#define	S_ISDIR(mode)	(((mode) & S_IFMT) == S_IFDIR)

#define E_IOWN 0x80000000	/* owner of file */

#define I_RD 04			/* Internal (Unix) bits for read */
#define I_WR 02			/*  write */
#define I_EX 01			/*  execute (search) */

#define E_RD 02			/* External bits for read */
#define E_WR 04			/*  write */
#define E_SR 01			/*  search */

#define IS_OWNER 6		/* internal owner shift amount */
#define IS_GROUP 3		/* internal group shift amount */
#define IS_WORLD 0		/* internal world shift amount */

#define ES_USER 24		/* external user shift amount */
				/*  which is a calculated access based on: */
#define ES_WORLD 16		/* external world shift amount */
#define ES_GROUP 8		/* external group shift amount */
#define ES_OWNER 0		/* external owner shift amount */

/* Mask search (is unix execute) bits for world, group and owner */

#define IS_EX_WGO ((I_EX << IS_OWNER) | \
		   (I_EX << IS_GROUP) | \
		   (I_EX << IS_WORLD))

private char *usrnam,*usrdir;
private int usruid;
private int usrgid;
private int ngroups;
#ifndef GGTYPE
# define GGTYPE int
#endif
private GGTYPE groups[NGROUPS+1];
#ifdef USEGETMNT
# ifndef NOSTAT_ONE
/* no big deal if this changes, it just means you can't compile under */
/* ultrix 2.0/1.2 for ultrix 2.2 (you probably can't for 1.2 anyway) */
/* WARNING: not 100% sure that there aren't other problems preventing */
/* a compile from ultrix 2.0 from working on 2.2 */
#  define NOSTAT_ONE 4		/* as of ultrix 2.2 */
#  define ISOLDGETMNT 1
# else
#  define ISOLDGETMNT 0
# endif
private int oldgetmnt = ISOLDGETMNT; /* use new or old format getmnt */
				/* default is based on compiling system */
#define NUMGETMNTBUF NMOUNT	/* 8 before, let's not be conservative */
				/* because on systems with many file */
				/* systems we will get killed with 8 */
#endif

import int errno;

/*
 * AFPOS functions
 *
 *  Generally, a name like: OSXxxxx means that it is a "primary" function
 *   that accomplishes a afp command (not always though).
 *
*/

export int OSEnable();
export void tellaboutos();
export OSErr OSMapID();
export OSErr OSMapName();
export OSErr OSDelete();
private OSErr os_rmdir();
private OSErr os_delete();
export OSErr OSRename();
export OSErr OSMove();
private OSErr os_move();
export OSErr OSFlush();
export OSErr OSFlushFork();
export OSErr OSClose();
export OSErr OSRead();
export OSErr OSWrite();
export OSErr OSCreateDir();
private OSErr os_mkdir();
export OSErr OSCreateDir();
export OSErr OSFileDirInfo();
export OSErr OSDirInfo();	/* from old spec */
export OSErr OSFileInfo();	/* from old spec */
export void OSValidateDIDDirInfo();
export OSErr OSFileExists();
export OSErr OSSetFileDirParms();
export OSErr OSSetFileParms();
export OSErr OSSetDirParms();
export OSErr OSSetForklen();
private OSErr os_chmod();
private void os_chmod_all();
private u_short EtoIPriv();
private int OSInGroup();
private u_short EtoIAccess();
private dword ItoEPriv();
private dword ItoEAccess();
export OSErr OSAccess();
export OSErr OSVolInfo();
#ifdef USEGETMNT
private OSErr ultrix_volinfo();
#endif
export OSErr OSCopyFile();
private OSErr os_copy();
export OSErr OSCreateFile();
export OSErr OSOpenFile();
export boolean setguestid();
export boolean setpasswdfile();
export OSErr OSLoginRand();
export OSErr OSLogin();
export word OSRandom();
export sdword CurTime();	/* current time in internal form */
export char *tilde();		/* tilde expansion */
export char *logdir();		/* user login directory */
private OSErr unix_rmdir();
private OSErr unix_unlink();
private OSErr unix_rename();
private OSErr unix_open();
private OSErr unix_close();
private OSErr unix_mkdir();
private OSErr unix_create();
private OSErr unix_createo();
private OSErr unix_chown();
private OSErr unix_chmod();
private OSErr unix_stat();
private OSErr ItoEErr();
private int filemode();
private char *syserr();

/*
 * Enable OS Dependent functions
 *
 * For now: under AUX, set full BSD compatibility
 * under sun quota systems, build a mount table for use in quota call
 *
*/
export int
OSEnable()
{
#ifdef USEGETMNT
  struct utsname unames;
#endif

#ifdef USEGETMNT
  if (uname(&unames) >= 0) {
    /* don't think getmnt was available in ultrix 1.1.  If it was */
    /* then we assume it had uname too */
    if (strcmp(unames.sysname, "ULTRIX-32") == 0) {
      if (strcmp(unames.release, "2.0") == 0 ||
	  strcmp(unames.release, "1.2") == 0 ||
	  strcmp(unames.release, "1.1")) {
	oldgetmnt = TRUE;
      } else oldgetmnt = FALSE;
    }
  }
#endif /* USEGETMNT */
#ifdef aux
/* ensure reliable signals, etc */
#define BSDCOMPAT COMPAT_BSDNBIO|COMPAT_BSDPROT|COMPAT_BSDSIGNALS|\
COMPAT_BSDTTY|COMPAT_EXEC|COMPAT_SYSCALLS
  setcompat(BSDCOMPAT);
#endif
#ifdef USESUNQUOTA
  build_mount_table();
#endif
}

void
tellaboutos()
{
  int haveflock;
  int havelockf;

  log("CONFIGURATION");
  getlockinfo(&haveflock, &havelockf);
  if (haveflock)
    log(" Configured: FLOCK");
  if (havelockf)
    log(" Configured: LOCKF");
#ifdef USEUSTAT
  log(" Configured: Volume space information: ustat");
#endif
#ifdef USESTATFS
  log(" Configured: Volume space information: statfs");
#endif
#ifdef USEGETMNT
  log(" Configured: Volume space information: getmnt");
  if (oldgetmnt)
    log("   using old style (Ultrix 1.2, 2.0) getmnt");
#endif
#ifdef USESUNQUOTA
  log(" Configured: SUN quota system");
#endif
#ifndef USESUNQUOTA
/* sunquota turns on usequota */
# ifdef USEQUOTA
  log(" Configured: Melbourne (BSD) quota system");
# endif
#endif
#ifdef USECHOWN
  log(" Configured: chown: system allows one to give away ownership of files");
#endif
  if (os_issmartunixfi())
    log(" Configured: reading unknown unix files to get finder information");
  log(" Configured translation tables are:");
  ncs_table_dump();
}

/*
 * OwnerID = 0 means that the folder is "unowned" or owned by
 * <any user>.  The owner bit of the User Rights summary is always 
 * set for such a folder.
 *
 * GroupID = 0 means that the folder has no group affiliation; hence
 * the group's access privileges (R, W, S) are ignored for such a
 * folder.
 *
*/

#define NOID (-1)			/* unused internal group/user id */

#define ItoEID(iid) ((sdword) (iid == 0 ? NOID : iid))
#define EtoIID(eid) ((int) (eid == NOID ? 0 : eid))

/*
 *
 * OSErr OSMapID(byte fcn,char *name,dword id)
 *
 *
 * This function is used to map a creator ID to a creator name, or
 * a group ID to a group name.
 *
 * The creator name/id is identical to the user name and UID under
 * Unix.
 *
 * Inputs:
 *   fcn	MapID_C for creator, MapID_G for group.
 *   id		The id to be mapped, either group ID or creator ID.	
 * 
 * Outputs:
 *  OSErr	Function result. 
 *  name	name corresponding to input ID.
 *
 *
 */

export OSErr
OSMapID(fcn,name,idd)
byte fcn;
char *name;
sdword idd;				/* 4 bytes */
{
  struct passwd *pwd;
  struct group *grp;
  int id = EtoIID(idd);			/* convert to internal id */

  if (DBOSI)
    printf("OSMapID fcn=%s id=%d\n",
	   ((fcn == MapID_C) ? "Creator" : "Group"),id);

  switch (fcn) {
  case MapID_C:
    pwd = getpwuid(id);
    if (pwd == NULL) 
      sprintf(name,"%08d",id);
    else
      strcpy(name,pwd->pw_name);
    break;
	  
  case MapID_G:
    grp = getgrgid(id);
    if (grp == NULL)
      sprintf(name,"%08d",id);
    else
      strcpy(name,grp->gr_name);
    break;
  default:
    return(aeParamErr);
  }
  return(noErr);
}

/*
 * OSErr OSMapName(byte fcn,char *name,sdword *id);
 *
 * This call is used to map a creator name to a creator ID or
 * a group name to a group id.
 *
 * The creator name/id is identical to the user name and UID under
 * Unix.
 *
 * Inputs:
 *  fcn		MapName_C for creator, MapName_G for group.
 *  name	Item to be mapped, either creator name or group name.
 *
 * Outputs:
 *  OSErr	Function result.
 *  id		ID corresponding to input name.
 *
 * 
 */

OSErr
OSMapName(fcn,name,eid)
byte fcn;
char *name;
sdword *eid;				/* 4 bytes */
{
  struct passwd *pwd;
  struct group *grp;
  int id;

  if (DBOSI)
    printf("OSMapName fcn=%s name=%s\n",
	   (fcn == MapName_C) ? "Creator" : "Group",name);

  switch (fcn) {
  case MapName_C:
    pwd = getpwnam(name); 
    if (pwd == NULL) 
      return(aeItemNotFound);
    id = pwd->pw_uid;			/* return user ID */
    break;

  case MapName_G:
    grp = getgrnam(name);		/* get group entry */
    if (grp == NULL)
      return(aeItemNotFound);
    id = grp->gr_gid;			/* return group ID */
    break;
  }
  *eid = ItoEID(id);			/* convert to external */
  return(noErr);
}

/*
 * return information about a particular user id.
 * if doself is true then return information about logged in user
 * AFP2.0
 *
*/
OSGetUserInfo(doself, userid, guirp)
boolean doself;
dword userid;
GetUserInfoReplyPkt *guirp;
{
  int bm = guirp->guir_bitmap;
  int usr = usruid;
  int grp = usrgid;
  struct passwd *pwd;

  if (!doself) {
    if ((pwd = (struct passwd *)getpwuid(userid)) == NULL)
      return(aeItemNotFound);
    usr = pwd->pw_uid;
    grp = pwd->pw_gid;
  }
  guirp->guir_userid = usr;
  guirp->guir_pgroup = grp;
  return(noErr);
}


/*
 * OSErr OSDelete(IDirP ipdir, idir ,char *file)
 *
 * OSDelete is used to delete a file or an empty directory.
 *
 * Inputs:
 *    parent directory
 *    directory id of directory (null if file)
 *    file name in parent directory
 *
 * Outputs, OSErr Function result:
 * 
 *  ParamErr		Bad path.  
 *  ObjectNotFound	Path does not point to an existing file or directory.
 *  DirNotEmpty		The directory is not empty.
 *  FileBusy		The file is open.
 *  AccessDenied	User does not have the rights (specified in AFP spec).
 *
 */
OSErr
OSDelete(ipdir,idir,file)
IDirP ipdir, idir;
char *file;
{
  int err;
  char path[MAXPATHLEN];

  OSfname(path,ipdir,file,F_DATA);	/* create data fork name */

  if (DBOSI)
    printf("OSDelete file=%s\n",path);

  if (idir) {
    err = os_rmdir(path,F_FNDR);	/* remove finder dir  */
    if (err != noErr)
      return(err);
    err = os_rmdir(path,F_RSRC);	/* delete resource directory */
    if (err != noErr)
      return(err);
    err = unix_rmdir(path);		/* delete the data file */
    if (err != noErr)
      return(err);
    (void) os_delete(ipdir,file,F_FNDR);	/* delete finder fork */
    /* remove the dirid */
    FModified(ipdir, file);
    Idrdirid(ipdir, idir);		/* idir is invalid after this point */
    return(noErr);			/* and return result */
  }

  err = unix_unlink(path);		/* rid the data file */
  if (err != noErr)
    return(err);
  (void) os_delete(ipdir,file,F_RSRC);	/* delete resource fork */
  (void) os_delete(ipdir,file,F_FNDR);	/* delete finder fork */
  FModified(ipdir, file);
  return(noErr);
}

/*
 * OSErr os_rmdir(char *dir, int typ)
 *
 * Delete a finder/resource directory as specified by type which
 * is either F_FNDR or F_RSRC.
 *
 * If a simple unix_rmdir fails because the directory is not empty
 * then scan the directory for "junk" files and remove those.
 *
 * Junk files are leftovers which exist in our finder/resource
 * directory but do not exist in the data directory.  They don't
 * usually occur under normal operation but cause a headache when
 * they do since the folder can stay locked after a delete error.
 *
*/
private OSErr
os_rmdir(dir,typ)
char *dir;
int typ;
{
  char path[MAXPATHLEN];		/* resource/finder path */
  char dpath[MAXPATHLEN];		/* data file path */
  DIR *dirp;
  struct direct *dp;
  struct stat stb;
  int pl,dpl,err;

  /* create the directory path for this rmdir... either fndr or rsrc dir */

  strcpy(path,dir);			/* local copy of dir name */
  if (typ == F_RSRC)
    strcat(path,RFDIR);			/* build resource directory name */
  else
    strcat(path,FIDIR);			/* build finder directory name */

  /* try deleting the directory */

  err = unix_rmdir(path);		/* try rmdir */
  if (err == aeObjectNotFound)		/* does not exist error? */
    err = noErr;			/* then ok by use */
  if (err == noErr ||			/* deleted ok? */
      err != aeDirNotEmpty)		/* or unknown cause? */
    return(err);			/* then return now */
  
  /* directory could not be deleted because it was not empty */
  /* delete dir entries which are not in the data directory and try again */

  strcpy(dpath,dir);			/* local copy of data dir name */
  dpl = strlen(dpath);			/* find length */
  dpath[dpl++] = '/';			/*  append slash */

  dirp = opendir(path);			/* open the fndr/rsrc dir... */
  if (dirp == NULL)			/* does not exist etc? */
    return(noErr);			/* then no directory */

  pl = strlen(path);			/* set length of fndr/rsrc dir */
  path[pl++] = '/';			/* add slash for file concats */

  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {

    if (dp->d_namlen <= 2  &&
	dp->d_name[0] == '.' &&
	(dp->d_name[1] == '.' || dp->d_name[1] == '\0'))
      continue;				/* skip dot and dot dot */

    strcpy(dpath+dpl,dp->d_name);	/* compose name in data dir */
    if (stat(dpath,&stb) == 0) {	/* to see if it exists there */
      closedir(dirp);
      return(aeDirNotEmpty);		/* if so... dir really not empty */
    }
    
    strcpy(path+pl,dp->d_name);		/* otherwise use fndr/rsrc file name */
    if (DBOSI)
      printf("os_rmdir: cleaning %s\n",path);
    err = unix_unlink(path);		/*  and remove */
    if (err != noErr) {			/* if that failed... */
      closedir(dirp);
      return(err);			/*  then return now */
    }
  }
  closedir(dirp);			/* finished with directory  */
  path[pl-1] = '\0';			/* back to fndr/rsrc name */
  return(unix_rmdir(path));		/* try deleting now */
}

private OSErr
os_delete(pdir,file,typ)
IDirP pdir;
char *file;
int typ;
{
  char path[MAXPATHLEN];

  OSfname(path,pdir,file,typ);		/* build unix file name */
  return(unix_unlink(path));		/* do the work... */
}


/*
 * OSErr OSRename(IDirP pdir, char *from, char *to);
 *
 * OSRename is used to rename a file or directory.
 *
 * Inputs:
 *  pdir	parent directory id.
 *  from	name of file or directory to rename.
 *  to		new name for file or directory.
 *
 * Outputs:
 *  OSErr	Function result.
 *
 * Pass the work along to os_move, which handles the general case.
 *
 */

OSErr
OSRename(pdir,from,to)
IDirP pdir;				/* parent directory id */
char *from,*to;				/* from and to file names */
{
  return(os_move(pdir,from,pdir,to));	/* do the work */
}

/*
 * OSErr OSMove(IDirP fpdir, char *from, IDirP tpdir, char *to)
 *
 * OSMove is used to move a directory or file to another location on
 * a single volume (source and destination must be on the same volume).
 * The destination of the move is specified by provinding a pathname
 * that indicates the object's new parent directory.
 *
 * Inputs:
 *  fpdir	parent directory id of from.
 *  from	name of file or directory to rename.
 *  tpdir	parent directory id of to.
 *  to		new directory for file or directory.
 *
 * Outputs:
 *  OSErr	Function result.
 *
 * Create an internal directory id for the new directory name by
 * combining the parent dir id (tpdir), and directory name of the
 * destination (to) and call the general routine os_move().  Note
 * that the new name is the same as the old name and to specifies 
 * the destination directory.
 *
 */

export OSErr
OSMove(fpdir,from,tpdir,to)
IDirP fpdir,tpdir;			/* from and to parent dirs */
char *from;				/* from file name */
char *to;				/*  to file name is dest directory */
{
  return(os_move(fpdir, from, tpdir, to));
}

/*
 * OSErr os_move(IDirP fpdir, char *from, IDirP tpdir, char *to)
 *
 * Move the file.
 *
 */
private OSErr
os_move(fpdir,from,tpdir,to)
IDirP fpdir,tpdir;			/* from and to parent dirs  */
char *from,*to;				/* from and to file names */
{
  char fpath[MAXPATHLEN];
  char tpath[MAXPATHLEN];
  struct stat stb;
  int err,cerr;
  int mo;

  OSfname(fpath,fpdir,from,F_DATA);	/* build data file name */
  OSfname(tpath,tpdir,to,F_DATA);	/* for from and to files */

  if (DBOSI)
    printf("OSRename from=%s, to=%s\n",fpath,tpath);

  if ((fpdir->flags & DID_FINDERINFO) && (tpdir->flags & DID_FINDERINFO) == 0)
    return(aeCantMove);
  if ((fpdir->flags & DID_RESOURCE) && (tpdir->flags & DID_RESOURCE) == 0)
    return(aeCantMove);

  /* must be able to stat destination */
  if ((err = unix_stat(pathstr(tpdir), &stb)) != noErr)
    return(err);
  mo = filemode(stb.st_mode, stb.st_uid, stb.st_gid);

  if ((err = unix_stat(fpath,&stb)) != noErr)
    return(err);

  err = unix_rename(fpath,tpath);	/* give unix the args */
  if (err != noErr)			/* if an error on data files */
    return(err);			/*  then give up */

  if (!S_ISDIR(stb.st_mode)) {		/* directories have no rsrc fork */
    unix_chmod(tpath, mo);		/* file: try to reset protection */
    if (fpdir->flags & DID_RESOURCE) {
      OSfname(fpath,fpdir,from,F_RSRC);	/* build resource file names */
      OSfname(tpath,tpdir,to,F_RSRC);
      err = unix_rename(fpath,tpath);	/* give unix a shot at it */
      /* allow non-existant resource */
      if (err != noErr && err != aeObjectNotFound) { /* error on rename? */
	if (DBOSI)
	  printf("os_rename: failed %s for %s -> %s\n",
		 afperr(err),fpath,tpath);
	OSfname(fpath,fpdir,from,F_DATA); /* try to rebuild */
	OSfname(tpath,tpdir,to,F_DATA);
	cerr = unix_rename(tpath,fpath);	/* rename back to orignal */
	if (cerr != noErr && DBOSI)
	  printf("os_rename: cleanup failed\n");
	unix_chmod(tpath, stb.st_mode&0777); /* file:try to reset protection */
	return(err);
      }
    }
  }  

  if (fpdir->flags & DID_FINDERINFO) {
    OSfname(fpath,fpdir,from,F_FNDR);	/* build finder info file names */
    OSfname(tpath,tpdir,to,F_FNDR);
    err = unix_rename(fpath,tpath);	/* give unix a shot at it */
    if (err != noErr && DBOSI) {
      printf("os_rename: failed %s for %s -> %s\n", afperr(err),fpath,tpath);
    } else {
      if (!S_ISDIR(stb.st_mode))
	unix_chmod(tpath, mo);		/* file: try to reset protection */
      OSSetMacFileName(tpdir, to);
    }
  } else
    if (DBOSI)
      printf("os_rename: no finder info to rename\n");

  if (S_ISDIR(stb.st_mode))		/* if a directory then need to */
    Idmove(fpdir,from,tpdir,to);	/*  change internal structure */

  FModified(fpdir, from);	/* does an emodified */
  /* EModified(fpdir); */
  /* don't need to mark dest file as modified since mac won't let this */
  /* happen */
  EModified(tpdir);
  return(noErr);
}

    
/*
 * OSErr OSFlush(int vid)
 *
 * OSFlush is used to flush to disk any data relating to the specified
 * volume that has been modified by the user.
 *
 * The Unix system call sync is used.  We should probably be dumping out
 * internal volume buffers instead.
 *
 * Inputs:
 *  vid		Volume ID.
 *
 * Outputs:
 *  OSErr	Function Result.	 
 *
 */

/*ARGSUSED*/
export OSErr
OSFlush(vid)
int vid;
{
  import GCHandle *fich;	/* get FinderInfo cache */

  GCFlush(fich, NILDIR);	/* flush the finderinfo of bad data */
  FlushDeskTop(vid);
/*  sync();			/* this is probably a waste */
  /* above is a waste and slows down system unnecessarily */
  return(noErr);
}

/*
 * OSErr OSFlushFork(int fd)
 *
 * Forces the write to disk of any pending file activity.
 * 
 * Really intended for buffered OSWrites.
 *
 * Inputs:
 *  fd		File descriptor.
 *  
 * Outputs:
 *  OSErr	Function Result.
 *
 */

OSErr
OSFlushFork(fd)
int fd;
{
  if (DBOSI)
    printf("OSFlushFork fd=%d\n",fd);

  return(fsync(fd) == 0 ? noErr : aeMiscErr);
}


export OSErr
OSClose(fd)
int fd;
{
  return(unix_close(fd));		/* return OSErr */
}

/*
 * From the open file referenced by fd
 * at the offset offs
 * read "reqcnt" bytes
 * using the new line mask nlmsk
 * and the newline character nlchr
 * into the buffer r for at most rl bytes
 * keeping the file position in fpos
 * translating from lf to cr if unixtomac is nonzero
 *
*/
export OSErr
OSRead(fd,offs,reqcnt,nlmsk,nlchr,r,rl,fpos,trans_table_index)
int fd;
sdword offs,reqcnt;
byte nlmsk,nlchr;
byte *r;
int *rl;
sdword *fpos;
int trans_table_index;
{
  register char c;
  int cnt,i;

#ifdef notdef
  /* want to probe for eof -- probably there */
  if (reqcnt == 0) {
    *rl = 0;
    return(noErr);
  }
#endif

  if (offs != *fpos)
    lseek(fd,(off_t)offs,L_SET);

    if (OSTestLock(fd, reqcnt) != noErr) {
      return(aeLockErr);
  }

  cnt = read(fd,r,reqcnt);
  if (cnt < 0) {
    printf("OSRead: Error from read %s\n",syserr());
    return(aeParamErr);
  }

  if (cnt == 0)
    return(aeEOFErr);

  *fpos += cnt;

  /* under appleshare prior to version 2.0, nlmask was either 0 or 0xff */
  /* so no anding needed to be done (either use or not).  shouldn't hurt */
  /* to do it for previous versions though */
  if (nlmsk != 0) {
#ifndef NONLXLATE
    if (nlchr == ENEWLINE) {
      for (i=0; i < cnt; i++) {
	c = r[i] & nlmsk;
	if (c == ENEWLINE || c == INEWLINE)
	  break;
      }
      if (r[i] == INEWLINE)		/* if ended on internal newline */
	r[i] = ENEWLINE;		/*  then convert to external */
    } else
      for (i=0; i < cnt && (r[i]&nlmsk) != nlchr; i++)
	/* NULL */;
#else    
    for (i=0; i < cnt && (r[i]&nlmsk) != nlchr; i++)
      /* NULL */;
#endif NONLXLATE

    if (i < cnt)			/* found it? */
      cnt = i+1;			/* yes count is position plus 1 */
  }
  if (trans_table_index >= 0) {
    if (DBOSI)
      printf("FPRead: translating to macintosh according to: %s\n",
	     ncs_tt_name(trans_table_index));
    ncs_translate(NCS_TRANS_UNIXTOMAC, trans_table_index, r, cnt);
  }

  *rl = cnt;				/* store count of bytes read */
  if (cnt < reqcnt && nlmsk == 0)	/* less than request and no nlchr */
    return(aeEOFErr);			/*  means we found eof */
  return(noErr);			/* else no error.... */
}

/*
 * Write to the open file referenced by fd
 *   the write buffer is wbuf of length wlen
 *   do the write at offset offs
 *   keeping file position in fpos
 * flg - marks whether offs relative to beginning or end of file
 * unixtomax - if non-zero translate cr to lf on writes
 *
*/
OSWrite(fd,wbuf,wlen,offs,flg,fpos,trans_table_index)
int fd;
byte *wbuf;
sdword wlen,offs;
byte flg;
sdword *fpos;
int trans_table_index;
{
  int cnt;

  if (wlen == 0)			/* zero byte request? */
    return(noErr);			/*  yes... no work */

  if (flg == 0) {
    if (offs != *fpos)
      *fpos = lseek(fd,(off_t)offs,L_SET);
  } else
   *fpos = lseek(fd,(off_t)offs,L_XTND);

  if (OSTestLock(fd, wlen) != noErr) {
    return(aeLockErr);
  }
  if (trans_table_index >= 0) {
    if (DBOSI)
      printf("FPWrite: translating from macintosh according to: %s\n",
	     ncs_tt_name(trans_table_index));
    ncs_translate(NCS_TRANS_MACTOUNIX, trans_table_index, wbuf, wlen);
  }

  cnt = write(fd,wbuf,wlen);
  *fpos += cnt;
  if (cnt == wlen)
    return(noErr);
  if (DBOSI)
    printf("OSWrite: Error from write %s\n",syserr());
  return(ItoEErr(errno));
}

/*
 * OSErr OSCreateDir(char *path,dword *dirid)
 *
 * This function is used to create a new directory.
 *
 * Inputs:
 *  path	The directory to create.
 *
 * Outputs:
 *  OSErr	Function result.
 *  dirid	Directory ID of newly created directory.
 *
 */

private OSErr
os_mkdir(pdir,name,mode,typ)
IDirP pdir;				/* parent directory */
char *name;
int typ,mode;
{
  char path[MAXPATHLEN];
  OSErr err;
					/* want path/name/.resource */
					/* want path/name/.finderinfo */
					/* want path/name */

  OSfname(path, pdir, name, F_DATA);	/* get path/name */
  switch (typ) {
  case F_RSRC:
    strcat(path, "/");
    strcat(path, RFDIRFN);
    break;
  case F_FNDR:
    strcat(path, "/");
    strcat(path, FIDIRFN);
    break;
  }
  if (DBOSI)
    printf("os_mkdir: creating mode=o%o dir=%s\n",mode,path);

  err = unix_mkdir(path,mode);		/* let unix do the work */
  if (err != noErr)
    return(err);
  EModified(pdir);
  return(noErr);
}  


OSErr
OSCreateDir(pdir,name, newdirid)
IDirP pdir;				/* parent directory id */
char *name;				/* name of new directory */
IDirP *newdirid;
{
  char path[MAXPATHLEN];
  int err,mo;
  struct stat stb;

  if (DBOSI)
    printf("OSCreateDir: creating %s\n",name);

  err = unix_stat(pathstr(pdir),&stb);	/* get current protections */
  mo = stb.st_mode & 0777;

  err = os_mkdir(pdir,name,mo,F_DATA);	/* create the data directory */
  if (err != noErr)			/* if that failed... then */
    return(err);			/*  return the error */

  if (pdir->flags  & DID_FINDERINFO) {
    OSfname(path,pdir,name,F_FNDR);	/* create finderinfo for folder */
    err = unix_create(path,TRUE,mo);	/*  do delete if exists... */
    os_mkdir(pdir,name,mo,F_FNDR);	/* create the finderinfo directory */
  }
  if (pdir->flags & DID_RESOURCE)
    os_mkdir(pdir,name,mo,F_RSRC);	/* create the resource directory */
  *newdirid = Idndirid(pdir,name);	/* now install the directory */
  return(noErr);
}


/*
 * OSErr OSFileDirInfo(IDirP ipdir, char *fn,
 *			FileDirParms *fdp, int volid);
 *
 * Return information for file fn, existing in directory ipdir into
 * the fdp structure.
 *
 * fdp->fdp_dbitmap and fdp->fdp_fbitmap are set with the request
 * bitmaps so we don't necessarily need to fetch unwanted (costly)
 * items.
 *
 */
export OSErr 
OSFileDirInfo(ipdir,idir,fn,fdp,volid)
IDirP ipdir;				/* parent directory */
IDirP idir;				/* directory id if directory */
char *fn;				/* file name */
FileDirParm *fdp;			/* returned parms */
int volid;				/* volume */
{
  char path[MAXPATHLEN];
  struct stat buf;
  time_t sometime;

  OSfname(path,ipdir,fn,F_DATA);

  if (DBOSI)
    printf("OSFileDirInfo on %s\n",path);

  if (stat(path,&buf) != 0) {		/* file exists? */
    if (idir)				/* was in directory tree? */
      Idrdirid(ipdir, idir);		/* invalidate the entry then */
    return(aeObjectNotFound);		/* no... */
  }

  /* pick out the earliest date for mac creation time */
  sometime = (buf.st_mtime > buf.st_ctime) ? buf.st_ctime : buf.st_mtime;
  fdp->fdp_cdate = (sometime > buf.st_atime) ? buf.st_atime : sometime;
  /* pick the later of status change and modification for */
  /* mac modified */
  fdp->fdp_mdate = (buf.st_mtime < buf.st_ctime) ? buf.st_ctime : buf.st_mtime;

  fdp->fdp_bdate = 0;
  fdp->fdp_zero = 0;			/* zero the zero byte (?) */
/*  strcpy(fdp->fdp_lname,fn);		/* copy long name */
  if (idir == VolRootD(volid))
    strcpy(fdp->fdp_lname, VolName(volid));
  else
    ItoEName(fn,fdp->fdp_lname);

  if (S_ISDIR(buf.st_mode)) {		/* is this a directory? */
    fdp->fdp_flg = FDP_DIRFLG;		/* yes... */
    return(OSDirInfo(ipdir,fn,fdp,&buf,volid));	/* fill in */
  }
  fdp->fdp_flg = 0;			/* otherwise a file */
  return(OSFileInfo(ipdir,fn,fdp,&buf)); /* fill in */
}

  
export OSErr
OSDirInfo(ipdir,fn,fdp,buf,volid)
IDirP ipdir; 
char *fn;
FileDirParm *fdp;
struct stat *buf;
int volid;
{
  IDirP idirid;
  dword ItoEAccess();
  word bm;
  int nchild;

  fdp->fdp_dbitmap &= DP_AUFS_VALID; /* truncate to findable */
  bm = fdp->fdp_dbitmap;

  if (DBDIR)
    printf("OSDirInfo on %s bm=%x\n",fn,bm);

  if (bm & DP_ATTR)			/* skip attr if not requested */
    OSGetAttr(ipdir,fn,&fdp->fdp_attr);
  if (bm & DP_FINFO)			/* skip finfo if not requested */
    OSGetFNDR(ipdir,fn,fdp->fdp_finfo);

  fdp->fdp_parms.dp_parms.dp_ownerid = ItoEID(buf->st_uid);
  fdp->fdp_parms.dp_parms.dp_groupid = ItoEID(buf->st_gid);
  fdp->fdp_parms.dp_parms.dp_accright =
    ItoEAccess(buf->st_mode,buf->st_uid,buf->st_gid);

  idirid = Idndirid(ipdir,fn);	/* must validate the entry now */
  if (idirid == NILDIR)
    return(aeAccessDenied);
  InitDIDVol(idirid, volid);
#ifdef notdef
  /* should be done already - so don't do it here! */
  if ((idirid->flags & DID_VALID) == 0) /* info valid? */
    OSValidateDIDDirInfo(idirid); /* valid it then */
#endif
  if (bm & DP_CHILD) {
    nchild = OSEnumCount(idirid);
    if (nchild < 0)			/* error if less than zero */
      nchild = 0;			/*  probably no read... set to 0 */
    fdp->fdp_parms.dp_parms.dp_nchild = nchild;
  }
  fdp->fdp_parms.dp_parms.dp_dirid = ItoEdirid(idirid,volid);
  return(noErr);
}

/* 
 * validates a did by making sure:
 *  - idirid points to a directory
 *  - limits number of symbolic links we will follow in any given path!
 *    o note: overlapping volumes may cause us to follow too many
 *      symbolic links, but things should eventually catch up.
 * also checks if the .resource and .finderinfo directories exists
 *  (must not be symbolic links)
 * double check that parent exists
*/
export void
OSValidateDIDDirInfo(idirid)
IDirP idirid;
{
  char path[MAXPATHLEN];
  struct stat stb;
  IDirP pdir;
  int i;

  OSfname(path,idirid,"",F_DATA);
  if (stat(path, &stb) == 0) {
    if (S_ISDIR(stb.st_mode))
      idirid->flags |= DID_DATA;
#ifndef NOLSTAT
    if (lstat(path, &stb) != 0) { /* shouldn't fail! */
      idirid->flags = DID_VALID;
      return;
    }
    if ((pdir = Ipdirid(idirid)) != NILDIR) {	/* get parent */
      /* get count of symlinks of parent */
      i = ((pdir->flags & DID_SYMLINKS) >> DID_SYMLINKS_SHIFT);
      if ((stb.st_mode & S_IFMT) == S_IFLNK) {
	i++;			/* bump up count */
	if (i > DID_MAXSYMLINKS) {
	  idirid->flags = DID_VALID; /* toss it, too many links down */
	  return;
	}
      }
      /* really shouldn't need to mask it - means we are overinc'ed */
      idirid->flags |= ((i << DID_SYMLINKS_SHIFT) & DID_SYMLINKS);
    }
    /* don't follow symbolic links here! */
    OSfname(path,idirid,"",F_FNDR);
    if (lstat(path, &stb) == 0) 
      if (S_ISDIR(stb.st_mode))
	idirid->flags |= DID_FINDERINFO;
    OSfname(path,idirid,"",F_RSRC);
    if (lstat(path, &stb) == 0)  
      if (S_ISDIR(stb.st_mode))
	idirid->flags |= DID_RESOURCE;
#else
    /* no symolic links then */
    OSfname(path,idirid,"",F_FNDR);
    if (stat(path, &stb) == 0) 
      if (S_ISDIR(stb.st_mode))
	idirid->flags |= DID_FINDERINFO;
    OSfname(path,idirid,"",F_RSRC);
    if (stat(path, &stb) == 0)  
      if (S_ISDIR(stb.st_mode))
	idirid->flags |= DID_RESOURCE;
#endif
  }
  idirid->flags |= DID_VALID;
}

export OSErr
OSFileInfo(ipdir,fn,fdp,buf)
IDirP ipdir;
char *fn;
FileDirParm *fdp;
struct stat *buf;
{
  struct stat stb;
  char rpath[MAXPATHLEN];
  word bm;

  fdp->fdp_fbitmap &= FP_AUFS_VALID; /* truncate to aufs supported */
  bm = fdp->fdp_fbitmap;		/* fetch file bitmap */

  if (DBDIR)
    printf("OSFileInfo on %s bm=%x\n",fn,bm);

  if (bm & FP_ATTR)			/* skip attr if not requested */
    OSGetAttr(ipdir,fn,&fdp->fdp_attr);

  if (bm & FP_FINFO)			/* skip finfo if not requested */
    OSGetFNDR(ipdir,fn,fdp->fdp_finfo);

  fdp->fdp_parms.fp_parms.fp_fileno = buf->st_ino;
  fdp->fdp_parms.fp_parms.fp_dflen = buf->st_size;
  fdp->fdp_parms.fp_parms.fp_rflen = 0;

  if (bm & FP_RFLEN) {
    OSfname(rpath,ipdir,fn,F_RSRC);	/* convert to rsrc name */
    if (stat(rpath,&stb) != 0)		/* to figure size of resource fork */
      return(noErr);
    if (DBFIL)
      printf("OSFileInfo: %s size is %d\n", rpath,stb.st_size);
    fdp->fdp_parms.fp_parms.fp_rflen = stb.st_size;
  }
  return(noErr);
}

/*
 * simply check to see if a particular file exists
 *
*/
export OSErr
OSFileExists(ipdir, fn, type)
IDirP ipdir;
char *fn;
int type;
{
  char path[MAXPATHLEN];  
  struct stat stb;

  OSfname(path, ipdir, fn, type);
  return(unix_stat(path, &stb));
}

export OSErr
OSSetFileDirParms(ipdir,idir,fn,fdp)
IDirP ipdir;
IDirP idir;				/* directory id if dir */
char *fn;
FileDirParm *fdp;
{
  char path[MAXPATHLEN];
  struct stat stb;
  int err;

  OSfname(path,ipdir,fn,F_DATA);	/* unix file name */
  if ((err = unix_stat(path,&stb)) != noErr) {
    /* can't find it !!! */
    if (idir)
      Idrdirid(ipdir, idir);		/* remove from tree */
    return(err);
  }

  if (S_ISDIR(stb.st_mode))		/* if a directory */
    return(OSSetDirParms(ipdir,fn,fdp)); /* then set dir parms... */
  else					/* else set file parms */
    return(OSSetFileParms(ipdir,fn,fdp));
}

export OSErr
OSSetFileParms(ipdir,fn,fdp)
IDirP ipdir;
char *fn;
FileDirParm *fdp;
{
  word bm = fdp->fdp_fbitmap;

  if (bm & (FP_FINFO|FP_ATTR))
    OSSetFA(ipdir,fn,fdp->fdp_fbitmap,fdp);
  return(noErr);
}


/*
 * OSSetDirParms
 * 
 *
*/
OSErr
OSSetDirParms(ipdir,fn,fdp)
IDirP ipdir;
char *fn;
FileDirParm *fdp;
{
  u_short EtoIAccess();
  char path[MAXPATHLEN];
  int own,grp,err;			/* owner and group ids */
  DirParm *dp = &fdp->fdp_parms.dp_parms;
  int flags;

  if (fdp->fdp_dbitmap & (DP_FINFO|DP_ATTR))
    OSSetFA(ipdir,fn,fdp->fdp_dbitmap,fdp);

  grp = own = -1;
  if (fdp->fdp_dbitmap & DP_CRTID)
    own = EtoIID(dp->dp_ownerid);    
  if (fdp->fdp_dbitmap & DP_GRPID)
    grp = EtoIID(dp->dp_groupid);

  flags = ipdir->flags;		/* should use to prevent overworking */
  if (own != -1 || grp != -1) {
    /* error recovery? do all just in case */
    OSfname(path,ipdir,fn,F_FNDR);	/* change unix name */
    if ((err = unix_chown(path,own,grp)) != noErr)
      return(err);
    OSfname(path,ipdir,fn,F_RSRC);	/* change unix name */
    if ((err = unix_chown(path,own,grp)) != noErr && err != aeObjectNotFound)
      return(err);
    OSfname(path,ipdir,fn,F_DATA);	/* create unix name */
    if ((err = unix_chown(path,own,grp)) != noErr && err != aeObjectNotFound)
      return(err);
    EModified(ipdir);
  }
    
  if (fdp->fdp_dbitmap & DP_ACCES) {
    u_short acc = EtoIAccess(dp->dp_accright);

    if ((err = os_chmod(ipdir,fn,acc,F_DATA)) != noErr)
      return(err);
    os_chmod_all(ipdir, fn, acc, F_DATA); /* change all file protections */
    os_chmod_all(ipdir, fn, acc, F_RSRC);
    os_chmod_all(ipdir, fn, acc, F_FNDR);
    if ((err = os_chmod(ipdir,fn,acc,F_RSRC)) != noErr &&
	err != aeObjectNotFound)
      return(err);
    if ((err = os_chmod(ipdir,fn,acc,F_FNDR)) != noErr &&
	err != aeObjectNotFound)
      return(err);
  }
  return(noErr);
}


/*
 * Set fork length specified the file handle
 * - careful about len - should be at least a signed double word
 *   on mac (4 bytes)
*/
export OSErr
OSSetForklen(fd, len)
int fd;
int len;
{
  int err;
  if (DBOSI)
    printf("OSSetForklen: truncating file on file descriptor %d to %d\n",
	   fd,len);
  if (ftruncate(fd, len) < 0) {
    err = errno;
    if (DBOSI)
      printf("OSSetForklen: error on truncate %s\n",syserr());
    return(ItoEErr(err));
  }
  return(noErr);
}

/*
 * OSErr os_chmod(IDirP idir, u_short mode, int typ)
 *
 * Directory id (idir), and type (typ) specify a directory name.
 * Internal access bits are mode.
 *
 * Change the protection of the directory to eacc.  
 *
 */
private OSErr
os_chmod(idir,fn,mode,typ)
IDirP idir;
char *fn;
u_short mode;
int typ;
{
  char path[MAXPATHLEN];
  int err;

  OSfname(path,idir,fn,typ);		/* convert unix name */
  if (DBOSI)
    printf("os_chmod: setting %o for %s\n",mode,path);

  err = unix_chmod(path,mode);		/* and set for the directory */
  if (err != noErr)
    return(err);

  EModified(idir);
  return(noErr);
}

/*
 * Change file protection for all files in directory
 *
 * Have to do because:
 * unix has file protection and AFP does not, change the protection
 * of each file in the directory as well.
 *
 * Do not change the protection of directories contained within
 * the directory... 
 *
*/
private void
os_chmod_all(idir,fn,mode,typ)
IDirP idir;
char *fn;
u_short mode;
int typ;
{
  char path[MAXPATHLEN];
  struct stat stb;
  struct direct *dp;
  DIR *dirp;
  int pl,err;

  OSfname(path,idir,fn,F_DATA);		/* convert unix name */
  pl = strlen(path);
  switch (typ) {
  case F_DATA:
    break;
  case F_RSRC:
    path[pl] = '/';
    strcpy(path+pl+1, RFDIRFN);
    break;
  case F_FNDR:
    path[pl] = '/';
    strcpy(path+pl+1, FIDIRFN);
    break;
  }
  if (DBOSI)
    printf("os_chmod: setting %o for %s\n",mode,path);

  dirp = opendir(path);
  if (dirp == NULL) {
    if (DBOSI)
      printf("os_chmod: opendir failed on %s\n",path);
    return;
  }

  pl = strlen(path);			/* length of the path */
  path[pl++] = '/';			/* add component terminator */
  for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
    strcpy(path+pl,dp->d_name);		/* create file name */
    if (stat(path,&stb) != 0) {		/* get the file status  */
      if (DBOSI)
	printf("os_chmod: stat failed for %s\n",path);
      continue;				/*  some error... */
    }
    if (S_ISDIR(stb.st_mode)) {
      if (dp->d_name[0] != '.')
	continue;
      /* if not .resource or .finderinfo then skip */
      if (typ != F_DATA &&
	  strcmp(dp->d_name,RFDIRFN) != 0 && strcmp(dp->d_name, FIDIRFN) != 0)
	continue;
    }
    err = unix_chmod(path,mode);	/* set the mode for this file */
    /* ignore errors */
  }
  closedir(dirp);			/* close the directory */
}


private u_short
EtoIPriv(emode,eshift,ishift)
dword emode;
int eshift,ishift;
{
  u_short i = 0;

  emode = (emode >> eshift);
  if (emode & E_RD) i = I_RD | I_EX;
  if (emode & E_WR) i |= I_WR | I_EX;
/*  if (emode & E_SR) i |= I_EX; */
  return(i << ishift);  
}


/*
 * Is the current user in the group gid?
 *
*/
private int
OSInGroup(gid)
int gid;
{
  int i;
  int gtgid;

  /* if ngroups gets very large, do a binary search */
  for (i=0; i < ngroups; i++) {
    gtgid = groups[i];
    if (gtgid == gid)
      return(TRUE);
    if (gtgid > gid)		/* limiting case */
      return(FALSE);
  }
  return(FALSE);
}

/*
 * Get groups that a user is valid in
 *
 * Sort the array for later use
 *
*/
dogetgroups()
{
  int ng;
  int i,k,idxofmin;
  int t;

  if ((ng = getgroups(NGROUPS, groups)) < 0) {
    return(-1);
  }
  if (ng == 0)			/* not in any groups? */
    return(0);

  /* sort groups array */
  /* we assume n is very small, else possibly replace with quicker sort */
  /* n**2 performance (comparisons), but no more than n swaps */
  /* the array tends to be mostly sorted with the first element out */
  /* of place.  Don't use std quicksort -- under this assumption */
  /* it will give very poor performance on average (at much higher overhead) */
  /* NOTE: we could really speed this up if we knew that the  */
  /* array was sorted after the first "n" items, but with N so */
  /* small (usually less than 32), it's not a big deal */
  for (i = 0 ; i < ng; i++) {
    for ( idxofmin = i, k = i + 1; k < ng; k++) /* find (i+1)'th min */
      if (groups[k] < groups[idxofmin])
	idxofmin = k;
    if (i != idxofmin) {
      t = groups[idxofmin];
      groups[idxofmin] = groups[i];
      groups[i] = t;
    }
  }
  return(ng);
}

private u_short
EtoIAccess(emode)
dword emode;
{
  u_short imode;

  imode = (EtoIPriv(emode,ES_OWNER,IS_OWNER) |
	  EtoIPriv(emode,ES_GROUP,IS_GROUP) |
	  EtoIPriv(emode,ES_WORLD,IS_WORLD));

  if (DBOSI)
    printf("EtoIAccess: E=0x%x, I=o%o\n",emode,imode);
  return(imode);
}

private dword
ItoEPriv(imode,ishift,eshift)
u_short imode;
int ishift,eshift;
{
  dword e = 0;
  
  imode = (imode >> ishift);
  if (imode & I_RD) e = E_RD | E_SR;
  if (imode & I_WR) e |= E_WR;
/*  if (imode & I_EX) e |= E_SR; */
  return(e << eshift);
}

private dword
ItoEAccess(imode,uid,gid)
u_short imode;
int uid;
int gid;
{
  dword e = 0;

  if (usruid == 0)		/* root? */
    e |= ((E_RD|E_WR|E_SR)<<ES_USER);
  else if (usruid == uid)	/* but if the owner then */
    e |= ItoEPriv(imode,IS_OWNER,ES_USER)|E_IOWN; /* set owner bits */
  else if (OSInGroup(gid))		/* if in one of the groups */
    e |= ItoEPriv(imode,IS_GROUP,ES_USER); /* set group access as well */
  else e = ItoEPriv(imode,IS_WORLD,ES_USER); /* user rights = world */
  
  e |= (ItoEPriv(imode,IS_OWNER,ES_OWNER) | /* other access */
	ItoEPriv(imode,IS_GROUP,ES_GROUP) |
	ItoEPriv(imode,IS_WORLD,ES_WORLD));

  if (DBOSI)
    printf("ItoEAccess: I=o%o, E=0x%x\n",imode,e);
  return(e);
}

export OSErr
OSAccess(idir,fn,mode)
IDirP idir;
char *fn;
int mode;
{
  int imode = 0;
  int err;
  char path[MAXPATHLEN];

  if (mode & OFK_MWR)
    imode |= W_OK;
  if (mode & OFK_MRD)
    imode |= R_OK;

  OSfname(path,idir,fn,F_DATA);		/* create unix style filename */
  err = access(path,imode);
  if (err == 0)
    return(noErr);
  switch (errno) {
  case ENOTDIR:
    return(aeDirNotFound);
  case ENOENT:
    return(aeObjectNotFound);
  case EACCES:
    return(aeAccessDenied);
  }
  return(aeAccessDenied);
}

/*
 * OSErr OSVolInfo(VolPtr v)
 *
 * Update volume information for volume pointed to by v.
 * Returns error if path does not exist.
 *
 * Update:
 *
 *  v_attr	Read only flag (V_RONLY)
 *  v_cdate	creation date (of v_path)
 *  v_mdate	modification date (of v_path)
 *  v_size 	size of volume in bytes ????
 *  v_free	free bytes on volume  ????
 *
 */

export OSErr
OSVolInfo(path,v, bitmap)
char *path;
VolPtr v;
word bitmap;			/* bitmap of info needed */
{
  struct stat buf;
#ifdef USEQUOTA
  struct dqblk dqblk;
#endif
#ifdef USEUSTAT
  struct ustat ubuf;
#endif
#ifdef USESTATFS
  struct statfs fsbuf;
#endif
  time_t sometime;

  if (stat(path,&buf) != 0)	/* directory exists? */
    return(aeObjectNotFound);	/* no... */
  if (!(S_ISDIR(buf.st_mode)))	/* check for directory */  
    return(aeParamErr);		/* not a directory! */
    
  if (bitmap & VP_CDATE) {
    /* pick out the earliest date for mac creation time */
    sometime = (buf.st_mtime > buf.st_ctime) ? buf.st_ctime : buf.st_mtime;
    v->v_cdate = sometime > buf.st_atime ? buf.st_atime : sometime;
  }
  if (bitmap & VP_MDATE) {
    /* pick the later of status change and modification for */
    /* mac modified */
    v->v_mdate = (buf.st_mtime < buf.st_ctime) ? buf.st_ctime : buf.st_mtime;
  }
#ifdef notdef
  /* had it as v->v_mdate -- probably the reason we ifdef'ed it out */
  if (bitmap & VP_BDATE)
    v->v_bdate = 0;
#endif

  if (bitmap & VP_ATTR) {
#ifdef notdef
    /* don't really want this - causes problems when you have access */
    /* futher down the tree - should only come up locked iff the */
    /* tree is write locked (no (easy) way to tell because of symbolic */
    /* links and mount points) */
    if (access(v->v_path,W_OK) != 0) 	/* ok to write into directory? */
      v->v_attr |= V_RONLY;	/* no, set read-only */
    else
#endif
      v->v_attr &= ~V_RONLY;	/* clear read-only */
  }

  if ((bitmap & (VP_FREE|VP_SIZE)) == 0)
    return(noErr);		/* naught else to do */

  /* All the following is good and fine unless: (a) the volume */
  /* has symlinks off the volume or (b) there are mounted file systems */
  /* under the mac volume.  In those cases, returning this information */
  /* could be damaging because some "good" programs base what they */
  /* can do on the volume information --- but people really like this */
  /* information!!! so we take the trade off (even though it is one */
  /* of the most system dependent parts of aufs) */

  /* don't know how to calculate disk free and size without being su */
  /* (in the general case) */

  /* hard coded values of 512 for quotas and 1024 for ustat are bad */
  /* where are the "real" numbers defined? */

  /* careful on the ordering - these must go last and if you can possibly */
  /* define more than one then you must define in order you wish */
#ifdef USEQUOTA
  if (quota(Q_GETDLIM, usruid, buf.st_dev, &dqblk) == 0 &&
      dqblk.dqb_bhardlimit != 0) { /* make sure not unlimited */
    v->v_size = dqblk.dqb_bhardlimit*512;
    v->v_free = (dqblk.dqb_bhardlimit-dqblk.dqb_curblocks)*512;
    return(noErr);
  }
#endif
#ifdef USEGETMNT
  if (ultrix_volinfo(path, &buf, v) == noErr)
    return(noErr);
#endif
#ifdef USEUSTAT
  if (ustat(buf.st_dev, &ubuf) >= 0) {
    if (VP_SIZE & bitmap) {
      /* should do something better here */
      v->v_size = ubuf.f_tfree*1024;
    }
    v->v_free = ubuf.f_tfree*1024;
    return(noErr);
  }
#endif
#ifdef USESTATFS
  if (statfs(path, &fsbuf) >= 0) {
    v->v_size = fsbuf.f_bsize * fsbuf.f_blocks;
    v->v_free = fsbuf.f_bsize * fsbuf.f_bavail;
    return(noErr);
  }
#endif
  v->v_size = 0x1000000;		/* some random number */
  v->v_free = 0x1000000;		/* same random number */
  return(noErr);			/* all ok */
}

#ifdef USEGETMNT
/* get info on path using buf when there is ambiguity (ultrix 2.0 or before) */
/* fill in info on v */
private OSErr
ultrix_volinfo(path,buf,v)
char *path;
struct stat *buf;
VolPtr v;
{
  int context = 0;
  int i, num;
  u_int vfree;
  /* multiple buffers are wasteful when using Ultrix 2.2, but code is */
  /* good enough */
  struct fs_data buffer[NUMGETMNTBUF];
  struct fs_data *bp;
  int nbytes = sizeof(struct fs_data)*NUMGETMNTBUF;

  if (!oldgetmnt) {
    /* Ultrix 2.2 */
    /* use nostat_one -- we don't want to hang on nfs */
    /* return none if error or (0) - not found */
    if ((num=getmnt(&context, buffer, NOSTAT_ONE, nbytes)) <= 0)
      return(-1);
    bp = buffer;
  } else {
    while ((num=getmnt(&context, buffer, nbytes)) > 0) {
      for (i = 0, bp = buffer; i < num; i++, bp++)
	if (buf->st_dev == bp->fd_req.dev)
	  goto found;
      /* context is set to zero if last call to getmnt returned */
      /* all file systems */
      if (context == 0)
	return(-1);
    }
    /* should never reach here, means getmnt returned an error */
    return(-1);			/* nothing found */
  }
found:
  /* "overflow" space if any - looks used */
  v->v_size = bp->fd_req.btot * 1024;
  /* bfreen must be "good" in that it cannot go below 0 when */
  /* out of space -- it is unsigned! */
  v->v_free = ((getuid() == 0) ? bp->fd_req.bfree : bp->fd_req.bfreen) * 1024;
  return(noErr);
}
#endif /* GETMNT */

#ifdef USESUNQUOTA

#ifndef MAXUFSMOUNTED
# ifdef NMOUNT
#  define MAXUFSMOUNTED NMOUNT	/* NMOUNT in param.h */
# else
#  define MAXUFSMOUNTED 32		/* arb. value */
# endif
#endif

private struct mount_points {
  char *mp_fsname;		/* name of "block" device */
  dev_t mp_dev;			/* device number */
} mount_points[MAXUFSMOUNTED];

private int num_mount_points = -1;

private struct mount_points *
find_mount_spec_intable(dev)
dev_t dev;
{
  int i;
  struct mount_points *mp;

  for (i = 0, mp = mount_points; i < num_mount_points; i++, mp++) {
    if (dev == mp->mp_dev)
      return(mp);
  }
  return(NULL);
}

/*
 * find the block special device...
 * try updating mount point table if possible
 *
 * returns name if it can, null o.w.
*/
private char *
find_mount_spec(dev)
{
  struct mount_points *mp;
  struct mntent *mtent;
  struct stat sbuf;
  FILE *mt;
  char *strdup();

  if ((mp = find_mount_spec_intable(dev)) != NULL) /* try once */
    return(mp->mp_fsname);
  
  if (num_mount_points < MAXUFSMOUNTED) {
    /* check to see if mounted */
    if ((mt = setmntent("/etc/mtab", "r")) == NULL) {
      if (DBOSI)
	log("/etc/mtab is read protected or nonexistant");
      return(NULL);
    }
    mp = NULL;
    while ((mtent = getmntent(mt)) != NULL) {
      if (stat(mtent->mnt_fsname, &sbuf) < 0)
	continue;
      if (dev != sbuf.st_rdev)
	continue;
      mp = mount_points+num_mount_points;
      num_mount_points++;
      mp->mp_fsname = strdup(mtent->mnt_fsname);
      mp->mp_dev = sbuf.st_rdev;
      break;
    }
    endmntent(mt);
  } else {
    /* table would overflow, try rebuilding */
    if (build_mount_table() < 0)	/* try rebuilding table */
      return(NULL);
    mp = find_mount_spec_intable(dev);
  }
  if (mp)
    return(mp->mp_fsname);
  if (DBOSI)
    log("Cannot find file system on device (%d,%d)\n", major(dev),minor(dev)); 
  return(NULL);			/* total failure */
}

/*
 * build a table of the various mounted file systems
 * using getmntent.  We want to use /etc/mtab, but
 * if we can't, then we use /etc/fstab to get some 
 * information anyway if this is the first time around (to
 * prevent constant rereads since /etc/fstab is pretty constant)
 *
*/
int
build_mount_table()
{
  FILE *mt;
  struct stat sbuf;
  struct mntent *mtent;
  struct mount_points *mp;
  char *strdup();

  if ((mt = setmntent("/etc/mtab", "r")) == NULL) {
    if (DBOSI)
      log("/etc/mtab is read protected or nonexistant");
    if (num_mount_points != 0)
      return(-1);
    if ((mt = setmntent("/etc/fstab", "r")) == NULL) {
      if (DBOSI)
	log("/etc/fstab is read protected or nonexistant");
      return(-1);
    }
  }

  /* free old info */
  if (num_mount_points) {
    for (mp = mount_points ; num_mount_points > 0; num_mount_points--, mp++)
      if (mp->mp_fsname)
	free(mp->mp_fsname);
  }
  num_mount_points = 0;	/* paranoia */

  mp  = mount_points;
  while ((mtent = getmntent(mt)) != NULL) {
    if (stat(mtent->mnt_fsname, &sbuf) < 0)
      continue;
    mp->mp_fsname = strdup(mtent->mnt_fsname);
    mp->mp_dev = sbuf.st_rdev;
    num_mount_points++, mp++;
    if (num_mount_points > MAXUFSMOUNTED) {
      log("Grrr.. too many mounted file systems for build_mount_table");
      break;
    }
  }
  endmntent(mt);
  if (num_mount_points == 0 && DBOSI)
    log("No mount points can be found");
  return(0);
}

/*
 * SunOS doesn't use the Melbourne quota system - it has its own
 * private one that uses quotactl instead of quota.  We emulate
 * quota here...
 *
*/
int
quota(cmd, uid, arg, addr)
int cmd, uid, arg;
caddr_t addr;
{
  char *fsname;

  switch (cmd) {
  case Q_QUOTAON:
  case Q_QUOTAOFF:
  case Q_SETQUOTA:
  case Q_GETQUOTA:
  case Q_SETQLIM:
  case Q_SYNC:
    break;
  default:
    errno = EINVAL;
    return(-1);
  }
  
  if ((fsname = find_mount_spec(arg)) == NULL) {
    errno = EPERM;
    return(-1);
  }
  return(quotactl(cmd, fsname, uid, addr));
}
#endif

export OSErr
OSCopyFile(spdir,sfile,dpdir,dfile)
IDirP spdir,dpdir;			/* source and destination parents */
char *sfile,*dfile;			/* source and destination file names */
{
  char spath[MAXPATHLEN];
  char dpath[MAXPATHLEN];
  struct stat stb;
  int mo;
  int err;

  OSfname(spath,spdir,sfile,F_DATA);	/* create unix style name for data */
  OSfname(dpath,dpdir,dfile,F_DATA);	/*  same for destination */

  if (DBOSI)
    printf("OSCopyFile: %s -> %s\n",spath,dpath);

  err = unix_stat(dpath,&stb);		/* see if destination exists... */
  if (err == noErr)			/* yes... it does */
    return(aeObjectExists);		/* return error... */

  /* get info on parent of destination */
  if ((err = unix_stat(pathstr(dpdir), &stb)) != noErr)
    return(err);
  mo = filemode(stb.st_mode, stb.st_uid, stb.st_gid);
  err = os_copy(spath,dpath, mo);

  if (err != noErr && DBOSI)
    printf("OSCopyFile: DATA copy failed %s\n",afperr(err));

  if (err != noErr)
    return(err);

  OSfname(spath,spdir,sfile,F_RSRC);	/* create unix style name for rsrc */
  OSfname(dpath,dpdir,dfile,F_RSRC);	/*  same for destination */
  err = os_copy(spath,dpath,mo); /* do the copy... */
  /* allow object not found */
  if (err != noErr && err != aeObjectNotFound) { /* if failure.... */
    if (DBOSI)
      printf("OSCopyFile: RSRC copy failed %s\n",afperr(err));
    (void) os_delete(dpdir,dfile,F_DATA); /*  cleanup dest files */
    return(err);
  }

  OSfname(spath,spdir,sfile,F_FNDR);	/* create unix style name for fndr */
  OSfname(dpath,dpdir,dfile,F_FNDR);	/*  same for destination */
  err = os_copy(spath,dpath,mo); /* do the copy... */
  /* allow object not found */
  if (err != noErr && err != aeObjectNotFound) {
    if (DBOSI)
      printf("OSCopyFile: FNDR copy failed %s\n",afperr(err));
    (void) os_delete(dpdir,dfile,F_DATA); /* cleanup dest files */
    (void) os_delete(dpdir,dfile,F_RSRC); /* .... */
    return(err);
  }
  OSSetMacFileName(dpdir, dfile);

  FModified(dpdir, dfile);	/* mark as modified */
#ifdef notdef
  EModified(dpdir);			/* destination dir is modified */
#endif
  return(noErr);
}

/*
 * OSErr os_copy(char *from, char *to, mo)
 *
 * Copy the file from, to the file to.  If "to" already exists then
 * overwrite.  File is created with mode "mo".
 *
 * Should probably lock the file!
 *
 */

private OSErr
os_copy(from, to, mo)
char *from,*to;
{
  int sfd,dfd,err;
  char iobuf[IOBSIZE];
  struct stat sstb;
  struct stat dstb;
  int i;

  if ((err = unix_stat(from,&sstb)) != noErr)
    return(err);

  if (S_ISDIR(sstb.st_mode)) {		/* dirs not allowed... */
    printf("os_copy: source is directory\n");
    return(aeObjectTypeErr);
  }

  if ((err=unix_open(from,0,&sfd)) != noErr) /* open source file */
    return(err);

  err = unix_stat(to,&dstb);	/* check on destination */
  if (err == noErr) {		/* file is there */
    if (sstb.st_dev == dstb.st_dev && sstb.st_ino == dstb.st_ino) {
      if (DBOSI)
	printf("os_copy: cannot copy to self\n");
      unix_close(sfd);
      return(aeParamErr);
    }
  } /* else ignore error from stat */

  err = unix_createo(to,TRUE,mo,&dfd);
  if (err != noErr) {
    printf("os_copy; create failed\n");
    (void) unix_close(sfd);
    if (err == aeObjectNotFound)	/* no destination? */
      err = aeParamErr;			/* then return this */
    return(err);
  }

  /* copy loop */
  for (i=0;;i++) {
    register int len;

    len = read(sfd,iobuf,IOBSIZE);
    if (len == 0)
      break;

    if (len < 0) {
      printf("os_copy: error during read\n");
      (void) unix_close(sfd);
      (void) unix_close(dfd);
      return(aeParamErr);		/* disk error */
    }

    if (write(dfd,iobuf,len) != len) {
      err = errno;			/* preserve error code */
      if (DBOSI)
	printf("os_copy: error on write %s\n",syserr());
      (void) unix_close(sfd);
      (void) unix_close(dfd);
      return(ItoEErr(err));
    }
    if (i % 5)
      abSleep(0, TRUE);
  }
  (void) unix_close(sfd);
  (void) unix_close(dfd);
  return(noErr);
}

export OSErr
OSCreateFile(pdir,file,delf)
IDirP pdir;
char *file;
int delf;			/* if want to delete existing file */
{
  char path[MAXPATHLEN];
  int err,derr,rerr,cerr,mo;
  struct stat stb;

  OSfname(path,pdir,file,F_DATA);	/* create data file name */

  if (DBOSI)
    printf("OSCreateFile: creating %s with %s\n",path,
	   (delf) ? "OverWrite" : "No OverWrite");
  
  err = unix_stat(pathstr(pdir),&stb);
  if (err != noErr)
    return(err);
  mo = filemode(stb.st_mode, stb.st_uid, stb.st_gid);

  /* should never get aeObjectExists if delf was true */
  OSfname(path,pdir,file,F_DATA);	/* create data fork */
  derr = unix_create(path,delf,mo);	/* using user delete flag */
  if (derr != noErr && derr != aeObjectExists) {
    if (DBOSI)
      printf("OSCreateFile: DATA fork create failed\n");
    /* previously under a conditional on delf, but not necessary */
    /* anymore because we don't get here if the object was already there */
    OSfname(path,pdir,file,F_DATA);
    cerr = unix_unlink(path);		/* clean up... */
    if (cerr != noErr && DBOSI)
      printf("OSCreateFile: cleanup failed\n");
    return(derr);
  }

  OSfname(path,pdir,file,F_RSRC);	/* try creating resource fork */
  rerr = unix_create(path,delf,mo);	/* ... */
  if (rerr != noErr && rerr != aeObjectExists && rerr != aeObjectNotFound) {
    if (DBOSI)
      printf("OSCreateFile: RSRC create failed\n");
    /* previously under a conditional on delf, but not necessary */
    /* anymore because we don't get here if the object was already there */
    OSfname(path,pdir,file,F_RSRC);
    cerr = unix_unlink(path);		/* clean up... */
    if (cerr != noErr && DBOSI)
      printf("OSCreateFile: cleanup failed\n");
    /* should we clean up data fork? */
    return(rerr);
  }

  OSfname(path,pdir,file,F_FNDR);	/* create finder fork */
  err = unix_create(path,TRUE,mo);
  /* ignore error here - exactly what should be done? */

  /* at this point, each had better be: aeObjectExists or noErr */
  if (rerr == aeObjectExists || derr == aeObjectExists)
    return(aeObjectExists);
  EModified(pdir);
  return(noErr);
}
  

export OSErr
OSOpenFork(pdir,file,mode,typ,fhdl)
IDirP pdir;				/* parent directory */
char *file;
word mode;
int typ,*fhdl;
{
  char path[MAXPATHLEN];
  char *ms;
  int mo;

  OSfname(path,pdir,file,typ);		/* expand name */

  if ((mode & ~(OFK_MRD|OFK_MWR)) != 0)
    if (DBOSI)
      printf("OSOpenFork: open mode bits are octal %o\n",mode);

  if ((mode & (OFK_MRD|OFK_MWR)) == (OFK_MRD|OFK_MWR)) {
    ms = "Read/Write";
    mo = O_RDWR;
  } else if (mode & OFK_MWR) {
    ms = "Write";
    mo = O_WRONLY;
  } else if (mode & OFK_MRD) {
    ms = "Read";
    mo = O_RDONLY;
  }

  if (DBOSI) 
    printf("OSOpenFork: Opening %s for %s\n",path,ms);

  return(unix_open(path,mo,fhdl));
}


private char *guestname = NULL;

export boolean
setguestid(nam)
char *nam;
{
  struct passwd *p;
  if ((p = getpwnam(nam)) == NULL) {
    log("Guest id %s NOT IN PASSWORD FILE",nam);
    log("Guest id %s NOT IN PASSWORD FILE",nam);
    return(FALSE);
  }
  if (p->pw_uid == 0) {
    log("Guest id %s is a root id!  NOT ALLOWED!", nam);
    log("Guest id %s is a root id!  NOT ALLOWED!", nam);
    log("Guest id %s is a root id!  NOT ALLOWED!", nam);
    return(FALSE);
  }
  if (p->pw_gid == 0) {
    log("Guest id %s is in group 0.  BE WARNED!", nam);
    log("Guest id %s is in group 0.  BE WARNED!", nam);
    log("Guest id %s is in group 0.  BE WARNED!", nam);
  }
  log("Guest id is %s, uid %d, primary gid %d",nam, p->pw_uid, p->pw_gid);
  guestname = nam;
  return(TRUE);
}

private boolean apasswdfile = FALSE;

export boolean
setpasswdfile(pw)
char *pw;
{

  if (desinit(0) < 0) {
    log("error: no des routines, so no aufs password file used");
    return(FALSE);
  }   
  apasswdfile = init_aufs_passwd(pw);
  return(apasswdfile);
}


export OSErr
OSLoginRand(nam)
char *nam;
{
  if (is_aufs_user(nam))
    return(noErr);
  return(aeParamErr);
}

export OSErr
OSLogin(nam,pwd,pwdother,uam)
char *nam,*pwd;
byte *pwdother;
int uam;
{
  struct passwd *p;
  boolean safedebug;
  byte encrypted[8];		/* 64 bits */
  byte passkey[8];		/* password is 8 bytes max */
  char *pass;

  safedebug = (DBOSI || (getuid() != 0 && geteuid() != 0));

  log("Login requested for %s (we are %srunning as root)",
      (uam == UAM_ANON) ? "<anonymous>" : nam,
      (getuid() == 0 || geteuid() == 0) ? "" : "not ");

  switch (uam) {
  case UAM_RANDNUM:
    if (!apasswdfile)
      return(aeBadUAM);
    if ((pass = user_aufs_passwd(nam)) == NULL)
      return(aeUserNotAuth);
    bzero(passkey,sizeof(passkey));		/* make sure zero */
    strncpy(passkey, pass, 8);
    dessetkey(passkey);
    /* copy the data to be encrypted */
    bcopy(pwdother, encrypted, sizeof(encrypted));
    endes(encrypted);
    if (bcmp(encrypted, pwd, 8) != 0)
      return(aeUserNotAuth);
    if ((p = aufs_unix_user(nam)) == NULL)
      return(aeUserNotAuth);
    usrgid = p->pw_gid;
    usruid = p->pw_uid;
    usrnam = (char *) malloc(strlen(p->pw_name)+1);
    strcpy(usrnam,p->pw_name);
    usrdir = (char *) malloc(strlen(p->pw_dir)+1);
    strcpy(usrdir,p->pw_dir);
    break;
  case UAM_ANON:
    if (guestname == NULL)
      return(aeParamErr);
    p = (struct passwd *)getpwnam(guestname);
    if (p == NILPWD) {
      log("Login: guest user not valid %s",guestname);
      return(aeParamErr);			/* unknown user */
    }  
    usrgid = p->pw_gid;
    usruid = p->pw_uid;
    usrnam = (char *) malloc(strlen(guestname)+1);
    strcpy(usrnam,guestname);
    usrdir = NULL;
    break;
  case UAM_CLEAR:
    if (!apasswdfile) {
      p = (struct passwd *) getpwnam(nam); /* user name */
      if (p == NILPWD) {
	log("Login: Unknown user %s",nam);
	return(aeParamErr);			/* unknown user */
      }  
      if (strcmp(crypt(pwd,p->pw_passwd),p->pw_passwd) != 0) {
	log("Login: Incorrect password for user %s",nam);
	if (!safedebug)
	  return(aeUserNotAuth);
      }
    } else {
      if ((p = aufs_unix_user(nam)) == NULL)
	return(aeUserNotAuth);
      if ((pass = user_aufs_passwd(nam)) == NULL)
	return(aeUserNotAuth);
      if (strcmp(pass,pwd) != 0)
	return(aeUserNotAuth);
    }
  
    usrgid = p->pw_gid;
    usruid = p->pw_uid;
    usrnam = (char *) malloc(strlen(p->pw_name)+1);
    strcpy(usrnam,p->pw_name);
    usrdir = (char *) malloc(strlen(p->pw_dir)+1);
    strcpy(usrdir,p->pw_dir);
    break;
  }

  if (!safedebug && setgid(usrgid) != 0) {
    log("Login: setgid failed for %s because %s",nam,syserr());
    return(aeUserNotAuth);
  }
  if ((getuid() == 0 || geteuid() == 0) && initgroups(usrnam, usrgid) < 0)
    log("OSLogin: initgroups failed for %s!: reason: %s",syserr(),usrnam);
  if ((ngroups = dogetgroups()) < 0) {
    log("OSLogin: getgroups failed for %s!: reason: %s",syserr(), usrnam);
    ngroups = 0;
  }

  if (!safedebug && setuid(usruid) != 0) {
    log("Login: setuid failed for %s because %s",nam,syserr());
    return(aeUserNotAuth);	/* or something */
  }

  log("Login: user %s, home directory %s",
      usrnam, usrdir == NULL ? "none" : usrdir);

  if (usrdir != NULL)
    VInit(usrnam,usrdir);	/* initialize volume stuff */
  return(noErr);
}

/*
 * change password.
 *
 * nice idea, but not really workable right now.
 * best we could do is fork passwd
 * AFP2.0
 *
*/
OSChangePassword(nam, pwdold, pwdnew, uam)
char *nam;
byte *pwdold;
byte *pwdnew;
int uam;
{
  return(aeCallNotSupported);
}

export word 
OSRandom()
{
  static time_t t = 0;

  if (t == 0) {
    time(&t);
#ifdef USERAND
    srand(t);
#else
    srandom(t);
#endif
  }
#ifdef USERAND
  return((word) rand());
#else
  return((word) random());
#endif
}

sdword
CurTime()
{
  return(time(0));
}

/*
 * char *tilde(char *s)
 *
 * Expands a path starting with tilde, the same as the shell.
 * Returns the expanded path.
 *
 */
export char *
tilde(s)
char *s;
{
  static char path[MAXPATHLEN];
  char *sp,*logdir();
  
  if (*s != '~')			/* start with tilde? */
    return(s);				/* no, return original */
  s++;					/* skip over tilde */
  if (*s == '\0')			/* if nothing more, return */
    return(usrdir);

  if (*s == '/') {			/* case of ~/ */
    strcpy(path,usrdir);		/* use user's dir */
    strcat(path,s);			/*  and then the remainder */
    return(path);			/* return that */
  }

  if ((sp = index(s,'/')) == NULL)	/* check for slash */
    return(logdir(s));			/*  return ~john expanded */

  *sp = '\0';				/* otherwise tie off ~bill/mac */
  strcpy(path,logdir(s));		/* copy in the expanded ~bill */
  *sp = '/';				/* ... put back slash */
  strcat(path,sp);			/* append the remainder */
  return(path);				/* and return it */
}
  
export char *
logdir(user)
char *user;
{
  struct passwd *p;

  if (strcmp(user,usrnam) == 0)
    return(usrdir);		/* already know logged in user dir */
    
  p = (struct passwd *) getpwnam(user);
  if (p != NILPWD)
    return(p->pw_dir);
  return(NULL);
}
  
private OSErr
unix_rmdir(path)
char *path;
{
  if (DBUNX)
    printf("unix_rmdir: path=%s\n",path);

  if (rmdir(path) == 0)			/* and try to delete it */
    return(noErr);

  if (DBUNX)
    printf("unix_rmdir: failed %s\n",syserr());

  return(ItoEErr(errno));
}

private OSErr
unix_unlink(path)
char *path;
{
  if (DBUNX)
    printf("unix_unlink: path=%s\n",path);

  if (unlink(path) == 0)	/* remove the file */
    return(noErr);		/* no error */

  if (DBUNX)
    printf("unix_unlink: failed %s\n",syserr());

  return(ItoEErr(errno));
}  

private OSErr
unix_rename(from,to)
char *from,*to;
{
  if (DBUNX)
    printf("unix_rename: from %s to %s\n",from,to);

#ifdef aux
  if (strcmp(from, to) == 0)
    return(noErr);
#endif
  if (rename(from,to) == 0)
    return(noErr);

  if (DBUNX)
    printf("unix_rename: failed %s\n",syserr());

  return(ItoEErr(errno));
}

private OSErr
unix_open(path,mode,fd)
char *path;
int mode;
int *fd;
{

  *fd = open(path,mode);

  if (DBUNX)
    printf("unix_open: fd=%d, mode=%d, path=%s\n",*fd,mode,path);

  if ((*fd) > 0)
    return(noErr);

  if (DBUNX)
    printf("unix_open: failed %s\n",syserr());

  return(ItoEErr(errno));
}

private OSErr
unix_close(fd)
int fd;
{
  if (DBUNX)
    printf("unix_close: fd=%d\n",fd);

  if (close(fd) == 0)
    return(noErr);

  if (DBUNX)
    printf("unix_close: failed %s\n",syserr());

  return(ItoEErr(errno));		/* this would be a problem */
}

private OSErr
unix_mkdir(path,prot)
char *path;
int prot;				/* protection */
{
  if (DBUNX)
    printf("unix_mkdir: path = %s\n",path);

  if (mkdir(path,prot) == 0)
    return(noErr);

  if (DBUNX)
    printf("unix_mkdir: failed %s\n",syserr());

  return(ItoEErr(errno));
}

/*
 * OSErr unix_create(char *path, int delf, int mode)
 *
 * Create a file.
 *
 */

private OSErr
unix_create(path,delf,mode)
char *path;
int delf;
int mode;
{
  int fd,flg;

  if (DBUNX)
    printf("unix_create: delf=%d, mode=o%o, path=%s\n",delf,mode,path);

  flg = (delf) ? O_CREAT : O_CREAT | O_EXCL;

  if ((fd = open(path,flg,mode)) != -1) {
    (void) close(fd); 
    return(noErr);
  }

  if (DBUNX)
    printf("unix_create: failed %s\n",syserr());

  return(ItoEErr(errno));
}

/*
 * OSErr unix_createo(char *path, int delf, int mode, int *fd)
 *
 * Create a file and return the open file handle.
 *
 */

private OSErr
unix_createo(path,delf,mode,fd)
char *path;
int delf;
int mode;
int *fd;
{
  int flg;

  if (DBUNX)
    printf("unix_createo: delf=%d, path=%s\n",delf,path);

  flg = (delf) ? O_CREAT : O_CREAT | O_EXCL;
  flg |= O_RDWR;

  if ((*fd = open(path,flg,mode)) != -1)
    return(noErr);

  if (DBUNX)
    printf("unix_createo: failed %s\n",syserr());

  return(ItoEErr(errno));
}

private OSErr
unix_chown(path,own,grp)
char *path;
int own,grp;
{
  char gid[20];			/* big enough */
  int pid, npid;
  int status;
#ifndef USECHOWN
  struct stat stb;
  OSErr err;
#endif

  if (DBOSI) 
    printf("unix_chown: Attempting chown %s to owner %d, group %d\n",
	   path,own,grp);
#ifndef USECHOWN
  if (usruid != 0) {		/* not root, then do it hard way */
    if (DBOSI) 
      printf("unix_chown: skipping owern, chgrp %s to group %d\n",path,grp);
    if ((err = unix_stat(path, &stb)) != noErr)
      return(err);
    if (stb.st_gid == grp)	/* naught to do */
      return(noErr);
    sprintf(gid, "%d",grp);
    if ((pid=vfork()) == 0) {
      execl("/bin/chgrp","chgrp",gid,path, 0);
      _exit(1);			/* no false eofs */
    }
    while ((npid = wait(&status)) != pid) 
      /* NULL */;
    /* right half of status is non-zero if */
    /*  (a) stopped (&0xff == 0177) */
    /* or */
    /*  (b) signaled  (0x7f != 0) */
    /*  (c) coredumped (0x80 != 0) */
    if ((status & 0xff) != 0)
      return(aeAccessDenied);	/* oh well */
    /* retcode is leftmost 8 bits */
    if ((status>>8) != 0)
      return(aeAccessDenied);	/* oh well */
    return(noErr);
  }
#endif
  /* root can do what it pleases, so can any user on sysv */
  if (chown(path, own, grp) < 0)
    return(ItoEErr(errno));
  return(noErr);
}


private OSErr
unix_chmod(path,mode)
char *path;
u_short mode;
{
  if (DBUNX)
    printf("unix_chmod: mode=o%o path=%d\n",mode,path);

  if (chmod(path,(int) mode) == 0)
    return(noErr);

  if (DBUNX)
    printf("unix_chmod: failed %s\n",syserr());

  return(ItoEErr(errno));
}

private OSErr
unix_stat(path,stb)
char *path;
struct stat *stb;
{
  if (DBUNX)
    printf("unix_stat: path=%s\n",path);

  if (stat(path,stb) == 0)
    return(noErr);

  if (DBUNX)
    printf("unix_stat: failed %s\n",syserr());

  return(ItoEErr(errno));
}

/*
 * figure out the mode a file should have based on the uid, gid, and mode
 * of its parents.  Mainly for drop folders.
 *
 * really shouldn't have to do this -- instead change the owner
 * of the file -- however: (a) bsd doesn't allow and (b) must do after
 * all file operations because we don't have handle -- mucho work --
 * if we could.
 *
*/
private int
filemode(mode, uid, gid)
int mode, uid, gid;
{
  int mo = mode & 0777;		/* convert st_mode to mode */
  if (uid != usruid) {
    /* check for conditions that would mean drop folder for us */
    /* (but, don't accept a drop folder on basis of group that is */
    /* world viewable even though it really is a drop folder for us) */
    if ((mo & 04) == 0 && (mo & 040) == 0 && OSInGroup(gid))
      mo |= 0666;		/* let everyone else read/write */
    /* We need to do this because the poor person who get's the file */
    /* can't do anything with it otherwise */
  }
  return(mo);
}

private char *
syserr()
{
  extern char *sys_errlist[];
  extern int sys_nerr;
  static char buf[50];
  int serrno;

  serrno = errno;
  if (serrno < 0 || serrno > sys_nerr) {
    sprintf(buf,"Unknown error %d",serrno);
    return(buf);
  }
  return(sys_errlist[serrno]);
}

private OSErr
ItoEErr(num)
int num;
{
  switch (num) {
  case EPERM:				/* Not owner */
    return(aeAccessDenied);
  case ENOENT:				/* No such file or directory */
    return(aeObjectNotFound);
  case EACCES:				/* Permission denied  */
    return(aeAccessDenied);
  case EEXIST:				/* File exists */
    return(aeObjectExists);
  case ENOTDIR:				/* Not a directory */
    return(aeDirNotFound);
  case EISDIR:				/* Is a directory */
    return(aeObjectTypeErr);
  case ENFILE:				/* File table overflow */
    return(aeDiskFull);
  case EMFILE:				/* Too many files open */
    return(aeTooManyFilesOpen);
  case ETXTBSY:				/* Text file busy */
    return(aeFileBusy);
  case ENOSPC:				/* No space left on device */
    return(aeDiskFull);
  case EROFS:				/* read only file system */
    return(aeAccessDenied);
  case ENOTEMPTY:
    return(aeDirNotEmpty);
#ifdef EDQUOT
  case EDQUOT:
    return(aeDiskFull);
#endif EDQUOT
  default:
    if (DBUNX)
      printf("ItoEErr: Unknown unix error code %d\n",errno);
    return(aeMiscErr);
  }
}

  
