ifndef sources
	sources := $(wildcard *.c *.S)
ifneq ($(HIDE),@)
	test := $(warning sources not defined, by default use sources = $(sources) instead.)
endif
endif

ifndef program
	program := $(notdir $(CURDIR))
ifneq ($(HIDE),@)
	test := $(warning program not defined, by default use program = $(library) instead.)
endif
endif

OBJS := $(subst .c,.o, $(filter %.c, $(sources))) \
		$(subst .S,.o, $(filter %.S, $(sources))) 

DEPS :=  $(subst .c,.d, $(filter %.c, $(sources))) \
		 $(subst .S,.d, $(filter %.S, $(sources))) 

program_full := $(PROJECT_DIR)/bin/$(program)

include_dirs := . $(PROJECT_DIR)/include $(PROJECT_DIR)/include/IL $(PROJECT_DIR)/include/AL $(PREFIX)/include $(EXTINC)
library_dirs := $(PROJECT_DIR)/lib $(PREFIX)/lib

CFLAGS += -fPIC -Wall $(addprefix -I, $(include_dirs))
LDFLAGS += -fPIC -Wall $(addprefix -L, $(library_dirs)) $(addprefix -l, $(DEPLIBS))

make-dir = $(if $(wildcard $1), , $(MKDIR) -p $1)

ifndef INSTALL_DIR
INSTALL_DIR = $(PREFIX)/bin
endif

.PHONY:program
program:$(program_full)

$(program_full):$(OBJS)
	$(HIDE)$(call make-dir, $(dir $@))
	$(HIDE)$(CC) $(LDFLAGS) -o $@ $^

.PHONY:clean
clean:
	$(HIDE)$(RM) $(OBJS) $(program_full)

ifneq "$(MAKECMDGOALS)" "clean"
	-include $(DEPS)
endif

install:$(program_full)
	$(HIDE)$(call make-dir, $(INSTALL_DIR))
#$(HIDE)$(CP) $(program_full) $(INSTALL_DIR)/.

.c.o:
	$(HIDE)$(CC) $(CFLAGS) -c -o $@ $<
