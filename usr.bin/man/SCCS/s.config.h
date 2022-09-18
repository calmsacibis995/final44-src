h45746
s 00002/00001/00029
d D 8.4 93/12/18 15:19:23 bostic 4 3
c fix copyright header
e
s 00015/00007/00015
d D 8.3 93/11/26 11:11:35 bostic 3 2
c convert to new <sys/queue.h> structures
e
s 00001/00001/00021
d D 8.2 93/10/13 17:48:43 bostic 2 1
c add a way to specify the config file (-C)
e
s 00022/00000/00000
d D 8.1 93/10/13 13:25:13 bostic 1 0
c date and time created 93/10/13 13:25:13 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1993 The Regents of the University of California.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.
E 4
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 3
typedef struct _tag {
	TAILQ_ENTRY(_tag) q;		/* Queue of tags. */

	TAILQ_HEAD(tqh, _entry) list;	/* Queue of entries. */
	char *s;			/* Associated string. */
	size_t len;			/* Length of 's'. */
} TAG;
E 3
typedef struct _entry {
D 3
	struct queue_entry	list;		/* List of items. */
	struct queue_entry	tags;		/* List of tags. */
	char *s;				/* Associated string. */
	size_t len;				/* Length of 's'. */
E 3
I 3
	TAILQ_ENTRY(_entry) q;		/* Queue of entries. */

	char *s;			/* Associated string. */
	size_t len;			/* Length of 's'. */
E 3
} ENTRY;

D 3
extern struct queue_entry head;
E 3
I 3
TAILQ_HEAD(_head, _tag);
extern struct _head head;
E 3

D 3
ENTRY	*addlist __P((char *));
E 3
I 3
TAG	*addlist __P((char *));
E 3
D 2
void	 config __P((void));
E 2
I 2
void	 config __P((char *));
E 2
void	 debug __P((char *));
D 3
ENTRY	*getlist __P((char *));
E 3
I 3
TAG	*getlist __P((char *));
E 3
E 1
