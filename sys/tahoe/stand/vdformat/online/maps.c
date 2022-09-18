#ifndef lint
static char sccsid[] = "%W% (Berkeley/CCI) %G%";
#endif


#include	"vdfmt.h"


/*
**
*/

boolean align_buf(buf, sync)
unsigned long	*buf;
unsigned long	sync;
{
	register int	i, shift;

	/* find shift amount */
	for(shift=0; shift < 32; shift++) {
		if((*buf >> shift ) == sync) {
			for(i=(512/sizeof(long))-1; i >= 0; i--) {
				*(buf+i+1) |= *(buf+i) << (32 - shift);
				*(buf+i) = *(buf+i) >> shift;
			}
			return true;
		}
	}
	return false;
}


/*
**	Looks for two maps in a row that are the same.
*/

boolean
read_map(flags)
short	flags;
{
	register int	trk, i;
	dskadr		dskaddr;

	dskaddr.cylinder = (lab->d_ncylinders - 1) | flags;
	for(i=0; i < 100; i++)
		scratch[i] = -1;
	for(trk=0; trk < lab->d_ntracks; trk++) {
		dskaddr.track = trk;
		dskaddr.sector = 0;
		if(access_dsk((char *)save,&dskaddr, VDOP_RD,
		    lab->d_nsectors,1)& VDERR_HARD)
			continue;
		if(bcmp((char *)scratch, (char *)save, bytes_trk) == true) {
			bcopy((char *)save, (char *)bad_map, bytes_trk);
			if(bad_map->bs_count <= MAX_FLAWS) {
				for(i=0; i < bad_map->bs_count; i++) {
					if(bad_map->list[i].bs_cyl >=
					    lab->d_ncylinders)
						break;
					if(bad_map->list[i].bs_trk >=
					    lab->d_ntracks)
						break;
					if(bad_map->list[i].bs_offset >=
					    lab->d_traksize)
						break;
				}
				if(i == bad_map->bs_count) {
					load_free_table();
					return true;
				}
			}
			bzero(bad_map, bytes_trk);
			bad_map->bs_id = 0;
			bad_map->bs_max = MAX_FLAWS;
		}
		bcopy((char *)save, (char *)scratch, bytes_trk);
	}
	return false;
}


/*
**
*/

boolean read_bad_sector_map()
{
	dskadr		dskaddr;

	dskaddr.cylinder = lab->d_ncylinders - 1;
	dskaddr.track = 0;
	dskaddr.sector = 0;
	/* start with nothing in map */
	bzero(bad_map, bytes_trk);
	bad_map->bs_id = 0;
	bad_map->bs_max = MAX_FLAWS;
	if (C_INFO->type == VDTYPE_SMDE) {
		access_dsk((char *)save, &dskaddr, VDOP_RDRAW, 1, 1);
		if (align_buf((unsigned long *)save, CDCSYNC) == true) {
			read_flaw_map();
			return (false);
		} else if (read_map(NRM) == true) {
			return (true);
		} else {
			get_smde_relocations();
			return false;
		}
	} else {
		if (read_map(WPT) == true)
			return (true);
		else {
			get_relocations_the_hard_way();
			return (false);
		}
	}
}


/*
**
*/

get_relocations_the_hard_way()
{
	register int	cyl, trk;
	register int	status;
	dskadr		dskaddr;

	dskaddr.sector = 0;
	/* scan each sector to see if it is relocated and take note if it is */
	for(cyl=0; cyl < lab->d_ncylinders - NUMSYS; cyl++) {
		dskaddr.cylinder = cyl;
		for(trk=0; trk < lab->d_ntracks; trk++) {
			dskaddr.track = trk;
			status=access_dsk((char *)scratch, &dskaddr,
			    VDOP_RD, lab->d_nsectors, 1);
			if(status & DCBS_ATA)
				get_track_relocations(dskaddr);
		}
	}
	load_free_table();
}


/*
**
*/

