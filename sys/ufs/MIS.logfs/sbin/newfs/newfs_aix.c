
/*
 * AIX Specific modules.
 */
#ifdef AIX
#include <sys/devinfo.h>
#include <sys/bsd_param.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/disklabel.h>
#include <sys/file.h>
#include <sys/mount.h>

#include <ufs/ufs/dir.h>
#include <ufs/ffs/fs.h>

#include <ctype.h>
#include <errno.h>
#include <paths.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

#include <odmi.h>
#include <sys/cfgodm.h>

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
aix_checkifmounted(special)
char *	special;
{

#include <sys/mntctl.h>
#include <sys/vmount.h>

		int num_returned;
		int bufsize;
		char *buffer;
		int i;

		bufsize = 8192; /* just a first guess */
		buffer = malloc(bufsize);
		if (buffer == 0) {
				printf("malloc error\n");
				exit(-1);
		}
		num_returned = mntctl(MCTL_QUERY, bufsize, buffer);
		if (num_returned < 0) { 
			fatal("mntctl: %s\n", strerror(errno));
		}
		else if (num_returned == 0) {
			/* need more space */
			int	needed;

			needed = (int)*((int *)buffer);
			buffer = realloc(buffer, needed);
			if (buffer == 0) {
				fatal("realloc: %s\n", strerror(errno));
			}
			num_returned = mntctl(MCTL_QUERY, needed, buffer);
			if (num_returned <= 0) {
				fatal("mntctl: %s\n", strerror(errno));
			}

		}
		
		for (i=0; i<num_returned; i++) {
			/* see if our device is already mounted */
			if (strcmp(special, vmt2dataptr((struct vmount *)buffer,
									VMT_OBJECT)) == 0) {
				fatal("error: %s is mounted on %s\n", special, 
						vmt2dataptr((struct vmount *)buffer, VMT_STUB));
			}
			buffer += ((struct vmount *)buffer)->vmt_length;
		}
}

int
aix_check_odm(special)
char *		special;
{

	char			*devname;
	int 			rc;

	/* strip off the last component of the device pathname */
	if ((devname = strrchr(special, '/')) != NULL) {
		devname++;
	}
	else { devname = special; }
	/* see if ODM has the name as either a physical or logical volume */
	rc = odm_initialize();
	if (rc == -1) {
		fprintf(stderr, "odm_initialize error %d.\n", odmerrno);
	}
	rc = check_physical_disk(devname);
	if (rc != 0) { return(rc); }
	rc = check_logical_volume(devname);
	return(rc);
}

int
check_physical_disk(devname)
char	*devname;
{

	char			crit[MAX_ODMI_CRIT];
	struct CuAt		*cuatp;
	struct listinfo listinfo;

	sprintf(crit, "name=%s and attribute=pvid", devname);
	cuatp = (struct CuAt *)odm_get_list(CuAt_CLASS, crit, &listinfo, 1, 1);
	if (cuatp == -1) {
		fprintf(stderr, "ODM Error %d.\n", odmerrno);
		exit(-1);
	}	
	else if (cuatp == NULL) {
		/* if the name wasn't found, and it starts with "r", try again 
		** without the "r", so that if we are using "rhdisk1" we look up
		** "hdisk1", etc.
		*/
		if (devname[0] == 'r') { 
			devname++;
			sprintf(crit, "name=%s and attribute=pvid", devname);
			cuatp = (struct CuAt *)odm_get_list(CuAt_CLASS, crit, &listinfo, 1, 
						1);
			if (cuatp == -1) {
				fprintf(stderr, "ODM Error %d.\n", odmerrno);
				exit(-1);
			}	
		}
	}
	if (cuatp == NULL) { return(0); }
	else {
		/* The device is in ODM as a physical disk.  See if it is 
		** part of a volume group.
		*/
		sprintf(crit, "attribute=pv and value=%s", cuatp->value);
		cuatp = (struct CuAt *)odm_get_list(CuAt_CLASS, crit, &listinfo, 1, 1);
		if (cuatp == -1) {
			fprintf(stderr, "ODM Error %d.\n", odmerrno);
			exit(-1);
		}
		else if (cuatp == NULL) { return(0); }
		else {
			fprintf(stderr, "Disk %s is used by volume group %s\n", devname, 
								cuatp->name);
			return(1);
		}
	}
}

int
check_logical_volume(devname)
char		*devname;
{
	char			crit[MAX_ODMI_CRIT];
	struct CuAt		*cuatp;
	struct listinfo listinfo;

	sprintf(crit, "name=%s and attribute=lvserial_id", devname);
	cuatp = (struct CuAt *)odm_get_list(CuAt_CLASS, crit, &listinfo, 1, 1);
	if (cuatp == -1) {
		fprintf(stderr, "ODM Error %d.\n", odmerrno);
		exit(-1);
	}	
	else {
		/* The device is a logical volume.  We assume that if there is
		** a "label" or "type" attribute associated with it, it is in
		** use.
		*/
		sprintf(crit, "name=%s", devname);
		cuatp = (struct CuAt *)odm_get_list(CuAt_CLASS, crit, &listinfo, 10,
													1);
		if (cuatp == -1) {
			fprintf(stderr, "ODM Error %d.\n", odmerrno);
			exit(-1);
		}
		else if (cuatp == NULL) { return(0); }
		else {
			int		i;
			for (i=0; i<listinfo.num; i++) {
				if ((strcmp(cuatp[i].attribute, "label") == 0) ||
				   (strcmp(cuatp[i].attribute, "type") == 0)) {
					fprintf(stderr, "Logical Volume %s appears to be in use.\n",
						devname);
					return(1);
				}
			}
			return(0);
		}
	}
}


#endif /* AIX */
