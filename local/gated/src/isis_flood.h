/*
 *  isis_flood.h,v 1.11 1993/01/07 22:39:18 jch Exp
 */

/* %(Copyright.header) */


#ifndef _flood_h
#define _flood_h

/*
 *	Quick summary of critical information about the LSP
 */
typedef struct _LSSignature {
	LSPID		id;				/* ID of LSP originator */
	u_long		seqNum;
	u_short		lifetime;		/* reasonably up-to-date remaining time */
	int			level;			/* 1 or 2 */
	u_short		checksum;
} LSSignature;

/*
 *	Structure to hold each LSP in the database.
 */
typedef struct _LSEntry {
	DLList		links;				/* link: timeout list */
	LSSignature	signature;
	u_short		originalLifetime;		/* value of lifetime when received */
	u_short		remainingTime;			/* time to live used in ageList */
	long		arrivalTimestamp;		/* when pdu arrived/updated */
	Boolean		SRM[MaximumCircuits];
	Boolean		SSN[MaximumCircuits];
	Boolean		foundInSNP;		/* used for processing CSNPs */
	Boolean		onDeletedList;		/* true if marked for deletion */
	u_char		*buf;			/* this baby is task_block_alloc'd */
	int		allocLen;		/* the actual amount alloc'd (different from len) */
	int		len;			/* amount of buffer space this LSP is using (different from allocLen) */
	struct _LSPDesc	*lspDesc;		/* ptr to LSPDesc, if I build this lsp */
	struct _LSEntry	*hashNext;		/* next in hash table */
	struct _LSEntry	*sortNext;		/* next in sorted list */
} LSEntry;

#define locallyGenerated(ent) (ent->lspDesc != NULL)

/*
 * This guy holds a list of LS entries containing only prefixes
 * in the case that no other entries changed (i.e., no interior
 * nodes in the SPF graph have changed, so I just need to adjust
 * routes for the prefixes contained in this list).
 */
struct _lseChangeList {
	struct _lseChangeList *next;
	struct _LSEntry *lse;
};

/*
 *	Various flags to the SRM/SSN routines
 */
#define	AllCircuits		 0x01
#define	SingleCircuit	 0x02

#endif 	/* _flood_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
