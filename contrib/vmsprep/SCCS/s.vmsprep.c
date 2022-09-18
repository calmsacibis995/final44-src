h22954
s 00001/00000/00166
d D 1.5 87/11/06 12:25:54 bostic 5 4
c new version from Tom Quarles
e
s 00002/00001/00164
d D 1.4 87/11/05 14:54:19 bostic 4 3
c fix exit status on usage error and on program success
e
s 00002/00001/00163
d D 1.3 87/08/14 11:41:59 bostic 3 2
c from Tom Quarles; fix problem with initial directory path on 
c the command line having more than one slash in it
e
s 00000/00000/00164
d D 1.2 87/07/30 09:35:40 bostic 2 1
c new version from Tom Quarles (quarles@panic.berkeley.edu)
e
s 00164/00000/00000
d D 1.1 87/07/30 09:25:17 bostic 1 0
c date and time created 87/07/30 09:25:17 by bostic
e
u
U
t
T
I 1

#include <stdio.h>
#include <ctype.h>
#include <strings.h>

main(argc,argv) 
	int argc;
	char *argv[];

{

char cmd[1000];
char *release;
FILE *dirs;
FILE *files;
FILE *mover;
FILE *popen();
FILE *script;
char dirname[1000];
char filename[1000];
char fixedname[1000];
char fixedpath[1000];
char tapename[10];
char *scriptname = "UNPACK.COM";
char *altscript = "/tmp/UNPACK.COMXXXXXX";
char *startname = "AAAAAAAAA";
int i;
int j;
char *k;
int pathlen;
int dot;
int pipeout=0;

	if(argc < 2) usage();
	if(*argv[1] == '-') {
		mover = stdout;
		pipeout=1;
	} else {
		mover = fopen("vmsprep.namelist","w");
	}
	strcpy(tapename,startname);
	if(pipeout) {
		mktemp(altscript);
		script = fopen(altscript,"w");
	} else {
		script = fopen(scriptname,"w");
	}
I 3
	fprintf(script,"$ SET NOON\n");
E 3
	for(j=1;j<argc;j++) {
		if(j==1 && *argv[j]=='-') continue;
		release = argv[j];
		strcpy(dirname,release);
		for(k=index(dirname,'/');k;k=index(k+1,'/')) {
			*k='\0';
			fprintf(script,"$ CREATE/DIR [.%s] \n",dirname);
D 3
			strcpy(dirname,release);
E 3
I 3
			*k='.';
E 3
		}
		sprintf(cmd,
			"find %s \\! \\( -name RCS -o -name \\*,v -o -name SCCS -o -name s.\\* \\) -type d -print\n", release);
		dirs = popen(cmd,"r");
		while(!feof(dirs)) {
			*dirname = NULL;
			fscanf(dirs," %s ",dirname);
			if(*dirname == NULL) continue;
			for(i=0;i<strlen(dirname);i++) {
				if(dirname[i]=='/') {
					dirname[i]='.';
				} else if (dirname[i]=='.') {
					dirname[i]='Z';
					fprintf(stderr,"vmsprep: warning - dot in filename illegal-");
					fprintf(stderr,"dot replaced by 'Z' %s\n",filename);
				} else if (!(isalpha(dirname[i]) || isdigit(dirname[i]))) {
					fprintf(stderr," error:  bad character in directory name %s\n",
							dirname);
				} else if(islower(dirname[i])) {
					dirname[i]=toupper(dirname[i]);
				}
			}
			fprintf(script,"$ CREATE/DIR [.%s] \n",dirname);
		}
		pclose(dirs);

		sprintf(cmd,
			"find %s \\! \\( -name RCS -o -name \\*,v -o -name SCCS -o -name s.\\* \\) -type f -print\n", release);
		files = popen(cmd,"r");
		while(!feof(files)) {
			fscanf(files," %s ",filename);
			if(*filename == NULL) continue;
			k = rindex(filename,'/') ;
			if(k != 0) {
				pathlen = k - filename;
			} else {
				pathlen=0;
				k = filename - 1;
			}
			strncpy(fixedpath,filename,pathlen);
			fixedpath[pathlen]='\0';
			strcpy(fixedname,k+1);
			for(i=0;i<pathlen;i++) {
				if(fixedpath[i]=='/') {
					fixedpath[i]='.';
				} else if (fixedpath[i]=='.') {
					fixedpath[i]='Z';
				} else if (!(isalpha(fixedpath[i]) || isdigit(fixedpath[i]))) {
					fprintf(stderr," error:  bad character in file name %s\n",
							filename);
				} else if(islower(fixedpath[i])) {
					fixedpath[i]=toupper(fixedpath[i]);
				}
			}
I 5
			dot=0;
E 5
			for(i=0;i<strlen(fixedname);i++) {
				if(fixedname[i]=='/') {
					fixedname[i]='.';
				} else if (fixedname[i]=='.') {
					dot++;
					if(dot != 1) fixedname[i]='Z';
				} else if (!(isalpha(fixedname[i]) || isdigit(fixedname[i]))) {
					fprintf(stderr," error:  bad character in file name %s\n",
							filename);
					fixedname[i]='Z';
				} else if(islower(fixedname[i])) {
					fixedname[i]=toupper(fixedname[i]);
				}
			}
			if(dot >1 ) 
				fprintf(stderr,"error:  too many dots in filename %s \n",
					fixedname);
			sprintf(cmd,"%s %s.MOV\n", filename,tapename);
			fprintf(mover,"%s",cmd);
			if(*fixedpath != NULL) {
				fprintf(script,"$ RENAME %s.MOV [.%s]%s%s\n",tapename,fixedpath,
						fixedname,dot==0?".":"");
			} else {
				fprintf(script,"$ RENAME %s.MOV []%s%s\n",tapename,fixedname,
						dot==0?".":"");
			}
			dot=0;
			bumpname(tapename);
		}
	pclose(files);
	}
	fclose(script);
	if(pipeout) fprintf(mover,"%s ",altscript);
	fprintf(mover,"%s\n",scriptname);
	fclose(mover);
I 4
	return(0);
E 4
}

bumpname(name)
	char name[10];

{
int i;
	for(i=8;i>=0;i--) {
		name[i]++;
		if(name[i] > 'Z') {
			name[i] = 'A';
		} else {
			return;
		}
	}
}
usage() {
	fprintf(stderr,"vmsprep:  usage:  vmsprep dirname [dirname...] \n");
D 4
	exit();
E 4
I 4
	exit(1);
E 4
}
E 1
