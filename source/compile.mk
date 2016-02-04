ifndef PLATFORM
PLATFORM := linux
endif

ifeq ($(PLATFORM),linux)
	CROSS_COMPILE := 
else
	test := $(error PLATFORM $(PALTFORM) not support.)
endif

ifeq ("$(origin V)", "command line")
	KBUILD_VERBOSE = $(V)
endif
ifndef KBUILD_VERBOSE
	KBUILD_VERBOSE = 0
endif


CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
MV := mv -f
RM := rm -f
CP := cp -rf
SED := sed
MKDIR := mkdir
HIDE := $(if $(KBUILD_VERBOSE:1=),@)
QUIET := $(if $(KBUILD_VERBOSE:1=),-s)

ifndef SDK_ROOT
	test := $(error SDK_ROOT not defined.)
endif

ifndef SDK_ROOT
	test := $(error SDK_ROOTFS not defined.)
endif

PREFIX := $(SDK_ROOT)/output
LIB_DIR := $(SDK_ROOT)/output
CFLAGS += -O2
#LDFLAGS += -EL
