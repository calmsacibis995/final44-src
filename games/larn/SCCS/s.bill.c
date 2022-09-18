h16652
s 00115/00117/00015
d D 5.2 91/05/28 18:11:05 sellgren 2 1
c use system calls instead of io.c, and clean up the style
e
s 00132/00000/00000
d D 5.1 89/03/05 18:59:13 bostic 1 0
c date and time created 89/03/05 18:59:13 by bostic
e
u
U
t
T
I 1
D 2
#include "header.h"
/* bill.c		 "Larn is copyrighted 1986 by Noah Morgan. */
static char mail600[32];
/*
 *	function to create the tax bill for the user
E 2
I 2
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
E 2
 */
D 2
static int pid;
static letter1()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 600 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  the LRS (Larn Revenue Service)\n");
  standout("\nSubject:"); lprcat("  undeclared income\n");
  lprcat("\n   We heard you survived the caverns of Larn.  Let me be the");
  lprcat("\nfirst to congratulate you on your success.  It is quite a feat.");
  lprcat("\nIt must also have been very profitable for you.");
  lprcat("\n\n   The Dungeon Master has informed us that you brought");
  lprintf("\n%d gold pieces back with you from your journey.  As the",(long)c[GOLD]);
  lprcat("\ncounty of Larn is in dire need of funds, we have spared no time");
  lprintf("\nin preparing your tax bill.  You owe %d gold pieces as",
	(long)c[GOLD]*TAXRATE);
  lprcat("\nof this notice, and is due within 5 days.  Failure to pay will");
  lprcat("\nmean penalties.  Once again, congratulations, We look forward");
  lprcat("\nto your future successful expeditions.\n");
  lwclose(); return(1);
  }
E 2

D 2
static letter2()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 601 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  His Majesty King Wilfred of Larndom\n");
  standout("\nSubject:"); lprcat("  a noble deed\n");
  lprcat("\n   I have heard of your magnificent feat, and I, King Wilfred,");
  lprcat("\nforthwith declare today to be a national holiday.  Furthermore,");
  lprcat("\nhence three days, Ye be invited to the castle to receive the");
  lprcat("\nhonour of Knight of the realm.  Upon thy name shall it be written. . .");
  lprcat("\nBravery and courage be yours.");
  lprcat("\nMay you live in happiness forevermore . . .\n");
  lwclose(); return(1);
  }
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

D 2
static letter3()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 602 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  Count Endelford\n");
  standout("\nSubject:"); lprcat("  You Bastard!\n");
  lprcat("\n   I heard (from sources) of your journey.  Congratulations!");
  lprcat("\nYou Bastard!  With several attempts I have yet to endure the");
  lprcat(" caves,\nand you, a nobody, makes the journey!  From this time");
  lprcat(" onward, bewarned\nupon our meeting you shall pay the price!\n");
  lwclose(); return(1);
  }
E 2
I 2
#include <sys/file.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "header.h"
E 2

D 2
static letter4()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 603 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  Mainair, Duke of Larnty\n");
  standout("\nSubject:"); lprcat("  High Praise\n");
  lprcat("\n   With a certainty a hero I declare to be amongst us!  A nod of");
  lprcat("\nfavour I send to thee.  Me thinks Count Endelford this day of");
  lprcat("\nright breath'eth fire as of dragon of whom ye are slayer.  I");
  lprcat("\nyearn to behold his anger and jealously.  Should ye choose to");
  lprcat("\nunleash some of thy wealth upon those who be unfortunate, I,");
  lprcat("\nDuke Mainair, Shall equal thy gift also.\n");
  lwclose(); return(1);
  }
E 2
I 2
/* bill.c		 Larn is copyrighted 1986 by Noah Morgan. */
E 2

D 2
static letter5()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 604 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  St. Mary's Children's Home\n");
  standout("\nSubject:"); lprcat("  these poor children\n");
  lprcat("\n   News of your great conquests has spread to all of Larndom.");
  lprcat("\nMight I have a moment of a great man's time.  We here at St.");
  lprcat("\nMary's Children's Home are very poor, and many children are");
  lprcat("\nstarving.  Disease is widespread and very often fatal without");
  lprcat("\ngood food.  Could you possibly find it in your heart to help us");
  lprcat("\nin our plight?  Whatever you could give will help much.");
  lprcat("\n(your gift is tax deductible)\n");
  lwclose(); return(1);
  }
