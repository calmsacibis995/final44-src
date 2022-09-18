h08134
s 00179/00043/00886
d D 8.3 95/04/28 17:07:54 christos 11 10
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00927
d D 8.2 94/01/02 15:04:02 bostic 10 9
c time_t is a long on most machines so it should need a %ld
e
s 00002/00002/00927
d D 8.1 93/06/06 15:14:02 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00012/00913
d D 5.8 93/05/24 14:45:23 bostic 8 7
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00003/00003/00922
d D 5.7 90/12/28 18:06:51 bostic 7 6
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00924
d D 5.6 90/06/01 17:06:38 bostic 6 5
c new copyright notice
e
s 00004/00004/00931
d D 5.5 90/03/19 09:51:16 bostic 5 4
c replace malloc with emalloc
e
s 00007/00006/00928
d D 5.4 90/03/12 09:30:02 bostic 4 3
c Remove NEED_FD_SET, FD_SETSIZE, NO_WAIT3, NO_VFORK, LIBTOC
e
s 00013/00013/00921
d D 5.3 90/03/12 08:59:31 bostic 3 2
c Str_New -> strdup
e
s 00026/00015/00908
d D 5.2 90/03/11 15:38:21 bostic 2 1
c add Berkeley specific copyright notice
e
s 00923/00000/00000
d D 5.1 90/03/11 15:27:17 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * arch.c --
 *	Functions to manipulate libraries, archives and their members.
 *
 * Copyright (c) 1988, 1989 by the Regents of the University of California
E 2
I 2
/*
D 9
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
E 2
 * Copyright (c) 1988, 1989 by Adam de Boor
E 9
I 9
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 * Copyright (c) 1989 by Berkeley Softworks
I 2
 * All rights reserved.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any non-commercial purpose
 * and without fee is hereby granted, provided that the above copyright
 * notice appears in all copies.  The University of California,
 * Berkeley Softworks and Adam de Boor make no representations about
 * the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
I 2
D 6
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 6
I 6
 * %sccs.include.redist.c%
E 6
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * arch.c --
 *	Functions to manipulate libraries, archives and their members.
 *
E 2
 *	Once again, cacheing/hashing comes into play in the manipulation
 * of archives. The first time an archive is referenced, all of its members'
 * headers are read and hashed and the archive closed again. All hashed
 * archives are kept on a list which is searched each time an archive member
 * is referenced.
 *
 * The interface to this module is:
 *	Arch_ParseArchive   	Given an archive specification, return a list
 *	    	  	    	of GNode's, one for each member in the spec.
 *	    	  	    	FAILURE is returned if the specification is
 *	    	  	    	invalid for some reason.
 *
 *	Arch_Touch	    	Alter the modification time of the archive
 *	    	  	    	member described by the given node to be
 *	    	  	    	the current time.
 *
 *	Arch_TouchLib	    	Update the modification time of the library
 *	    	  	    	described by the given node. This is special
 *	    	  	    	because it also updates the modification time
 *	    	  	    	of the library's table of contents.
 *
 *	Arch_MTime	    	Find the modification time of a member of
 *	    	  	    	an archive *in the archive*. The time is also
 *	    	  	    	placed in the member's GNode. Returns the
 *	    	  	    	modification time.
 *
 *	Arch_MemTime	    	Find the modification time of a member of
 *	    	  	    	an archive. Called when the member doesn't
 *	    	  	    	already exist. Looks in the archive for the
 *	    	  	    	modification time. Returns the modification
 *	    	  	    	time.
 *
 *	Arch_FindLib	    	Search for a library along a path. The
 *	    	  	    	library name in the GNode should be in
 *	    	  	    	-l<name> format.
 *
 *	Arch_LibOODate	    	Special function to decide if a library node
 *	    	  	    	is out-of-date.
 *
 *	Arch_Init 	    	Initialize this module.
I 11
 *
 *	Arch_End 	    	Cleanup this module.
E 11
 */
D 2
#ifndef lint
static char *rcsid = "$Id: arch.c,v 1.20 89/11/14 13:43:37 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2

D 4
#include    <stdio.h>
E 4
#include    <sys/types.h>
#include    <sys/stat.h>
#include    <sys/time.h>
I 11
#include    <sys/param.h>
E 11
#include    <ctype.h>
#include    <ar.h>
I 4
D 8
#include <ranlib.h>
E 8
I 8
#include    <ranlib.h>
E 8
#include    <stdio.h>
I 11
#include    <stdlib.h>
E 11
E 4
#include    "make.h"
#include    "hash.h"
I 8
#include    "dir.h"
#include    "config.h"
E 8

static Lst	  archives;   /* Lst of archives we've already examined */

typedef struct Arch {
    char	  *name;      /* Name of archive */
    Hash_Table	  members;    /* All the members of the archive described
			       * by <name, struct ar_hdr *> key/value pairs */
} Arch;

