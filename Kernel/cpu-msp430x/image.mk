fuzix.bin: tools/map_syscall target $(OBJS)
	+make -C platform-$(TARGET) image
