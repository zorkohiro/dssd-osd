/**
 * Copyright 2016 DSSD, Inc.
 * This file is part of the dssd-osd kernel module.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @file
 * @brief   Common private definitions for the dssd-osd kernel module.
 */

#ifndef _DSSD_OSD_COMMON_H_
#define _DSSD_OSD_COMMON_H_

#include <linux/module.h>
#include <linux/version.h>

#ifdef KMOD_OSD_ENABLED
#define DSSD_OSD_EXPORT_SYMBOL(S)	EXPORT_SYMBOL(S)
#else
#define DSSD_OSD_EXPORT_SYMBOL(S)
#endif /* KMOD_OSD_ENABLED */

#ifdef RHEL_RELEASE_CODE
#define DSSD_OSD_OS_RHEL		1
#define DSSD_OSD_OS_RELEASE_VERSION(X, Y)	RHEL_RELEASE_VERSION((X), (Y))
#else
#define DSSD_OSD_OS_RHEL		0
#define DSSD_OSD_OS_RELEASE_VERSION(X, Y)	0
#endif /* RHEL_RELEASE_CODE */

#endif  // _DSSD_OSD_COMMON_H_
