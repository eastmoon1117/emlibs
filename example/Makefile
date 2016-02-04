include compile.mk

ifeq ($(HIDE),@)
	QUIET := -s
endif
#SUB_DIRS=$(sort $(dir $(shell find . -name *.c)))
SUB_DIRS = list     \
		   hashmap  \


.PHONY: all $(SUB_DIRS)
all: $(SUB_DIRS)

$(SUB_DIRS):
	@$(MAKE) -C $@ $(TARGET) $(QUIET)

clean:
	@$(MAKE) TARGET=clean $(QUIET)

install:
	@$(MAKE) TARGET=install $(QUIET)
#	$(HIDE)mkdir -p $(SDK_ROOT)/bin