D 8
static FILE *ArchFindMember();
E 8
I 8
D 11
static int ArchFindArchive __P((Arch *, char *));
E 11
I 11
static int ArchFindArchive __P((ClientData, ClientData));
static void ArchFree __P((ClientData));
E 11
static struct ar_hdr *ArchStatMember __P((char *, char *, Boolean));
static FILE *ArchFindMember __P((char *, char *, struct ar_hdr *, char *));
E 8
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
I 11
 * ArchFree --
 *	Free memory used by an archive
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static void
ArchFree(ap)
    ClientData ap;
{
    Arch *a = (Arch *) ap;
    Hash_Search	  search;
    Hash_Entry	  *entry;
    
    /* Free memory from hash entries */ 
    for (entry = Hash_EnumFirst(&a->members, &search);
	 entry != (Hash_Entry *)NULL;
	 entry = Hash_EnumNext(&search))
	free((Address) Hash_GetValue (entry));

    free(a->name);
    Hash_DeleteTable(&a->members);
    free((Address) a);
}
	


/*-
 *-----------------------------------------------------------------------
E 11
 * Arch_ParseArchive --
 *	Parse the archive specification in the given line and find/create
 *	the nodes for the specified archive members, placing their nodes
 *	on the given list.
 *
 * Results:
 *	SUCCESS if it was a valid specification. The linePtr is updated
 *	to point to the first non-space after the archive spec. The
 *	nodes for the members are placed on the given list.
 *
 * Side Effects:
 *	Some nodes may be created. The given list is extended.
 *
 *-----------------------------------------------------------------------
 */