get_track_relocations(dskaddr)
dskadr	dskaddr;
{
	register int	status;
	bs_entry	temp;
	fmt_err		error;
	
	for(dskaddr.sector=0; dskaddr.sector < lab->d_nsectors; dskaddr.sector++) {
		status = access_dsk((char *)scratch, &dskaddr, VDOP_RD, 1, 1);
		if(status & DCBS_ATA) {
			error.err_adr = dskaddr;
			error.err_stat = DATA_ERROR;
			temp = (*C_INFO->code_pos)(error);
			temp.bs_how = operator;
			add_flaw(&temp);
		}
	}
}


/*
**
*/

remove_user_relocations(entry)
bs_entry	entry;
{
	register int	i, j;
	fmt_err		temp;
	fmt_err		error;
	bs_entry	*ptr;	

	error = (*C_INFO->decode_pos)(entry);
	if(is_in_map(&error.err_adr) == true) {
		ptr = bad_map->list;
		for(i=0; i < bad_map->bs_count; i++) {
			temp = (*C_INFO->decode_pos)(*ptr);
			if((ptr->bs_how == operator) &&
			    (temp.err_adr.cylinder == error.err_adr.cylinder) &&
			    (temp.err_adr.track == error.err_adr.track) &&
			    (temp.err_adr.sector == error.err_adr.sector)) {
				if(temp.err_stat & HEADER_ERROR)
					remove_track(temp, ptr);
				else
					remove_sector(temp, ptr);
				for(j=i+1; j < bad_map->bs_count; j++)
					bad_map->list[j-1] = bad_map->list[j];
				bad_map->bs_count--;
				return;
			}
			ptr++;
		}
	}
	else {
		indent();
		print("Sector %d is not in bad sector map!\n",
		    to_sector(error.err_adr));
		exdent(1);
	}
}


/*
**
*/

remove_sector(error, entry)
fmt_err		error;
bs_entry	*entry;
{
	format_sectors(&error.err_adr, &error.err_adr, NRM, 1);
	format_sectors(&entry->bs_alt, &entry->bs_alt, NRM, 1);
}


/*
**
*/

remove_track(error, entry)
fmt_err		error;
bs_entry	*entry;
{
	format_sectors(&error.err_adr,&error.err_adr,NRM,(long)lab->d_nsectors);
	format_sectors(&entry->bs_alt,&entry->bs_alt,NRM,(long)lab->d_nsectors);
}


/*
**
*/

write_bad_sector_map()
{
	register int	trk, sec;
	dskadr		dskaddr;

	dskaddr.cylinder = (lab->d_ncylinders - NUMMAP);
	for(trk=0; trk < lab->d_ntracks; trk++) {
		for(sec = 0; sec < lab->d_nsectors; sec++) {
			bcopy((char *)bs_map_space + (sec * lab->d_secsize),
			    (char *)scratch, lab->d_secsize);
			dskaddr.track = trk;
			dskaddr.sector = sec;
			format_sectors(&dskaddr, &dskaddr, WPT, 1);
		}
	}
}


/*
**
*/

zero_bad_sector_map()
{
	bs_map		*bm = bad_map;
	register int	i;
	dskadr		zero;

	zero.cylinder = 0;
	zero.track = 0;
	zero.sector = 0;
	for(i=0; i < bm->bs_count; i++)
		bm->list[i].bs_alt = zero;
	load_free_table();
}


/*
**
*/

read_flaw_map()
{
	register int	cyl, trk;
	dskadr		dskaddr;
	flaw		buffer;

	dskaddr.sector = 0;
	for  (cyl=0; cyl < lab->d_ncylinders; cyl++) {
		dskaddr.cylinder = cyl;
		for  (trk=0; trk < lab->d_ntracks; trk++) {
			dskaddr.track = trk;
			access_dsk(&buffer, &dskaddr, VDOP_RDRAW, 1, 1);
			if(align_buf(&buffer, CDCSYNC) == true) {
				add_flaw_entries(&buffer);
				continue;
			}
		}	
	}
	load_free_table();
}


/*
**
*/

