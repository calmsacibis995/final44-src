 /* t6.c: compute tab stops */
# define tx(a) (a>0 && a<128)
# include "t..c"
maktab()
{
# define FN(i,c) font[c][stynum[i]]
# define SZ(i,c) csize[c][stynum[i]]
/* define the tab stops of the table */
int icol, ilin, tsep, k, ik, vforml, il, text;
char *s;
for(icol=0; icol <ncol; icol++)
	{
	doubled[icol] = acase[icol] = 0;
	fprintf(tabout, ".nr %s 0\n", reg(icol,CRIGHT));
   for(text=0; text<2; text++)
	{
	if (text)
		fprintf(tabout, ".%s\n.rm %s\n", reg(icol, CRIGHT), reg(icol, CRIGHT));
	for(ilin=0; ilin<nlin; ilin++)
		{
		if (instead[ilin]|| fullbot[ilin]) continue;
		vforml=ilin;
		for(il=prev(ilin); il>=0 && vspen(table[il][icol].col); il=prev(il))
			vforml=il;
		if (fspan(vforml,icol)) continue;
		if (filler(table[ilin][icol].col)) continue;
		if ((flags[icol][stynum[ilin]] & ZEROW) != 0) continue;
		switch(ctype(vforml,icol))
			{
			case 'a':
				acase[icol]=1;
				s = table[ilin][icol].col;
				if ((int)s>0 && (int)s<128 && text)
					{
					if (doubled[icol]==0)
						fprintf(tabout, ".nr %s 0\n.nr %s 0\n",S1,S2);
					doubled[icol]=1;
					fprintf(tabout, ".if \\n(%c->\\n(%s .nr %s \\n(%c-\n",s,S2,S2,s);
					}
			case 'n':
				if (table[ilin][icol].rcol!=0)
					{
					if (doubled[icol]==0 && text==0)
						fprintf(tabout, ".nr %s 0\n.nr %s 0\n", S1, S2);
					doubled[icol]=1;
					if (real(s=table[ilin][icol].col) && !vspen(s))
						{
						if (tx((int)s) != text) continue;
						fprintf(tabout, ".nr %s ", TMP);
						wide(s, FN(vforml,icol), SZ(vforml,icol)); fprintf(tabout, "\n");
						fprintf(tabout, ".if \\n(%s<\\n(%s .nr %s \\n(%s\n", S1, TMP, S1, TMP);
						}
					if (text==0 && real(s=table[ilin][icol].rcol) && !vspen(s) && !barent(s))
						{
						fprintf(tabout, ".nr %s \\w%c%s%c\n",TMP, F1, s, F1);
						fprintf(tabout, ".if \\n(%s<\\n(%s .nr %s \\n(%s\n",S2,TMP,S2,TMP);
						}
					continue;
					}
			case 'r':
			case 'c':
			case 'l':
				if (real(s=table[ilin][icol].col) && !vspen(s))
					{
					if (tx((int)s) != text) continue;
					fprintf(tabout, ".nr %s ", TMP);
					wide(s, FN(vforml,icol), SZ(vforml,icol)); fprintf(tabout, "\n");
					fprintf(tabout, ".if \\n(%s<\\n(%s .nr %s \\n(%s\n", reg(icol,CRIGHT), TMP, reg(icol,CRIGHT), TMP);
					}
			}
		}
		}
	if (acase[icol])
		{
		fprintf(tabout, ".if \\n(%s>=\\n(%s .nr %s \\n(%su+2n\n",S2,reg(icol,CRIGHT),reg(icol,CRIGHT),S2);
		}
	if (doubled[icol])
		{
		fprintf(tabout, ".nr %s \\n(%s\n", reg(icol,CMID), S1);
		fprintf(tabout, ".nr %s \\n(%s+\\n(%s\n",TMP,reg(icol,CMID),S2);
		fprintf(tabout, ".if \\n(%s>\\n(%s .nr %s \\n(%s\n",TMP,reg(icol,CRIGHT),reg(icol,CRIGHT),TMP);
		fprintf(tabout, ".if \\n(%s<\\n(%s .nr %s +(\\n(%s-\\n(%s)/2\n",TMP,reg(icol,CRIGHT),reg(icol,CMID),reg(icol,CRIGHT),TMP);
		}
	if (cll[icol][0])
		{
		fprintf(tabout, ".nr %s %sn\n", TMP, cll[icol]);
		fprintf(tabout, ".if \\n(%s<\\n(%s .nr %s \\n(%s\n",reg(icol,CRIGHT), TMP, reg(icol,CRIGHT), TMP);
		}
	for(ilin=0; ilin<nlin; ilin++)
	if (k=lspan(ilin, icol))
		{
		s=table[ilin][icol-k].col;
		if (!real(s) || barent(s) || vspen(s) ) continue;
		fprintf(tabout, ".nr %s ", TMP);
		wide(table[ilin][icol-k].col, FN(ilin,icol-k), SZ(ilin,icol-k));
		for(ik=k; ik>=0; ik--)
			{
			fprintf(tabout, "-\\n(%s",reg(icol-ik,CRIGHT));
			if (!expflg && ik>0) fprintf(tabout, "-%dn", sep[icol-ik]);
			}
		fprintf(tabout, "\n");
		fprintf(tabout, ".if \\n(%s>0 .nr %s \\n(%s/%d\n", TMP, TMP, TMP, k);
		fprintf(tabout, ".if \\n(%s<0 .nr %s 0\n", TMP, TMP);
		for(ik=1; ik<=k; ik++)
			{
			if (doubled[icol-k+ik])
				fprintf(tabout, ".nr %s +\\n(%s/2\n", reg(icol-k+ik,CMID), TMP);
			fprintf(tabout, ".nr %s +\\n(%s\n", reg(icol-k+ik,CRIGHT), TMP);
			}
		}
	}
if (textflg) untext();
/* if even requested, make all columns widest width */
# define TMP1 S1
# define TMP2 S2
if (evenflg)
	{
	fprintf(tabout, ".nr %s 0\n", TMP);
	for(icol=0; icol<ncol; icol++)
		{
		if (evenup[icol]==0) continue;
		fprintf(tabout, ".if \\n(%s>\\n(%s .nr %s \\n(%s\n",
			reg(icol,CRIGHT), TMP, TMP, reg(icol,CRIGHT));
		}
	for(icol=0; icol<ncol; icol++)
		{
		if (evenup[icol]==0)
			/* if column not evened just retain old interval */
			continue;
		if (doubled[icol])
			fprintf(tabout, ".nr %s (100*\\n(%s/\\n(%s)*\\n(%s/100\n",
				reg(icol,CMID), reg(icol,CMID), reg(icol,CRIGHT), TMP);
				/* that nonsense with the 100's and parens tries
				   to avoid overflow while proportionally shifting
				   the middle of the number */
		fprintf(tabout, ".nr %s \\n(%s\n", reg(icol,CRIGHT), TMP);
		}
	}
/* now adjust for total table width */
for(tsep=icol=0; icol<ncol; icol++)
	tsep+= sep[icol];
if (expflg)
	{
	fprintf(tabout, ".nr %s 0", TMP);
	for(icol=0; icol<ncol; icol++)
		fprintf(tabout, "+\\n(%s", reg(icol,CRIGHT));
	fprintf(tabout, "\n");
	fprintf(tabout, ".nr %s \\n(.l-\\n(%s\n", TMP, TMP);
	if (boxflg || dboxflg || allflg)
		/* tsep += 1; */ ;
	else
		tsep -= sep[ncol-1];
	fprintf(tabout, ".nr %s \\n(%s/%d\n", TMP, TMP,  tsep);
	fprintf(tabout, ".if \\n(%s<0 .nr %s 0\n", TMP, TMP);
	}
else
	fprintf(tabout, ".nr %s 1n\n", TMP);
fprintf(tabout, ".nr %s 0\n",reg(-1, CRIGHT));
tsep= (boxflg || allflg || dboxflg || left1flg) ? 2 : 0;
if (sep[-1] >= 0) tsep = sep[-1];
for(icol=0; icol<ncol; icol++)
	{
	fprintf(tabout, ".nr %s \\n(%s+((%d*\\n(%s)/2)\n",reg(icol,CLEFT), reg(icol-1,CRIGHT), tsep, TMP);
	fprintf(tabout, ".nr %s +\\n(%s\n",reg(icol,CRIGHT), reg(icol,CLEFT));
	if (doubled[icol])
		{
		/* the next line is last-ditch effort to avoid zero field width */
		/*fprintf(tabout, ".if \\n(%s=0 .nr %s 1\n",reg(icol,CMID), reg(icol,CMID));*/
		fprintf(tabout, ".nr %s +\\n(%s\n", reg(icol,CMID), reg(icol,CLEFT));
	/*  fprintf(tabout, ".if n .if \\n(%s%%24>0 .nr %s +12u\n",reg(icol,CMID), reg(icol,CMID)); */
		}
	tsep=sep[icol]*2;
	}
if (rightl)
	fprintf(tabout, ".nr %s (\\n(%s+\\n(%s)/2\n",reg(ncol-1, CRIGHT), reg(ncol-1,CLEFT), reg(ncol-2,CRIGHT));
fprintf(tabout, ".nr TW \\n(%s\n", reg(ncol-1, CRIGHT));
tsep = sep[ncol-1];
if (boxflg || allflg || dboxflg)
	fprintf(tabout, ".nr TW +((%d*\\n(%s)/2)\n", tsep, TMP);
fprintf(tabout,
 ".if t .if \\n(TW>\\n(.lu .tm Table at line %d file %s is too wide - \\n(TW units\n", iline-1, ifile);
return;
}
wide(s, fn, size)
	char *s, *size, *fn;
{
if (point(s))
	{
	fprintf(tabout, "\\w%c", F1);
	if (*fn>0) putfont(fn);
	if (*size) putsize(size);
	fprintf(tabout, "%s", s);
	if (*fn>0) putfont("P");
	if (*size) putsize("0");
	fprintf(tabout, "%c",F1);
	}
else
	fprintf(tabout, "\\n(%c-", s);
}
filler(s)
	char *s;
{
return (point(s) && s[0]=='\\' && s[1] == 'R');
}
