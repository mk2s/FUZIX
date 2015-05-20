TARGETS :=
TARGET :=
CLASS :=

find-makefile = \
	$(eval DIR := $(dir $(word $(words $(MAKEFILE_LIST)), $(MAKEFILE_LIST))))

build = \
	$(eval TARGET := $(strip $1)) \
	$(eval CLASS := $(strip $2)) \
	$(eval include $(BUILD)/object.mk) \
	$(eval TARGET :=) \
	$(eval CLASS :=)

# Given a path $1 and a list of filenames $2, prepends the path to any
# relative filename in $2 (but leaves absolute paths alone).

absify = \
	$(filter /%, $2) \
	$(addprefix $1, $(filter-out /%, $2))

