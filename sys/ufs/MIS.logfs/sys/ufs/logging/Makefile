DEBUG=-g -c -DKERNEL
INCLUDES=-I. -I../recovery -I/usr2/src/sys/compile/MISLITE -I/usr2/src/sys -I/usr2/src/sbin/fsck 

ALL_USER=lffs_read_utils.o lffs_read.o lffs_print.o lffs_recover.o lffs_strings.o
ALL_KERNEL=lffs_log.o

all: $(ALL_USER) $(ALL_KERNEL)

lffs_read_utils.c: lffs.src lffs_read.sh
	./lffs_read.sh lffs.src

lffs_log.c: lffs.src lffs_log.sh
	./lffs_log.sh lffs.src

lffs_auto.h: lffs.src lffs_h.sh
	./lffs_h.sh lffs.src

lffs_log.o: lffs_auto.h lffs.h
	$(CC) $(DEBUG) $(INCLUDES) lffs_log.c

lffs_read.o: lffs_auto.h lffs.h
	$(CC) $(DEBUG) $(INCLUDES) lffs_read.c

lffs_read_utils.o: lffs_auto.h lffs.h
	$(CC) $(DEBUG) $(INCLUDES) lffs_read_utils.c

lffs_print.c: lffs.src lffs_print.sh
	./lffs_print.sh lffs.src

lffs_print.o: lffs_auto.h lffs.h
	$(CC) $(DEBUG) $(INCLUDES) lffs_print.c

lffs_recover.c: lffs.src lffs_recover.sh
	./lffs_recover.sh lffs.src

lffs_recover.o: lffs_auto.h lffs.h
	$(CC) $(DEBUG) $(INCLUDES) lffs_recover.c

lffs_strings.o: lffs.h lffs_strings.c
	$(CC) $(DEBUG) $(INCLUDES) lffs_strings.c


liblffs.a: $(ALL_USER)
	ar -r liblffs.a $(ALL_USER)
	ranlib liblffs.a
