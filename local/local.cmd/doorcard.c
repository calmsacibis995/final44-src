# include	<stdio.h>

# define	reg	register

# define	MAXSTR	20

char	buf[BUFSIZ],
	*strings[MAXSTR];

main(ac, av)
int	ac;
char	**av; {

	reg char	*sp;
	reg int		i, p;

	sp = buf;

	printf(".nf\n");
	printf(".vs 0\n");
	printf(".sp 2i\n");
	printf(".ft B\n");
	printf(".ps 10\n");
	printf(".mk a\n");
	printf(".ll 3.75i\n");
	printf(".pl 2i\n");
	printf("\\l'3.75i'\\L'1.25i'\n");
	printf(".sp -1.25i\n");
	printf("\\L'1.25i'\\l'3.75i'\n");
	printf(".rt a\n");
	i = 0;
	while (fgets(sp, BUFSIZ, stdin) != NULL) {
		sp[strlen(sp)-1] = '\0';
		strings[i] = (char *) malloc(strlen(sp) + 1);
		strcpy(strings[i], sp);
		i++;
	}
	switch (i) {
	  case 1:
		p = 36;
		printf(".sp .25i\n");
		break;
	  case 2:
		p = 28;
		printf(".sp .125i\n");
		break;
	  case 3:
		p = 24;
		break;
	  case 4:
		p = 20;
		break;
	  case 5:
		p = 16;
		break;
	  case 6:
		p = 14;
		break;
	}
	printf(".ps %d\n", p);
	printf(".vs \\n(.s+2p\n");
	printf(".ce %d\n", i);
	for (p = 0; p < i; p++)
		printf("%s\n", strings[p]);
}
