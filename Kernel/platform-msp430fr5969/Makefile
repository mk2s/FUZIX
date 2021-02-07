ASRCS = crt0.S tricks.S
CSRCS = lowlevel-msp430x.c devices.c devices_discard.c devsdspi.c
CSRCS += devsdspi_discard.c devtty.c devtty_discard.c libc.c
CSRCS += main.c main_discard.c


COBJS = $(CSRCS:.c=$(BINEXT))
AOBJS = $(ASRCS:.S=$(BINEXT))
DOBJS =
CDOBJS = $(CDSRCS:.c=$(BINEXT))
OBJS  = $(COBJS) $(AOBJS) $(DOBJS) $(CDOBJS)

CROSS_CCOPTS += -I../include -I. -I../cpu-$(CPU)
CROSS_CCOPTS += -I../dev/

CROSS_CCOPTS += -Wno-int-to-pointer-cast
CROSS_CCOPTS += -Wno-pointer-to-int-cast
CROSS_CCOPTS += -fno-inline
CROSS_CCOPTS += -fno-common
CROSS_CCOPTS += -g

CROSS_ASOPTS += -I..
CROSS_ASOPTS += -g

all: $(OBJS)

$(COBJS): %$(BINEXT): %.c
	$(CROSS_CC) $(CROSS_CCOPTS) -c $<

$(CDOBJS): %$(BINEXT): %.c
	$(CROSS_CC) $(CROSS_CCOPTS) $(CROSS_CC_SEGDISC) -c $<

$(DOBJS): %$(BINEXT): ../dev/%.c
	$(CROSS_CC) $(CROSS_CCOPTS) -c $<

$(AOBJS): %$(BINEXT): %.S kernel.def ../kernel430x.def msp430fr5969.h
	$(CROSS_AS) $(CROSS_ASOPTS) -c $< -o $*.o

main.c: syscallmap.h
	$(CROSS_CC) $(CROSS_CCOPTS) -c main.c

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

image:
	@echo KERNEL $$@

clean:
	rm $(OBJS) syscallmap.h