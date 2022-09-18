/*
 * vmsexe.h:		Thanks for this file to the people at Rice University!
 *
 * This file contains the declarations for all control blocks necessary
 * to build and decode mvs executable images.  The information was obtained
 * from SYSDEF.MDL in the vms microfiche.  This information is current to 
 * vms rel 2.04.
 *
 * Information for decoding VMS object modules can be found in <vmsobj.h>
 *
 * Much of the actual code is available online in /SYS/SYSLIB/LIB.MLB
 * but this in in some ways unusable since it is uppercase dec assembly
 * language with ALL the comments stripped.  The macros can be obtained
 * by use of the vms library /extract command.  The format of the macro 
 * name is $xxxDEF where xxx is the name of the structure.
 * 
 * Kenneth Zadeck (edited by David Kashtan)
 */

/*
 * macros to convert the vms pages to addresses and back.
 *
 * when making conversions it is importaint to not that disk page numbers
 * begin at block 1 NOT block 0;
 */

#define VMS_BLOCK_SIZE          512
#define VMS_LOG_BLOCK           9  /* 2 ** 9 = VMS_BLOCK_SIZE               */
#define VMS_NUM_PAGES(size)     (((size) + VMS_BLOCK_SIZE - 1) >> VMS_LOG_BLOCK)

#define VMS_PAGE(addr)          ((addr) >> VMS_LOG_BLOCK)
#define VMS_ADDR(page)          ((page) << VMS_LOG_BLOCK)

#define VMS_DISK_PAGE(addr)     (VMS_PAGE((addr)) + 1)
#define VMS_DISK_ADDR(page)     (VMS_ADDR((page) - 1))

#define vshort char         /* one byte integers                            */

/* 
 * the following defines allow the decoding of the ihd.imgtype field
 * the loader must produce only IHD_EXECUTABLE type images.
 */

#define IHD_EXECUTABLE     1
#define IHD_LINKABLE       2

/* 
 * the following defines allow the decoding of the matchctl fields in
 * the isd record and the ihd.lnkflags record. 
 */

#define MATCTL_MATALL         0
#define MATCTL_MATEQU         1
#define MATCTL_MATLEQ         2
#define MATCTL_MATNEV         3

/*
 *  ihd - the first record of the image header
 *
 * If any of the records that the offset fields point to are missing the 
 * offset field should be zero.
 *
 * Any space after the all the header records must be initialized to 0xff.
 * This is particularly true of bytes 511 and 512 of the header record
 * that many vms utilities expect all valid headers to have.
 */

/*
 * The rice ld command uses two disk blocks for the disk header.  The first
 * disk block is used for the vms header and the second disk block
 * is used for the unix a.out header.  This unix header is begins in 
 * character location VMS_A_OUT_LOC of the vms file.  This location is
 * at the end of the second disk block of the file.  This location was
 * selected so that the header could be located immediately before the text
 * to simulate the old impure format and the text could start at character
 * location 1024 to simulate the new demand format.
 * Any program that needs to read exe files produced by this linker as if
 * they were unix a.out files needs to do an
 *
 *      lseek(image_file, VMS_A_OUT_LOC, 0);
 *
 * before attempting to read the the vms file image.
 */

/* 
 * The matchctl and ident fields of this structure only have meaning if
 * the imgtype field is set to linkable.  In that case, the ident and
 * match control fields are to be copied into the isd of the executable 
 * image that is to be produced.  This match control is used to keep
 * images from using a sharable image that is out of date.
 */

