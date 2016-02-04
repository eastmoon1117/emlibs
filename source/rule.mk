PROJECT_DIR := $(LIB_DIR)

ifndef sources
	sources := $(wildcard *.c *.S)

ifneq ($(HIDE),@)
	test := $(warning sources not defined, by default use sources = $(sources) instead.)
endif

endif

ifndef library
	library := libem$(notdir $(CURDIR)).so

ifneq ($(HIDE),@)
	test := $(warning library not defined, by default use library = $(library) instead.)
endif

endif

OBJS := $(subst .c,.o, $(filter %.c, $(sources))) \
		$(subst .S,.o, $(filter %.S, $(sources))) 

DEPS :=  $(subst .c,.d, $(filter %.c, $(sources))) \
		 $(subst .S,.d, $(filter %.S, $(sources))) 

library_full := $(PROJECT_DIR)/lib/$(library)

include_dirs := $(PROJECT_DIR)/include $(PROJECT_DIR)/src/inc . $(EXTINC)
library_dirs := $(PROJECT_DIR)/lib

CFLAGS += -fPIC -Wall $(addprefix -I, $(include_dirs))
LDFLAGS += -fPIC -Wall -shared -lpthread $(addprefix -L, $(library_dirs)) $(addprefix -lsl, $(DEPLIBS))

make-dir = $(if $(wildcard $1), , $(MKDIR) -p $1)

ifndef INSTALL_DIR
INSTALL_DIR = $(PREFIX)/lib
endif

.PHONY:library
library:$(library_full)

$(library_full):$(OBJS)
	$(HIDE)$(call make-dir, $(dir $@))
	$(HIDE)$(CC) $(LDFLAGS) -o $@ $^

.PHONY:clean
clean:
	$(HIDE)$(RM) $(OBJS) $(library_full)

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(DEPS)
endif

install:$(library_full)
	$(HIDE)$(call make-dir, $(INSTALL_DIR))
#$(HIDE)$(CP) $(library_full) $(INSTALL_DIR)/.

.c.o:
	$(HIDE)$(CC) $(CFLAGS) -c -o $@ $<
