ASRCS = crt0.S tricks.S
CSRCS = lowlevel-msp430x.c devices.c devices_discard.c devsdspi.c
CSRCS += devsdspi_discard.c devtty.c devtty_discard.c libc.c
CSRCS += main.c main_discard.c

DSRCS = ../dev/blkdev.c ../dev/mbr.c ../dev/devsd.c ../dev/devsd_discard.c

COBJS = $(CSRCS:.c=$(BINEXT))
AOBJS = $(ASRCS:.S=$(BINEXT))
DOBJS = $(DSRCS:.c=$(BINEXT))
CDOBJS = $(CDSRCS:.c=$(BINEXT))
OBJS  = $(COBJS) $(AOBJS) $(DOBJS) $(CDOBJS)

CROSS_CCOPTS += -I../include -I../cpu-$(CPU)
CROSS_CCOPTS += -I../dev/


CROSS_ASOPTS += -I..
CROSS_ASOPTS += -g -c

all: $(OBJS)

$(COBJS): %$(BINEXT): %.c
	$(CROSS_CC) $(CROSS_CCOPTS) $<

$(CDOBJS): %$(BINEXT): %.c
	$(CROSS_CC) $(CROSS_CCOPTS) $(CROSS_CC_SEGDISC) -c $<

$(DOBJS): %$(BINEXT): ../dev/%.c
	$(CROSS_CC) $(CROSS_CCOPTS) $<

$(AOBJS): %$(BINEXT): %.S kernel.def ../kernel430x.def msp430fr5969.h
	$(CROSS_AS) $(CROSS_ASOPTS) $< -o $*.o

main.o: main.c syscallmap.h
#	$(CROSS_CC) $(CROSS_CCOPTS) -c main.c

# Do not change the order below without updating main.c.
syscallmap.srcs = \
	../syscall_exec16.c \
	../syscall_fs.c \
	../syscall_fs2.c \
	../syscall_fs3.c \
	../syscall_other.c \
	../syscall_proc.c

syscallmap.h: ../tools/map_syscall
	../tools/map_syscall $(syscallmap.srcs) > syscallmap.h

# figure out $$(dir $$($1.libgcc))
image:
	$(CROSS_LD) -s --relax -g -o ../fuzix.bin -Map=../fuzix.map --script=msp430fr5969.ld.out \
	--start-group \
	crt0.o main_discard.o tricks.o main.o lowlevel-msp430x.o devices.o devtty.o \
	libc.o blkdev.o devsd.o devsdspi.o devsdspi_discard.o devices_discard.o devsd_discard.o devtty_discard.o mbr.o \
	../kdata.o ../devio.o ../process.o ../devsys.o ../inode.o \
	../usermem.o ../mm.o \
	../syscall_exec16.o ../syscall_fs.o ../syscall_fs2.o ../syscall_fs3.o ../syscall_other.o ../syscall_proc.o ../filesys.o ../start.o ../simple.o ../swap.o ../tty.o ../timer.o \
	../version.o \
    -L/home/mk2s/ti/gcc3/bin/../lib/gcc/msp430-elf/4.9.1 -lgcc \
	--end-group

clean:
	rm $(OBJS) syscallmap.h