get_smde_relocations()
{
	register int	cyl, trk, sec;
	smde_hdr	buffer;
	dskadr		dskaddr;
	fmt_err		bad;
	bs_entry	temp;
	boolean		bad_track;

	/* Read any old drive relocations */
	for(cyl=0; cyl < NUMREL; cyl++) {
		dskaddr.cylinder = lab->d_ncylinders - NUMSYS + cyl;
		for(trk=0; trk < lab->d_ntracks; trk++) {
			dskaddr.track = trk;
			bad_track = true;
			for(sec=0; sec < lab->d_nsectors; sec++) {
				dskaddr.sector = sec;
				access_dsk(&buffer, &dskaddr, VDOP_RDRAW, 1, 1);
				if(align_buf(&buffer, SMDE1SYNC) == false) {
					bad_track = false;
					break;
				}
			}
			if(bad_track == true) {
				dskaddr.sector = 0;
				bad.err_adr.cylinder = buffer.alt_cyl;
				bad.err_adr.track = buffer.alt_trk;
				bad.err_adr.sector = 0;
				bad.err_stat = HEADER_ERROR;
				temp = (*C_INFO->code_pos)(bad);
				temp.bs_alt = dskaddr;
				temp.bs_how = scanning;
				add_flaw(&temp);
				continue;
			}
			for(sec=0; sec < lab->d_nsectors; sec++) {
				dskaddr.sector = sec;
				access_dsk(&buffer, &dskaddr, VDOP_RDRAW, 1, 1);
				if(align_buf(&buffer, SMDE1SYNC) == true) {
					bad.err_adr.cylinder = buffer.alt_cyl;
					bad.err_adr.track = buffer.alt_trk;
					bad.err_adr.sector = buffer.alt_sec;
					bad.err_stat = DATA_ERROR;
					temp = (*C_INFO->code_pos)(bad);
					temp.bs_alt = dskaddr;
					temp.bs_how = scanning;
					add_flaw(&temp);
				}
			}
		}
	}
	load_free_table();
}


/*
**
*/

add_flaw_entries(buffer)
flaw	*buffer;
{
	register int	i;
	bs_entry	temp;

	temp.bs_cyl = buffer->flaw_cyl & 0x7fff; /* clear off bad track bit */
	temp.bs_trk = buffer->flaw_trk;
	for(i=0; i < 4; i++) {
		if(buffer->flaw_pos[i].flaw_length != 0) {
			temp.bs_offset = buffer->flaw_pos[i].flaw_offset;
			temp.bs_length = buffer->flaw_pos[i].flaw_length;
			temp.bs_alt.cylinder = 0;
			temp.bs_alt.track = 0;
			temp.bs_alt.sector = 0;
			temp.bs_how = flaw_map;
			add_flaw(&temp);
		}
	}
}


cmp_entry(a, b)
bs_entry	*a;
bs_entry	*b;
{
	if(a->bs_cyl == b->bs_cyl) {
		if(a->bs_trk == b->bs_trk) {
			if(a->bs_offset == b->bs_offset)
				return 0;
			else if(a->bs_offset < b->bs_offset)
				return -1;
		 }
		else if(a->bs_trk < b->bs_trk)
			return -1;
	}
	else if(a->bs_cyl < b->bs_cyl)
		return -1;
	return 1;
}


add_flaw(entry)
bs_entry	*entry;
{
	extern	int	cmp_entry();
	bs_map		*bm = bad_map;
	register int	i;

	if(bm->bs_count > MAX_FLAWS)
		return;
	if (entry->bs_cyl >= lab->d_ncylinders ||
	    entry->bs_trk >= lab->d_ntracks ||
	    entry->bs_offset >= lab->d_traksize)
		return;
	for(i=0; i < bm->bs_count; i++) {
		if(((bm->list[i].bs_cyl == entry->bs_cyl)) &&
		    (bm->list[i].bs_trk == entry->bs_trk) &&
		    (bm->list[i].bs_offset == entry->bs_offset)) {
			if((int)bm->list[i].bs_how > (int)entry->bs_how)
				bm->list[i].bs_how = entry->bs_how;
			return;
		}
	}
	bm->list[i] = *entry;
	bm->list[i].bs_alt.cylinder = 0;
	bm->list[i].bs_alt.track = 0;
	bm->list[i].bs_alt.sector = 0;
	bm->bs_count++;
	qsort((char *)&(bm->list[0]), (unsigned)bm->bs_count,
	    sizeof(bs_entry), cmp_entry);
}


/*
**	Is_in_map checks to see if a block is known to be bad already.
*/

