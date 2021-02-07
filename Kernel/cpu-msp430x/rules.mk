export CROSS_CC = msp430-elf-gcc
export CROSS_CCOPTS = 
#TARGETCPP = msp430-elf-cpp -nostdinc -undef -P
#export CROSS_AS = msp430-elf-as
export CROSS_AS = $(CROSS_CC)

#TARGETAR = msp430-elf-ar
export CROSS_LD = msp430-elf-ld
#TARGETOBJCOPY = msp430-elf-objcopy

export ASMEXT = .S
export BINEXT = .o

targetgcc.cflags += \
	-g \
	-ffunction-sections \
	-fdata-sections \
	-funit-at-a-time \
	-mhwmult=auto \
	-mmcu=msp430fr5969

target-exe.ldflags += \
	-g

targetgcc.includes += -I$(TOP)/Library/include/msp430x