E 2
I 2
char *mail[] = {
	"From: the LRS (Larn Revenue Service)\n",
	"~s undeclared income\n",
	"\n   We have heard you survived the caverns of Larn.  Let me be the",
	"\nfirst to congratulate you on your success.  It was quite a feat.",
	"\nIt was also very profitable for you...",
	"\n\n   The Dungeon Master has informed us that you brought",
	"1",
	"\ncounty of Larn is in dire need of funds, we have spared no time",
	"2",
	"\nof this notice, and is due within 5 days.  Failure to pay will",
	"\nmean penalties.  Once again, congratulations, We look forward",
	"\nto your future successful expeditions.\n",
	NULL,
	"From: His Majesty King Wilfred of Larndom\n",
	"~s a noble deed\n",
	"\n   I have heard of your magnificent feat, and I, King Wilfred,",
	"\nforthwith declare today to be a national holiday.  Furthermore,",
	"\nhence three days, ye be invited to the castle to receive the",
	"\nhonour of Knight of the realm.  Upon thy name shall it be written...",
	"\n\nBravery and courage be yours.",
	"\n\nMay you live in happiness forevermore...\n",
	NULL,
	"From: Count Endelford\n",
	"~s You Bastard!\n",
	"\n   I have heard (from sources) of your journey.  Congratulations!",
	"\nYou Bastard!  With several attempts I have yet to endure the",
	" caves,\nand you, a nobody, makes the journey!  From this time",
	" onward, bewarned\nupon our meeting you shall pay the price!\n",
	NULL,
	"From: Mainair, Duke of Larnty\n",
	"~s High Praise\n",
	"\n   With certainty, a hero I declare to be amongst us!  A nod of",
	"\nfavour I send to thee.  Me thinks Count Endelford this day of",
	"\nright breath'eth fire as of dragon of whom ye are slayer.  I",
	"\nyearn to behold his anger and jealously.  Should ye choose to",
	"\nunleash some of thy wealth upon those who be unfortunate, I,",
	"\nDuke Mainair, shall equal thy gift also.\n",
	NULL,
	"From: St. Mary's Children's Home\n",
	"~s these poor children\n",
	"\n   News of your great conquests has spread to all of Larndom.",
	"\nMight I have a moment of a great adventurers's time?  We here at",
	"\nSt. Mary's Children's Home are very poor, and many children are",
	"\nstarving.  Disease is widespread and very often fatal without",
	"\ngood food.  Could you possibly find it in your heart to help us",
	"\nin our plight?  Whatever you could give will help much.",
	"\n(your gift is tax deductible)\n",
	NULL,
	"From: The National Cancer Society of Larn\n",
	"~s hope\n",
	"\nCongratulations on your successful expedition.  We are sure much",
	"\ncourage and determination were needed on your quest.  There are",
	"\nmany though, that could never hope to undertake such a journey",
	"\ndue to an enfeebling disease -- cancer.  We at the National",
	"\nCancer Society of Larn wish to appeal to your philanthropy in",
	"\norder to save many good people -- possibly even yourself a few",
	"\nyears from now.  Much work needs to be done in researching this",
	"\ndreaded disease, and you can help today.  Could you please see it",
	"\nin your heart to give generously?  Your continued good health",
	"\ncan be your everlasting reward.\n",
	NULL
};
E 2

D 2
static letter6()
  {
  sprintf(mail600,"/tmp/#%dmail600",pid); /* prepare path */
  if (lcreat(mail600) < 0) { write(1,"can't write 605 letter\n",23); return(0);}
  lprcat("\n\n\n\n\n\n\n\n\n\n\n\n");
  standout("From:"); lprcat("  The National Cancer Society of Larn\n");
  standout("\nSubject:"); lprcat("  hope\n");
  lprcat("\nCongratulations on your successful expedition.  We are sure much");
  lprcat("\ncourage and determination were needed on your quest.  There are");
  lprcat("\nmany though, that could never hope to undertake such a journey");
  lprcat("\ndue to an enfeebling disease -- cancer.  We at the National");
  lprcat("\nCancer Society of Larn wish to appeal to your philanthropy in");
  lprcat("\norder to save many good people -- possibly even yourself a few");
  lprcat("\nyears from now.  Much work needs to be done in researching this");
  lprcat("\ndreaded disease, and you can help today.  Could you please see it");
  lprcat("\nin your heart to give generously?  Your continued good health");
  lprcat("\ncan be your everlasting reward.\n");
  lwclose(); return(1);
  }

E 2
/*
 *	function to mail the letters to the player if a winner
 */
D 2
static int (*pfn[])()= { letter1, letter2, letter3, letter4, letter5, letter6 };
E 2
I 2

void
E 2
mailbill()
D 2
	{
E 2
I 2
{
E 2
	register int i;
I 2
	char fname[32];
E 2
	char buf[128];
D 2
	wait(0);  pid=getpid();
	if (fork() == 0)
		{
E 2
I 2
	char **cp;
	int fd;

	wait(0);
	if (fork() == 0) {
E 2
		resetscroll();
D 2
		for (i=0; i<sizeof(pfn)/sizeof(int (*)()); i++)
			if ((*pfn[i])())
				{
				sleep(20);  sprintf(buf,"mail %s < %s",loginname,mail600);
				system(buf);  unlink(mail600);
				}
		exit();
E 2
I 2
		cp = mail;
		sprintf(fname, "/tmp/#%dlarnmail", getpid());
		for (i = 0; i < 6; i++) {
			if ((fd = open(fname, O_WRONLY | O_TRUNC | O_CREAT),
			    0666) == -1)
				exit(0);
			while (*cp != NULL) {
				if (*cp[0] == '1') {
					sprintf(buf, "\n%d gold pieces back with you from your journey.  As the",
					    (long)c[GOLD]);
					write(fd, buf, strlen(buf));
				} else if (*cp[0] == '2') {
					sprintf(buf, "\nin preparing your tax bill.  You owe %d gold pieces as", (long)c[GOLD]*TAXRATE);
					write(fd, buf, strlen(buf));
				} else
					write(fd, *cp, strlen(*cp));
				cp++;
			}
			cp++;

			close(fd);
			sprintf(buf, "mail -I %s < %s > /dev/null",
			    loginname, fname);
			system(buf);
			unlink(fname);
E 2
		}
	}
I 2
	exit(0);
}
E 2
E 1