boolean is_in_map(dskaddr)
dskadr	*dskaddr;
{
	register int	i;
	fmt_err		temp;

	for(i=0; i < bad_map->bs_count; i++) {
		temp = (*C_INFO->decode_pos)(bad_map->list[i]);
		if((temp.err_adr.cylinder == dskaddr->cylinder) &&
		    (temp.err_adr.track == dskaddr->track) &&
		    (temp.err_adr.sector == dskaddr->sector)) {
			return true;
		}
	}
	return false;
}


/*
**
*/

print_bad_sector_list()
{
	register int	i;
	fmt_err		errloc;

	if(bad_map->bs_count == 0) {
		print("There are no bad sectors in bad sector map.\n");
		return;
	}
	print("The following sector%s known to be bad:\n",
	    (bad_map->bs_count == 1) ? " is" : "s are");
	indent();
	for(i=0; i < bad_map->bs_count; i++) {
		print("cyl %d, head %d, pos %d, len %d ",
			bad_map->list[i].bs_cyl,
			bad_map->list[i].bs_trk,
			bad_map->list[i].bs_offset,
			bad_map->list[i].bs_length);
		errloc = (*C_INFO->decode_pos)(bad_map->list[i]);
		if(errloc.err_stat & HEADER_ERROR) {
			printf("(Track #%d)", to_track(errloc.err_adr));
		}
		else {
			printf("(Sector #%d)", to_sector(errloc.err_adr));
		}
		if((bad_map->list[i].bs_alt.cylinder != 0) ||
		    (bad_map->list[i].bs_alt.track != 0) ||
		    (bad_map->list[i].bs_alt.sector != 0)) {
			indent();
			printf(" -> ");
			if(errloc.err_stat & HEADER_ERROR) {
				printf("Track %d",
		    		    to_track(bad_map->list[i].bs_alt));
			}
			else {
				printf("Sector %d",
		    		    to_sector(bad_map->list[i].bs_alt));
			}
			exdent(1);
		}
		printf(".\n");
	}
	exdent(1);
}


/*
**	Vdload_free_table checks each block in the bad block relocation area
** to see if it is used. If it is, the free relocation block table is updated.
*/

load_free_table()
{
	register int	i, j;
	fmt_err		temp;

	/* Clear free table before starting */
	for(i = 0; i < (lab->d_ntracks * NUMREL); i++) {
		for(j=0; j < lab->d_nsectors; j++)
			free_tbl[i][j].free_status = NOTALLOCATED;
	}
	for(i=0; i < bad_map->bs_count; i++)
		if((bad_map->list[i].bs_alt.cylinder != 0) ||
		    (bad_map->list[i].bs_alt.track != 0) ||
		    (bad_map->list[i].bs_alt.sector != 0)) {
			temp = (*C_INFO->decode_pos)(bad_map->list[i]);
			allocate(&(bad_map->list[i].bs_alt), temp.err_stat);
		}
}


/*
**	allocate marks a replacement sector as used.
*/

allocate(dskaddr, status)
dskadr	*dskaddr;
long	status;
{
	register int	trk, sec;

	trk = dskaddr->cylinder - (lab->d_ncylinders - NUMSYS);
	if((trk < 0) || (trk >= NUMREL))
		return;
	trk *= lab->d_ntracks;
	trk += dskaddr->track;
	if(status & HEADER_ERROR)
		for(sec=0; sec < lab->d_nsectors; sec++)
			free_tbl[trk][sec].free_status = ALLOCATED;
	else
		free_tbl[trk][dskaddr->sector].free_status = ALLOCATED;
}


/*
**
*/

boolean mapping_collision(entry)
bs_entry	*entry;
{
	register int	trk, sec;
	fmt_err		temp;

	trk = entry->bs_cyl - (lab->d_ncylinders - NUMSYS);
	if((trk < 0) || (trk >= NUMREL))
		return false;
	trk *= lab->d_ntracks;
	trk += entry->bs_trk;
	temp = (*C_INFO->decode_pos)(*entry);
	/* if this relocation should take up the whole track */
	if(temp.err_stat & HEADER_ERROR) {
		for(sec=0; sec < lab->d_nsectors; sec++)
			if(free_tbl[trk][sec].free_status == ALLOCATED)
				return true;
	}
	/* else just check the current sector */
	else {
		if(free_tbl[trk][temp.err_adr.sector].free_status == ALLOCATED)
			return true;
	}
	return false;
}


