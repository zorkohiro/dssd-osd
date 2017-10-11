#
# Copyright 2015 DSSD, Inc.
# This file is part of the dssd-osd kernel module.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
# Makefile to build common OS compatibility kernel module.
#

MODULE          := dssd-osd
BUILD_CLASS     := client client-kmod
SRCS            := dssd-osd_mod.c

ifeq ($(KMOD_OSD_ENABLED),1)
SRCS            +=	\
	dssd-osd_blkdev.c	\
	dssd-osd_device.c	\
	dssd-osd_dmi.c		\
	dssd-osd_eventfd.c	\
	dssd-osd_interrupt.c	\
	dssd-osd_iommu.c	\
	dssd-osd_keys.c	\
	dssd-osd_mm.c		\
	dssd-osd_pci.c		\
	dssd-osd_percpu.c	\
	dssd-osd_rcupdate.c	\
	dssd-osd_sched.c
endif

#
# Common compatibility layer KMOD
ifeq ($(KMOD_OSD_ENABLED),1)
EXTRA_CFLAGS   += -DKMOD_OSD_ENABLED
endif

#
# Extra kernel module compile-time flags
EXTRA_CFLAGS    += $(CFLAGS_KMOD) -I$(PWD)/$(SRCDIR)/include

#
# Required build arguments for modules in the Linux kernel tree:
obj-m           += $(MODULE).o
$(MODULE)-objs  := $(patsubst %.c,$(OBJDIR)/%.o,$(SRCS))

#
# Include the DSSD make system if this Makefile is included from
# the DSSD tree (it is also included from the Linux kernel tree).
UP              ?= ..
ifneq ($(wildcard $(UP)/Makefile.build), )
include $(UP)/Makefile.build
endif