ReturnStatus
Arch_ParseArchive (linePtr, nodeLst, ctxt)
    char	    **linePtr;      /* Pointer to start of specification */
    Lst	    	    nodeLst;   	    /* Lst on which to place the nodes */
    GNode   	    *ctxt;  	    /* Context in which to expand variables */
{
    register char   *cp;	    /* Pointer into line */
    GNode	    *gn;     	    /* New node */
    char	    *libName;  	    /* Library-part of specification */
    char	    *memName;  	    /* Member-part of specification */
D 8
    char	    nameBuf[BSIZE]; /* temporary place for node name */
E 8
I 8
    char	    nameBuf[MAKE_BSIZE]; /* temporary place for node name */
E 8
    char	    saveChar;  	    /* Ending delimiter of member-name */
    Boolean 	    subLibName;	    /* TRUE if libName should have/had
				     * variable substitution performed on it */

    libName = *linePtr;
    
    subLibName = FALSE;

    for (cp = libName; *cp != '(' && *cp != '\0'; cp++) {
	if (*cp == '$') {
	    /*
	     * Variable spec, so call the Var module to parse the puppy
	     * so we can safely advance beyond it...
	     */
	    int 	length;
	    Boolean	freeIt;
	    char	*result;
	    
	    result=Var_Parse(cp, ctxt, TRUE, &length, &freeIt);
	    if (result == var_Error) {
		return(FAILURE);
	    } else {
		subLibName = TRUE;
	    }
	    
	    if (freeIt) {
		free(result);
	    }
	    cp += length-1;
	}
    }

    *cp++ = '\0';
    if (subLibName) {
D 8
	libName = Var_Subst(libName, ctxt, TRUE);
E 8
I 8
	libName = Var_Subst(NULL, libName, ctxt, TRUE);
E 8
    }
    

D 8
    while (1) {
E 8
I 8
    for (;;) {
E 8
	/*
	 * First skip to the start of the member's name, mark that
	 * place and skip to the end of it (either white-space or
	 * a close paren).
	 */
	Boolean	doSubst = FALSE; /* TRUE if need to substitute in memName */

	while (*cp != '\0' && *cp != ')' && isspace (*cp)) {
	    cp++;
	}
	memName = cp;
	while (*cp != '\0' && *cp != ')' && !isspace (*cp)) {
	    if (*cp == '$') {
		/*
		 * Variable spec, so call the Var module to parse the puppy
		 * so we can safely advance beyond it...
		 */
		int 	length;
		Boolean	freeIt;
		char	*result;

		result=Var_Parse(cp, ctxt, TRUE, &length, &freeIt);
		if (result == var_Error) {
		    return(FAILURE);
		} else {
		    doSubst = TRUE;
		}

		if (freeIt) {
		    free(result);
		}
		cp += length;
	    } else {
		cp++;
	    }
	}

	/*
	 * If the specification ends without a closing parenthesis,
	 * chances are there's something wrong (like a missing backslash),
	 * so it's better to return failure than allow such things to happen
	 */
	if (*cp == '\0') {
	    printf("No closing parenthesis in archive specification\n");
	    return (FAILURE);
	}

	/*
	 * If we didn't move anywhere, we must be done
	 */
	if (cp == memName) {
	    break;
	}

	saveChar = *cp;
	*cp = '\0';

	/*
	 * XXX: This should be taken care of intelligently by
	 * SuffExpandChildren, both for the archive and the member portions.
	 */
	/*
	 * If member contains variables, try and substitute for them.
	 * This will slow down archive specs with dynamic sources, of course,
	 * since we'll be (non-)substituting them three times, but them's
	 * the breaks -- we need to do this since SuffExpandChildren calls
	 * us, otherwise we could assume the thing would be taken care of
	 * later.
	 */
	if (doSubst) {
	    char    *buf;
	    char    *sacrifice;
	    char    *oldMemName = memName;
	    
D 8
	    memName = Var_Subst(memName, ctxt, TRUE);
E 8
I 8
	    memName = Var_Subst(NULL, memName, ctxt, TRUE);
E 8

	    /*
	     * Now form an archive spec and recurse to deal with nested
	     * variables and multi-word variable values.... The results
	     * are just placed at the end of the nodeLst we're returning.
	     */
D 5
	    buf=sacrifice=(char *)malloc(strlen(memName)+strlen(libName)+3);
E 5
I 5
	    buf = sacrifice = emalloc(strlen(memName)+strlen(libName)+3);
E 5

	    sprintf(buf, "%s(%s)", libName, memName);

D 8
	    if (index(memName, '$') && strcmp(memName, oldMemName) == 0) {
E 8
I 8
	    if (strchr(memName, '$') && strcmp(memName, oldMemName) == 0) {
E 8
		/*
		 * Must contain dynamic sources, so we can't deal with it now.
		 * Just create an ARCHV node for the thing and let
		 * SuffExpandChildren handle it...
		 */
		gn = Targ_FindNode(buf, TARG_CREATE);

		if (gn == NILGNODE) {
		    free(buf);
		    return(FAILURE);
		} else {
		    gn->type |= OP_ARCHV;
		    (void)Lst_AtEnd(nodeLst, (ClientData)gn);
		}
	    } else if (Arch_ParseArchive(&sacrifice, nodeLst, ctxt)!=SUCCESS) {
		/*
		 * Error in nested call -- free buffer and return FAILURE
		 * ourselves.
		 */
		free(buf);
		return(FAILURE);
	    }
	    /*
	     * Free buffer and continue with our work.
	     */
	    free(buf);
	} else if (Dir_HasWildcards(memName)) {
	    Lst	  members = Lst_Init(FALSE);
	    char  *member;

	    Dir_Expand(memName, dirSearchPath, members);
	    while (!Lst_IsEmpty(members)) {
		member = (char *)Lst_DeQueue(members);
		
		sprintf(nameBuf, "%s(%s)", libName, member);
		free(member);
		gn = Targ_FindNode (nameBuf, TARG_CREATE);
		if (gn == NILGNODE) {
		    return (FAILURE);
		} else {
		    /*
		     * We've found the node, but have to make sure the rest of
		     * the world knows it's an archive member, without having
		     * to constantly check for parentheses, so we type the
		     * thing with the OP_ARCHV bit before we place it on the
		     * end of the provided list.
		     */
		    gn->type |= OP_ARCHV;
		    (void) Lst_AtEnd (nodeLst, (ClientData)gn);
		}
	    }
	    Lst_Destroy(members, NOFREE);
	} else {
	    sprintf(nameBuf, "%s(%s)", libName, memName);
	    gn = Targ_FindNode (nameBuf, TARG_CREATE);
	    if (gn == NILGNODE) {
		return (FAILURE);
	    } else {
		/*
		 * We've found the node, but have to make sure the rest of the
		 * world knows it's an archive member, without having to
		 * constantly check for parentheses, so we type the thing with
		 * the OP_ARCHV bit before we place it on the end of the
		 * provided list.
		 */
		gn->type |= OP_ARCHV;
		(void) Lst_AtEnd (nodeLst, (ClientData)gn);
	    }
	}
	if (doSubst) {
	    free(memName);
	}
	
	*cp = saveChar;
    }

    /*
     * If substituted libName, free it now, since we need it no longer.
     */
    if (subLibName) {
	free(libName);
    }

    /*
     * We promised the pointer would be set up at the next non-space, so
     * we must advance cp there before setting *linePtr... (note that on
     * entrance to the loop, cp is guaranteed to point at a ')')
     */
    do {
	cp++;
    } while (*cp != '\0' && isspace (*cp));

    *linePtr = cp;
    return (SUCCESS);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ArchFindArchive --
 *	See if the given archive is the one we are looking for. Called
 *	From ArchStatMember and ArchFindMember via Lst_Find.
 *
 * Results:
 *	0 if it is, non-zero if it isn't.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
static int
ArchFindArchive (ar, archName)
D 11
    Arch	  *ar;	      	  /* Current list element */
    char	  *archName;  	  /* Name we want */
E 11
I 11
    ClientData	  ar;	      	  /* Current list element */
    ClientData	  archName;  	  /* Name we want */
E 11
{
D 11
    return (strcmp (archName, ar->name));
E 11
I 11
    return (strcmp ((char *) archName, ((Arch *) ar)->name));
E 11
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ArchStatMember --
 *	Locate a member of an archive, given the path of the archive and
 *	the path of the desired member.
 *
 * Results:
 *	A pointer to the current struct ar_hdr structure for the member. Note
 *	That no position is returned, so this is not useful for touching
 *	archive members. This is mostly because we have no assurances that
 *	The archive will remain constant after we read all the headers, so
 *	there's not much point in remembering the position...
 *
 * Side Effects:
 *
 *-----------------------------------------------------------------------
 */
static struct ar_hdr *
ArchStatMember (archive, member, hash)
    char	  *archive;   /* Path to the archive */
    char	  *member;    /* Name of member. If it is a path, only the
			       * last component is used. */
    Boolean	  hash;	      /* TRUE if archive should be hashed if not
    			       * already so. */
{
#define AR_MAX_NAME_LEN	    (sizeof(arh.ar_name)-1)
    FILE *	  arch;	      /* Stream to archive */
    int		  size;       /* Size of archive member */
    char	  *cp;	      /* Useful character pointer */
    char	  magic[SARMAG];
D 11
    int		  len;
E 11
    LstNode	  ln;	      /* Lst member containing archive descriptor */
    Arch	  *ar;	      /* Archive descriptor */
    Hash_Entry	  *he;	      /* Entry containing member's description */
    struct ar_hdr arh;        /* archive-member header for reading archive */
D 11
    char	  memName[AR_MAX_NAME_LEN+1];
    	    	    	    /* Current member name while hashing. The name is
			     * truncated to AR_MAX_NAME_LEN bytes, but we need
			     * room for the null byte... */
    char    	  copy[AR_MAX_NAME_LEN+1];
    	    	    	    /* Holds copy of last path element from member, if
			     * it has to be truncated, so we don't have to
			     * figure it out again once the table is hashed. */
E 11
I 11
    char	  memName[MAXPATHLEN+1];
    	    	    	    /* Current member name while hashing. */
E 11

    /*
     * Because of space constraints and similar things, files are archived
     * using their final path components, not the entire thing, so we need
     * to point 'member' to the final component, if there is one, to make
     * the comparisons easier...
     */
D 8
    cp = rindex (member, '/');
E 8
I 8
    cp = strrchr (member, '/');
E 8
    if (cp != (char *) NULL) {
	member = cp + 1;
    }
D 11
    len = strlen (member);
    if (len > AR_MAX_NAME_LEN) {
	len = AR_MAX_NAME_LEN;
	strncpy(copy, member, AR_MAX_NAME_LEN);
	copy[AR_MAX_NAME_LEN] = '\0';
	member = copy;
    }
E 11

    ln = Lst_Find (archives, (ClientData) archive, ArchFindArchive);
    if (ln != NILLNODE) {
	ar = (Arch *) Lst_Datum (ln);

D 7
	he = Hash_FindEntry (&ar->members, (Address) member);
E 7
I 7
	he = Hash_FindEntry (&ar->members, member);
E 7

	if (he != (Hash_Entry *) NULL) {
	    return ((struct ar_hdr *) Hash_GetValue (he));
	} else {
I 11
	    /* Try truncated name */
	    char copy[AR_MAX_NAME_LEN+1];
	    int len = strlen (member);

	    if (len > AR_MAX_NAME_LEN) {
		len = AR_MAX_NAME_LEN;
		strncpy(copy, member, AR_MAX_NAME_LEN);
		copy[AR_MAX_NAME_LEN] = '\0';
	    }
	    if (he = Hash_FindEntry (&ar->members, copy))
		return ((struct ar_hdr *) Hash_GetValue (he));
E 11
	    return ((struct ar_hdr *) NULL);
	}
    }

    if (!hash) {
	/*
	 * Caller doesn't want the thing hashed, just use ArchFindMember
	 * to read the header for the member out and close down the stream
	 * again. Since the archive is not to be hashed, we assume there's
	 * no need to allocate extra room for the header we're returning,
	 * so just declare it static.
	 */
	 static struct ar_hdr	sarh;

	 arch = ArchFindMember(archive, member, &sarh, "r");

	 if (arch == (FILE *)NULL) {
	    return ((struct ar_hdr *)NULL);
	} else {
	    fclose(arch);
	    return (&sarh);
	}
    }

    /*
     * We don't have this archive on the list yet, so we want to find out
     * everything that's in it and cache it so we can get at it quickly.
     */
    arch = fopen (archive, "r");
    if (arch == (FILE *) NULL) {
	return ((struct ar_hdr *) NULL);
    }
    
    /*
     * We use the ARMAG string to make sure this is an archive we
     * can handle...
     */
    if ((fread (magic, SARMAG, 1, arch) != 1) ||
    	(strncmp (magic, ARMAG, SARMAG) != 0)) {
	    fclose (arch);
	    return ((struct ar_hdr *) NULL);
    }

D 5
    ar = (Arch *) malloc (sizeof (Arch));
E 5
I 5
    ar = (Arch *)emalloc (sizeof (Arch));
E 5
D 3
    ar->name = Str_New (archive);
E 3
I 3
    ar->name = strdup (archive);
E 3
D 7
    Hash_InitTable (&ar->members, -1, HASH_STRING_KEYS);
E 7
I 7
    Hash_InitTable (&ar->members, -1);
E 7
    memName[AR_MAX_NAME_LEN] = '\0';
    
    while (fread ((char *)&arh, sizeof (struct ar_hdr), 1, arch) == 1) {
	if (strncmp ( arh.ar_fmag, ARFMAG, sizeof (arh.ar_fmag)) != 0) {
				 /*
				  * The header is bogus, so the archive is bad
				  * and there's no way we can recover...
				  */
				 fclose (arch);
				 Hash_DeleteTable (&ar->members);
				 free ((Address)ar);
				 return ((struct ar_hdr *) NULL);
	} else {
	    (void) strncpy (memName, arh.ar_name, sizeof(arh.ar_name));
	    for (cp = &memName[AR_MAX_NAME_LEN]; *cp == ' '; cp--) {
		continue;
	    }
	    cp[1] = '\0';

D 3
	    he = Hash_CreateEntry (&ar->members, Str_New (memName),
E 3
I 3
D 11
	    he = Hash_CreateEntry (&ar->members, strdup (memName),
E 3
				   (Boolean *)NULL);
E 11
I 11
#ifdef AR_EFMT1
	    /*
	     * BSD 4.4 extended AR format: #1/<namelen>, with name as the
	     * first <namelen> bytes of the file
	     */
	    if (strncmp(memName, AR_EFMT1, sizeof(AR_EFMT1) - 1) == 0 &&
		isdigit(memName[sizeof(AR_EFMT1) - 1])) {

		unsigned int elen = atoi(&memName[sizeof(AR_EFMT1)-1]);

		if (elen > MAXPATHLEN) {
			fclose (arch);
			Hash_DeleteTable (&ar->members);
			free ((Address)ar);
			return ((struct ar_hdr *) NULL);
		}
		if (fread (memName, elen, 1, arch) != 1) {
			fclose (arch);
			Hash_DeleteTable (&ar->members);
			free ((Address)ar);
			return ((struct ar_hdr *) NULL);
		}
		memName[elen] = '\0';
		fseek (arch, -elen, 1);
		if (DEBUG(ARCH) || DEBUG(MAKE)) {
		    printf("ArchStat: Extended format entry for %s\n", memName);
		}
	    }
#endif

	    he = Hash_CreateEntry (&ar->members, memName, (Boolean *)NULL);
E 11
D 5
	    Hash_SetValue (he, (ClientData)malloc (sizeof (struct ar_hdr)));
E 5
I 5
	    Hash_SetValue (he, (ClientData)emalloc (sizeof (struct ar_hdr)));
E 5
D 8
	    bcopy ((Address)&arh, (Address)Hash_GetValue (he), 
E 8
I 8
D 11
	    memcpy ((Address)Hash_GetValue (he), (Address)&arh, 
E 11
I 11
	    memcpy ((Address)Hash_GetValue (he), (Address)&arh,
E 11
E 8
		sizeof (struct ar_hdr));
	}
	/*
	 * We need to advance the stream's pointer to the start of the
	 * next header. Files are padded with newlines to an even-byte
	 * boundary, so we need to extract the size of the file from the
	 * 'size' field of the header and round it up during the seek.
	 */
	arh.ar_size[sizeof(arh.ar_size)-1] = '\0';
D 11
	(void) sscanf (arh.ar_size, "%10d", &size);
E 11
I 11
	size = (int) strtol(arh.ar_size, NULL, 10);
E 11
	fseek (arch, (size + 1) & ~1, 1);
    }

    fclose (arch);

    (void) Lst_AtEnd (archives, (ClientData) ar);

    /*
     * Now that the archive has been read and cached, we can look into
     * the hash table to find the desired member's header.
     */
D 7
    he = Hash_FindEntry (&ar->members, (Address) member);
E 7
I 7
    he = Hash_FindEntry (&ar->members, member);
E 7

    if (he != (Hash_Entry *) NULL) {
	return ((struct ar_hdr *) Hash_GetValue (he));
    } else {
	return ((struct ar_hdr *) NULL);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * ArchFindMember --
 *	Locate a member of an archive, given the path of the archive and
 *	the path of the desired member. If the archive is to be modified,
 *	the mode should be "r+", if not, it should be "r".
 *
 * Results:
 *	An FILE *, opened for reading and writing, positioned at the
 *	start of the member's struct ar_hdr, or NULL if the member was
 *	nonexistent. The current struct ar_hdr for member.
 *
 * Side Effects:
 *	The passed struct ar_hdr structure is filled in.
 *
 *-----------------------------------------------------------------------
 */
static FILE *
ArchFindMember (archive, member, arhPtr, mode)
    char	  *archive;   /* Path to the archive */
    char	  *member;    /* Name of member. If it is a path, only the
			       * last component is used. */
    struct ar_hdr *arhPtr;    /* Pointer to header structure to be filled in */
    char	  *mode;      /* The mode for opening the stream */
{
    FILE *	  arch;	      /* Stream to archive */
    int		  size;       /* Size of archive member */
    char	  *cp;	      /* Useful character pointer */
    char	  magic[SARMAG];
D 11
    int		  len;
E 11
I 11
    int		  len, tlen;
E 11

    arch = fopen (archive, mode);
    if (arch == (FILE *) NULL) {
	return ((FILE *) NULL);
    }
    
    /*
     * We use the ARMAG string to make sure this is an archive we
     * can handle...
     */
    if ((fread (magic, SARMAG, 1, arch) != 1) ||
    	(strncmp (magic, ARMAG, SARMAG) != 0)) {
	    fclose (arch);
	    return ((FILE *) NULL);
    }

    /*
     * Because of space constraints and similar things, files are archived
     * using their final path components, not the entire thing, so we need
     * to point 'member' to the final component, if there is one, to make
     * the comparisons easier...
     */
D 8
    cp = rindex (member, '/');
E 8
I 8
    cp = strrchr (member, '/');
E 8
    if (cp != (char *) NULL) {
	member = cp + 1;
    }
D 11
    len = strlen (member);
E 11
I 11
    len = tlen = strlen (member);
E 11
    if (len > sizeof (arhPtr->ar_name)) {
D 11
	len = sizeof (arhPtr->ar_name);
E 11
I 11
	tlen = sizeof (arhPtr->ar_name);
E 11
    }
    
    while (fread ((char *)arhPtr, sizeof (struct ar_hdr), 1, arch) == 1) {
	if (strncmp(arhPtr->ar_fmag, ARFMAG, sizeof (arhPtr->ar_fmag) ) != 0) {
	     /*
	      * The header is bogus, so the archive is bad
	      * and there's no way we can recover...
	      */
	     fclose (arch);
	     return ((FILE *) NULL);
D 11
	} else if (strncmp (member, arhPtr->ar_name, len) == 0) {
E 11
I 11
	} else if (strncmp (member, arhPtr->ar_name, tlen) == 0) {
E 11
	    /*
	     * If the member's name doesn't take up the entire 'name' field,
	     * we have to be careful of matching prefixes. Names are space-
	     * padded to the right, so if the character in 'name' at the end
	     * of the matched string is anything but a space, this isn't the
	     * member we sought.
	     */
D 11
	    if (len != sizeof(arhPtr->ar_name) && arhPtr->ar_name[len] != ' '){
		continue;
E 11
I 11
	    if (tlen != sizeof(arhPtr->ar_name) && arhPtr->ar_name[tlen] != ' '){
		goto skip;
E 11
	    } else {
		/*
		 * To make life easier, we reposition the file at the start
		 * of the header we just read before we return the stream.
		 * In a more general situation, it might be better to leave
		 * the file at the actual member, rather than its header, but
		 * not here...
		 */
		fseek (arch, -sizeof(struct ar_hdr), 1);
		return (arch);
	    }
D 11
	} else {
E 11
I 11
	} else
#ifdef AR_EFMT1
		/*
		 * BSD 4.4 extended AR format: #1/<namelen>, with name as the
		 * first <namelen> bytes of the file
		 */
	    if (strncmp(arhPtr->ar_name, AR_EFMT1,
					sizeof(AR_EFMT1) - 1) == 0 &&
		isdigit(arhPtr->ar_name[sizeof(AR_EFMT1) - 1])) {

		unsigned int elen = atoi(&arhPtr->ar_name[sizeof(AR_EFMT1)-1]);
		char ename[MAXPATHLEN];

		if (elen > MAXPATHLEN) {
			fclose (arch);
			return NULL;
		}
		if (fread (ename, elen, 1, arch) != 1) {
			fclose (arch);
			return NULL;
		}
		ename[elen] = '\0';
		if (DEBUG(ARCH) || DEBUG(MAKE)) {
		    printf("ArchFind: Extended format entry for %s\n", ename);
		}
		if (strncmp(ename, member, len) == 0) {
			/* Found as extended name */
			fseek (arch, -sizeof(struct ar_hdr) - elen, 1);
			return (arch);
		}
		fseek (arch, -elen, 1);
		goto skip;
	} else
#endif
	{
skip:
E 11
	    /*
	     * This isn't the member we're after, so we need to advance the
	     * stream's pointer to the start of the next header. Files are
	     * padded with newlines to an even-byte boundary, so we need to
	     * extract the size of the file from the 'size' field of the
	     * header and round it up during the seek.
	     */
	    arhPtr->ar_size[sizeof(arhPtr->ar_size)-1] = '\0';
D 11
	    (void)sscanf (arhPtr->ar_size, "%10d", &size);
E 11
I 11
	    size = (int) strtol(arhPtr->ar_size, NULL, 10);
E 11
	    fseek (arch, (size + 1) & ~1, 1);
	}
    }

    /*
     * We've looked everywhere, but the member is not to be found. Close the
     * archive and return NULL -- an error.
     */
    fclose (arch);
    return ((FILE *) NULL);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_Touch --
 *	Touch a member of an archive.
 *
 * Results:
 *	The 'time' field of the member's header is updated.
 *
 * Side Effects:
 *	The modification time of the entire archive is also changed.
 *	For a library, this could necessitate the re-ranlib'ing of the
 *	whole thing.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_Touch (gn)
    GNode	  *gn;	  /* Node of member to touch */
{
    FILE *	  arch;	  /* Stream open to archive, positioned properly */
    struct ar_hdr arh;	  /* Current header describing member */
I 11
    char *p1, *p2;
E 11

D 11
    arch = ArchFindMember(Var_Value (ARCHIVE, gn),
			  Var_Value (TARGET, gn),
E 11
I 11
    arch = ArchFindMember(Var_Value (ARCHIVE, gn, &p1),
			  Var_Value (TARGET, gn, &p2),
E 11
			  &arh, "r+");
I 11
    if (p1)
	free(p1);
    if (p2)
	free(p2);
E 11
D 10
    sprintf(arh.ar_date, "%-12d", now);
E 10
I 10
    sprintf(arh.ar_date, "%-12ld", (long) now);
E 10

    if (arch != (FILE *) NULL) {
	(void)fwrite ((char *)&arh, sizeof (struct ar_hdr), 1, arch);
	fclose (arch);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_TouchLib --
 *	Given a node which represents a library, touch the thing, making
 *	sure that the table of contents also is touched.
 *
 * Results:
 *	None.
 *
 * Side Effects:
D 4
 *	Both the modification time of the library and of the LIBTOC
E 4
I 4
 *	Both the modification time of the library and of the RANLIBMAG
E 4
 *	member are set to 'now'.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_TouchLib (gn)
    GNode	    *gn;      	/* The node of the library to touch */
{
    FILE *	    arch;	/* Stream open to archive */
    struct ar_hdr   arh;      	/* Header describing table of contents */
    struct timeval  times[2];	/* Times for utimes() call */

D 4
    arch = ArchFindMember (gn->path, LIBTOC, &arh, "r+");
E 4
I 4
    arch = ArchFindMember (gn->path, RANLIBMAG, &arh, "r+");
E 4
D 10
    sprintf(arh.ar_date, "%-12d", now);
E 10
I 10
    sprintf(arh.ar_date, "%-12ld", (long) now);
E 10

    if (arch != (FILE *) NULL) {
	(void)fwrite ((char *)&arh, sizeof (struct ar_hdr), 1, arch);
	fclose (arch);

	times[0].tv_sec = times[1].tv_sec = now;
	times[0].tv_usec = times[1].tv_usec = 0;
	utimes(gn->path, times);
    }
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_MTime --
 *	Return the modification time of a member of an archive.
 *
 * Results:
 *	The modification time (seconds).
 *
 * Side Effects:
 *	The mtime field of the given node is filled in with the value
 *	returned by the function.
 *
 *-----------------------------------------------------------------------
 */
int
Arch_MTime (gn)
    GNode	  *gn;	      /* Node describing archive member */
{
    struct ar_hdr *arhPtr;    /* Header of desired member */
    int		  modTime;    /* Modification time as an integer */
I 11
    char *p1, *p2;
E 11

D 11
    arhPtr = ArchStatMember (Var_Value (ARCHIVE, gn),
			     Var_Value (TARGET, gn),
E 11
I 11
    arhPtr = ArchStatMember (Var_Value (ARCHIVE, gn, &p1),
			     Var_Value (TARGET, gn, &p2),
E 11
			     TRUE);
I 11
    if (p1)
	free(p1);
    if (p2)
	free(p2);

E 11
    if (arhPtr != (struct ar_hdr *) NULL) {
D 11
	(void)sscanf (arhPtr->ar_date, "%12d", &modTime);
E 11
I 11
	modTime = (int) strtol(arhPtr->ar_date, NULL, 10);
E 11
    } else {
	modTime = 0;
    }

    gn->mtime = modTime;
    return (modTime);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_MemMTime --
 *	Given a non-existent archive member's node, get its modification
 *	time from its archived form, if it exists.
 *
 * Results:
 *	The modification time.
 *
 * Side Effects:
 *	The mtime field is filled in.
 *
 *-----------------------------------------------------------------------
 */
int
Arch_MemMTime (gn)
    GNode   	  *gn;
{
    LstNode 	  ln;
    GNode   	  *pgn;
    char    	  *nameStart,
		  *nameEnd;

    if (Lst_Open (gn->parents) != SUCCESS) {
	gn->mtime = 0;
	return (0);
    }
    while ((ln = Lst_Next (gn->parents)) != NILLNODE) {
	pgn = (GNode *) Lst_Datum (ln);

	if (pgn->type & OP_ARCHV) {
	    /*
	     * If the parent is an archive specification and is being made
	     * and its member's name matches the name of the node we were
	     * given, record the modification time of the parent in the
	     * child. We keep searching its parents in case some other
	     * parent requires this child to exist...
	     */
D 8
	    nameStart = index (pgn->name, '(') + 1;
	    nameEnd = index (nameStart, ')');
E 8
I 8
	    nameStart = strchr (pgn->name, '(') + 1;
	    nameEnd = strchr (nameStart, ')');
E 8

	    if (pgn->make &&
		strncmp(nameStart, gn->name, nameEnd - nameStart) == 0) {
				     gn->mtime = Arch_MTime(pgn);
	    }
	} else if (pgn->make) {
	    /*
	     * Something which isn't a library depends on the existence of
	     * this target, so it needs to exist.
	     */
	    gn->mtime = 0;
	    break;
	}
    }

    Lst_Close (gn->parents);

    return (gn->mtime);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_FindLib --
 *	Search for a library along the given search path. 
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The node's 'path' field is set to the found path (including the
 *	actual file name, not -l...). If the system can handle the -L
 *	flag when linking (or we cannot find the library), we assume that
 *	the user has placed the .LIBRARIES variable in the final linking
 *	command (or the linker will know where to find it) and set the
 *	TARGET variable for this node to be the node's name. Otherwise,
 *	we set the TARGET variable to be the full path of the library,
 *	as returned by Dir_FindFile.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_FindLib (gn, path)
    GNode	    *gn;	      /* Node of library to find */
    Lst	    	    path;	      /* Search path */
{
    char	    *libName;   /* file name for archive */

D 5
    libName = (char *)malloc (strlen (gn->name) + 6 - 2);
E 5
I 5
    libName = (char *)emalloc (strlen (gn->name) + 6 - 2);
E 5
    sprintf(libName, "lib%s.a", &gn->name[2]);

    gn->path = Dir_FindFile (libName, path);

    free (libName);

#ifdef LIBRARIES
    Var_Set (TARGET, gn->name, gn);
#else
    Var_Set (TARGET, gn->path == (char *) NULL ? gn->name : gn->path, gn);
#endif LIBRARIES
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_LibOODate --
 *	Decide if a node with the OP_LIB attribute is out-of-date. Called
 *	from Make_OODate to make its life easier.
 *
 *	There are several ways for a library to be out-of-date that are
 *	not available to ordinary files. In addition, there are ways
 *	that are open to regular files that are not available to
 *	libraries. A library that is only used as a source is never
 *	considered out-of-date by itself. This does not preclude the
 *	library's modification time from making its parent be out-of-date.
 *	A library will be considered out-of-date for any of these reasons,
 *	given that it is a target on a dependency line somewhere:
 *	    Its modification time is less than that of one of its
 *	    	  sources (gn->mtime < gn->cmtime).
 *	    Its modification time is greater than the time at which the
 *	    	  make began (i.e. it's been modified in the course
 *	    	  of the make, probably by archiving).
D 11
 *	    Its modification time doesn't agree with the modification
D 4
 *	    	  time of its LIBTOC member (i.e. its table of contents
E 4
I 4
 *	    	  time of its RANLIBMAG member (i.e. its table of contents
E 4
 *	    	  is out-of-date).
E 11
I 11
 *	    The modification time of one of its sources is greater than
 *		  the one of its RANLIBMAG member (i.e. its table of contents
 *	    	  is out-of-date). We don't compare of the archive time
 *		  vs. TOC time because they can be too close. In my
 *		  opinion we should not bother with the TOC at all since
 *		  this is used by 'ar' rules that affect the data contents
 *		  of the archive, not by ranlib rules, which affect the
 *		  TOC. 
E 11
 *
D 11
 *
E 11
 * Results:
 *	TRUE if the library is out-of-date. FALSE otherwise.
 *
 * Side Effects:
 *	The library will be hashed if it hasn't been already.
 *
 *-----------------------------------------------------------------------
 */
Boolean
Arch_LibOODate (gn)
    GNode   	  *gn;  	/* The library's graph node */
{
    Boolean 	  oodate;
    
    if (OP_NOP(gn->type) && Lst_IsEmpty(gn->children)) {
	oodate = FALSE;
    } else if ((gn->mtime > now) || (gn->mtime < gn->cmtime)) {
	oodate = TRUE;
    } else {
	struct ar_hdr  	*arhPtr;    /* Header for __.SYMDEF */
	int 	  	modTimeTOC; /* The table-of-contents's mod time */

D 4
	arhPtr = ArchStatMember (gn->path, LIBTOC, FALSE);
E 4
I 4
	arhPtr = ArchStatMember (gn->path, RANLIBMAG, FALSE);
E 4

	if (arhPtr != (struct ar_hdr *)NULL) {
D 11
	    (void)sscanf (arhPtr->ar_date, "%12d", &modTimeTOC);
E 11
I 11
	    modTimeTOC = (int) strtol(arhPtr->ar_date, NULL, 10);
E 11

	    if (DEBUG(ARCH) || DEBUG(MAKE)) {
D 4
		printf("%s modified %s...", LIBTOC, Targ_FmtTime(modTimeTOC));
E 4
I 4
		printf("%s modified %s...", RANLIBMAG, Targ_FmtTime(modTimeTOC));
E 4
	    }
D 11
	    oodate = (gn->mtime > modTimeTOC);
E 11
I 11
	    oodate = (gn->cmtime > modTimeTOC);
E 11
	} else {
	    /*
	     * A library w/o a table of contents is out-of-date
	     */
	    if (DEBUG(ARCH) || DEBUG(MAKE)) {
		printf("No t.o.c....");
	    }
	    oodate = TRUE;
	}
    }
    return (oodate);
}
D 3

E 3
I 3

E 3
/*-
 *-----------------------------------------------------------------------
 * Arch_Init --
 *	Initialize things for this module.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The 'archives' list is initialized.
 *
 *-----------------------------------------------------------------------
 */
void
Arch_Init ()
{
    archives = Lst_Init (FALSE);
I 11
}



/*-
 *-----------------------------------------------------------------------
 * Arch_End --
 *	Cleanup things for this module.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The 'archives' list is freed
 *
 *-----------------------------------------------------------------------
 */
void
Arch_End ()
{
    Lst_Destroy(archives, ArchFree);
E 11
}
E 1
