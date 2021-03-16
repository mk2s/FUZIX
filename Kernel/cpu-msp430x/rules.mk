export CROSS_CC = msp430-elf-gcc
export CROSS_CCOPTS = -ffunction-sections -fdata-sections -funit-at-a-time -mhwmult=f5series -mmcu=msp430fr5969 -Wall -Werror=implicit-function-declaration --short-enums -Os -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast -fno-inline -fno-common -g -c -I. -I include -I cpu-$(CPU) -I platform-$(TARGET)
export CROSS_ASOPTS = -c
export ASOPTS = $(CROSS_ASOPTS)
#TARGETCPP = msp430-elf-cpp -nostdinc -undef -P
#export CROSS_AS = msp430-elf-as
export CROSS_AS = $(CROSS_CC)

#TARGETAR = msp430-elf-ar
export CROSS_LD = msp430-elf-ld
#TARGETOBJCOPY = msp430-elf-objcopy

export ASMEXT = .S
export BINEXT = .o

export BITS=16

targetgcc.cflags += \
	-g \
	-ffunction-sections \
	-fdata-sections \
	-funit-at-a-time \
	-mhwmult=f5series \
	-mmcu=msp430fr5969

target-exe.ldflags += \
	-g

targetgcc.includes += -I$(TOP)/Library/include/msp430x
