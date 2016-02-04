include compile.mk

SUB_DIRS = list  \
		   hashmap \
	
.PHONY: all $(SUB_DIRS)
all: $(SUB_DIRS)

$(SUB_DIRS):
	@$(MAKE) -C $@ $(TARGET) $(QUIET)

clean:
	@$(MAKE) TARGET=clean $(QUIET)

install:
	@$(MAKE) TARGET=install $(QUIET)