typedef     struct  {
    short   size;           /* size in bytes of image header record         */
    short   activoff;       /* byte offset to (iha) activation data         */
    short   symdbgoff;      /* byte offset to (ihs) sym tab and debug data  */
    short   imgidoff;       /* byte offset to (ihi) image ident data        */
    short   patchoff;       /* byte offset to (ihp) patch data              */
    short   reserved1;
    char    majorid[2];     /* major id value in character format           */
    char    minorid[2];     /* minor id value in character format           */
    vshort  hdrblkcnt;      /* count of header blocks                       */
    vshort  imgtype;        /* image type                                   */
                            /* 1 - executable                               */
                            /* 2 - linkable                                 */
    short   reserved2;
    long    privreqs[2];    /* requested privledge mask                     */
                            /* hex FF's if you don't care                   */
    short   iochancnt;      /* # of i-o channels requested                  */
                            /* 0 gets the system default                    */
    short   imgiocnt;       /* # of pages of image i-o section requested    */
                            /* 0 gets the system default                    */
    struct  {               /* linker produced image flags                  */
        unsigned    lnkdebug  : 1;  /* full debug requested                 */
        unsigned    lnknotfr  : 1;  /* first transfer address missing       */
                                    /* this is set for linkable images      */
        unsigned    nopobufs  : 1;  /* rms use of p0 for image has been     */
                                    /* disabled. This is requirred to use   */
                                    /* a real BRK and SBRK                  */
        unsigned    picimg    : 1;  /* image is position independant        */
                                    /* no unix compiler produces position   */
                                    /* independant code                     */
        unsigned    poimg     : 1;  /* image is p0 space only               */
        unsigned    reserved1 : 19; /* reserved bits                        */
        unsigned    matchctl  : 3;  /* match control for linkable           */
                                    /* image, this field is 3 bits          */
        unsigned    reserved2 : 5;  /* reserved bits                        */
    }   lnkflags;
    struct  {         
        unsigned    minorid   :24;  /* minor ident                          */
        unsigned    majorid   : 8;  /* major ident                          */
 
    }       ident;          /* ident for global section for linkable image  */
    long    sysver;         /* sys$k_link version or zero if not linked     */
                            /* with exec (always zero for our purposes)     */
}   IHD;

/* 
 * iha - image activation section 
 *
 * The first transfer address is the entry point of the debugger.
 * it is always set to the value of SYS$IMGSTA which should be a forever
 * constant.  If the image cannot be executed, this field should be
 * set to zero and the iha.lnknotfr flag should be set.
 *
 * The second transfer address is the real entry point.  This value 
 * is set by the loader.
 *
 * The third transfer address is always zero.
 */

#define SYS$IMGSTA  0x80000168	/* They wouldn't DARE move this guy!!! */

typedef     struct  {
    long    tfradr1;        /* first transfer address                       */
    long    tfradr2;        /* second transfer address                      */
    long    tfradr3;        /* third transfer address                       */
    long    reserved1;      /* guarantee zero                               */
}   IHA;

/*
 * ihp - image patch section
 *
 * This record is put in for completeness.  It can occur in images 
 * produced by the vms linker. Unix compilers do not produce enough
 * information to handle patching so we do not produce a patch section in
 * the vms LD command.
 */

typedef     struct  {
    long    eco1;           /* dec  eco levels 1 -32                        */
    long    eco2;           /* dec  eco levels 33-64                        */
    long    eco3;           /* dec  eco levels 65-98                        */
    long    eco4;           /* user eco levels 99-132                       */
    long    rw_patsiz;      /* size of free rw patch area                   */
    long    rw_patadr;      /* vir addr of next free rw patch area          */
    long    ro_patsiz;      /* size of free ro patch area                   */
    long    ro_patadr;      /* vir addr of next free ro patch area          */
    long    patdate[2];     /* date of most recent patch                    */
}   IHP;

/*
 * image symbol table record
 *
 * The global symbol table is in vms object module format.  This format
 * has counted length vms records.  The documentation to decode the records
 * is found in the vms linker manual (very shitty documentation).  The 
 * ihs.gstrecs field is the number of counted string records, not the number
 * of 512 byte blocks as are all other count fields.
 *
 * There is no documentation on how to produce debugger records.
 */

typedef     struct  {
    long    dstvbn;         /* debug symbol table virtual block number      */
    long    gstvbn;         /* global symbol table virtual block number     */
    short   dstblks;        /* debug symbol table block count               */
    short   gstrecs;        /* global symbol table record count             */
}   IHS;

/* 
 * ihi - image header identification
 */

#define VMS_LINK_ID  "2A.44"

