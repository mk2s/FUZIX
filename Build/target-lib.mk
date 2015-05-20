# On entry, $T is the target name.

ifeq ($($T.objdir),)
$T.objdir := $(OBJ)/$(PLATFORM)/$T
endif

ifeq ($($T.exe),)
$T.exe := $($T.objdir)/$T.$A
endif

$T: $($T.exe)
.PHONY: $T

$(eval $T.cflags += -I$(TOP)/Library/include)

include $(PLATFORM_RULES)

