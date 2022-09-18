#ifndef lint
static char sccsid[] = "@(#)exercise.c	1.3 (Berkeley/CCI) 11/23/87";
#endif

#include	"vdfmt.h"

#define	verbose	1

/*
**
*/

exercise()
{
	int		cyl, trk;
	dskadr		ead, sad;

	print("Starting disk exercise on ");
	printf("controller %d, drive %d, ", cur.controller, cur.drive);
	printf("type %s.\n", lab->d_typename);

	if(read_bad_sector_map() == true) {
		if(bad_map->bs_id != D_INFO->id) {
			print("Module serial numbers do not match!\n");
			print("Use `info' to find the real serial number.\n");
			_longjmp(abort_environ, 1);
		}
	}
	else if(is_formatted() == false) {
		print("Can not exercise unformatted drives!\n");
		_longjmp(abort_environ, 1);
	}
	print("Starting read test.\n");
	cur.state = exec;
	sad.track = sad.sector = 0;
	indent();
	for(sad.cylinder=0; sad.cylinder<lab->d_ncylinders; sad.cylinder++) {
		print("pass %d...\n", sad.cylinder);
		for(cyl=0; cyl<lab->d_ncylinders-NUMSYS; cyl++){
			ead.cylinder = cyl;
			for(trk=0; trk<lab->d_ntracks; trk++) {
				ead.track = trk;
				ead.sector = 0;
				access_dsk((char *)scratch, &sad,
				    VDOP_SEEK, 1, 1);
				verify_track(&ead, 16, verbose);
				if(kill_processes == true)
					goto exit;
			}
		}
	}
	exdent(2);
exit:	sync_bad_sector_map();
	printf("Exercise completed successfully.\n");
}