/*
**
*/

report_collision()
{
	indent();
	print("Sector resides in relocation area");
	printf("but it has a sector mapped to it already.\n");
	print("Please reformat disk with 0 patterns to eliminate problem.\n");
	exdent(1);
}


/*
**
*/

add_user_relocations(entry)
bs_entry	*entry;
{
	fmt_err		error;
	
	error = (*C_INFO->decode_pos)(*entry);
	if(is_in_map(&error.err_adr) == false) {
		if(mapping_collision(entry) == true)
			report_collision();
		entry->bs_how = operator;
		add_flaw(entry);
	}
	else {
		indent();
		print("Sector %d is already mapped out!\n",
		    to_sector(error.err_adr));
		exdent(1);
	}
}


/*
** 	New_location allocates a replacement block given a bad block address.
**  The algorithm is fairly simple; it simply searches for the first
**  free sector that has the same sector number of the bad sector.  If no sector
**  is found then the drive should be considered bad because of a microcode bug
**  in the controller that forces us to use the same sector number as the bad
**  sector for relocation purposes.  Using different tracks and cylinders is ok
**  of course.
*/

dskadr *new_location(entry)
bs_entry	*entry;
{
	register int	i, sec;
	static fmt_err	temp;
	static dskadr	newaddr;

	newaddr.cylinder = 0;
	newaddr.track = 0;
	newaddr.sector = 0;
	temp = (*C_INFO->decode_pos)(*entry);
	/* If it is ouside of the user's data area */
	if(entry->bs_cyl >= lab->d_ncylinders-NUMSYS) {
		/* if it is in the relocation area */
		if(entry->bs_cyl < (lab->d_ncylinders - NUMMAP - NUMMNT)) {
			/* mark space as allocated */
			allocate(&temp.err_adr, temp.err_stat);
			return &temp.err_adr;
		}
		/* if it is in the map area forget about it */
		if(entry->bs_cyl != (lab->d_ncylinders - NUMMAP - NUMMNT))
			return &temp.err_adr;
		/* otherwise treat maintainence cylinder normally */
	}
	if(temp.err_stat & (HEADER_ERROR)) {
		for(i = 0; i < (lab->d_ntracks * NUMREL); i++) {
			for(sec=0; sec < lab->d_nsectors; sec++) {
				if(free_tbl[i][sec].free_status == ALLOCATED)
					break;
			}
			if(sec == lab->d_nsectors) {
				for(sec = 0; sec < lab->d_nsectors; sec++)
					free_tbl[i][sec].free_status=ALLOCATED;
				newaddr.cylinder = i / lab->d_ntracks +
				    (lab->d_ncylinders - NUMSYS);
				newaddr.track = i % lab->d_ntracks;
				break;
			}
		}
	}
	else if(C_INFO->type == VDTYPE_VDDC) {
		for(i = 0; i < (lab->d_ntracks * NUMREL); i++) {
			if(free_tbl[i][temp.err_adr.sector].free_status !=
			    ALLOCATED) {
				free_tbl[i][temp.err_adr.sector].free_status =
				    ALLOCATED;
				newaddr.cylinder = i / lab->d_ntracks +
				    (lab->d_ncylinders - NUMSYS);
				newaddr.track = i % lab->d_ntracks;
				newaddr.sector = temp.err_adr.sector;
				break;
			}	
		}
	}
	else {
		for(i = 0; i < (lab->d_ntracks * NUMREL); i++) {
			for(sec=0; sec < lab->d_nsectors; sec++)
				if(free_tbl[i][sec].free_status != ALLOCATED)
					break;
			if(sec < lab->d_nsectors) {
				free_tbl[i][sec].free_status = ALLOCATED;
				newaddr.cylinder = i / lab->d_ntracks +
				    (lab->d_ncylinders - NUMSYS);
				newaddr.track = i % lab->d_ntracks;
				newaddr.sector = sec;
				break;
			}
		}
	}
	return &newaddr;
}
