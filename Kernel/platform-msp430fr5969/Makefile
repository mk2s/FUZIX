#CSRCS = dev/blkdev.c dev/devsd.c dev/devsd_discard.c dev/mbr.c devio.c
#CSRCS += devsys.c filesys.c inode.c lowlevel-msp430x.c kdata.c
#CSRCS += mm.c process.c simple.c start.c swap.c syscall_exec16.c
#CSRCS += syscall_fs.c syscall_fs2.c syscall_fs3.c syscall_other.c
#CSRCS += syscall_proc.c timer.c tty.c usermem.c devices.c 
#CSRCS += devices_discard.c devsdspi.c devsdspi_discard.c
#CSRCS += devtty.c devtty_discard.c libc.c main.c main_discard.c

#	$(kernelversion.result)

CSRCS = lowlevel-msp430x.c
CROSS_CCOPTS = -I../include -I. -I../cpu-$(CPU)

#ASRCS = crt0.S tricks.S

COBJS = $(CSRCS:.c=$(BINEXT))
#AOBJS = $(ASRCS:.s=$(BINEXT))
OBJS  = $(COBJS) $(AOBJS)
BINEXT = .o

all: $(OBJS)
	@echo objs $(OBJS)
	@echo binext $(BINEXT)

#$(COBJS): %$(BINEXT): %.c
#	pwd
#	$(CROSS_CC) $(CROSS_CCOPTS) -c $<

image:
	@echo KERNEL $$@