typedef     struct  { 
    char    imgnam[16];     /* image name string                            */
    char    imgid[16];      /* image ident string                           */
    long    linktime[2];    /* date and time this image was linked          */
    char    linkid[16];     /* linker ident string VMS_LINK_ID              */
}   IHI;

/*
 * isd - image section descriptor
 *
 * the (isd) image segment descriptors begin immediately after the 
 * ihd.size and continue until there is an isd.size field with size = 0x0000.
 * If the size of an isd = 0xffff, the next isd is found on the next page
 * of the image header, care must be made to insure that isds do not cross
 * page boundries and that no isd is written in locations 511 and 512 of the
 * first image header block.
 *
 * There are three possible values for the length field.
 * The shortest of these, ISDSIZE_DZRO, is used for stack and uninited data.
 * This size is so short, that there is no room for the isd.vbn field
 * which is not needed for this type.  The middle size, ISDSIZE_TEXT,
 * is used for inited data and program text that is stored in the image.
 * This size is large enough to hold the vbn so that the text can be dug
 * out of the image file.  The largest size, ISDSIZE_SHR, holds the whole
 * record, the record holds the information to find the sharable images
 * to be pulled into the image.  For this largest size, the isd.vbn
 * field holds the pointer to location in the image where a copy
 * of the sharable image may have been copied.  This copy is only used
 * if the sharable image cannot be found in SYS$SHARE or has not been
 * instaled.  If the image was not copied, the value of isd.vbn is 0.
 */

#define ISDSIZE_DZRO        12
#define ISDSIZE_TEXT        16
#define ISDSIZE_SHR         36

/*
 * The page fault cluster (pfc) bits are used to set page fault clustering
 * sizes for individual Image Sections (ISDs).  Generally they are set to
 * zero (which gives you the system default page fault cluster size)
 * 
 * The global name field is only used in an isd that points to a sharable
 * image.  The name is built from the sharable images ihi.imgnam with a 
 * "_nnn" where nnn is an integer that tells which isd in the sharable image
 * this isd relates to.  The nnn starts at 001.
 */

/*
 * The starting address for the stack and the number of initial stack
 * pages seems to be a standard value inside vms.  These values are
 * are ISDSTACK_BASE and ISDSTACK_SIZE. Both sizes are given in vms pages.
 */
 
#define ISDSTACK_BASE       VMS_PAGE(0x7fffd800)
#define ISDSTACK_SIZE       0x14

/*
 * the following defines allow the decoding of the isd.type field
 */

#define ISD_NORMAL          0
#define ISD_SHARED_FIXED    1
#define ISD_PRIVATE_FIXED   2
#define ISD_SHARE_PIC       3
#define ISD_PRIVATE_PIC     4
#define ISD_USERSTACK     253


typedef     struct  {
    short   size;           /* size in bytes of this isd                    */
    short   pagcnt;         /* number of pages described by this isd        */
    struct      {           /* vpn & pfc fields                             */
        unsigned    vpn       : 23; /* starting virtual page number         */
        unsigned    reserved  : 1;
        unsigned    pfc       : 8;  /* page fault cluster (8 bits)          */
    }   vpnpfc;
    struct      {    
        unsigned    gbl       : 1;  /* global                               */
        unsigned    crf       : 1;  /* copy on reference                    */
        unsigned    dzro      : 1;  /* demand zero                          */
        unsigned    wrt       : 1;  /* writable                             */
        unsigned    matchctl  : 3;  /* ident match control field            */
        unsigned    lastclu   : 1;  /* isd is part of last p0 space cluster */
        unsigned    copyalway : 1;  /* copy always from user image          */
        unsigned    reserved1 : 8;  
        unsigned    vector    : 1;  /* vector contained in image            */ 
        unsigned    protect   : 1;  /* image section is protected           */
        unsigned    reserved2 : 5;  
        unsigned    type      : 8;  /* isd type codes                       */
    }   flags;
    long    vbn;            /* base virtual block number                    */
                            /* block number in file of start of text        */
    struct  {         
        unsigned    minorid   :24;  /* minor ident                          */
        unsigned    majorid   : 8;  /* major ident                          */
 
    }       ident;          /* ident for global section                     */
    char    gblnam[16];     /* global name                                  */
}   ISD;
