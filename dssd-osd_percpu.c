/**
 * Copyright 2015 DSSD, Inc.
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
 * @brief   dssd_osd kernel module: percpu-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/percpu.h>

/*
 * Exported functions.
 */

void __percpu *
dssd_osd__alloc_percpu(size_t size, size_t align)
{
    return (__alloc_percpu(size, align));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd__alloc_percpu);

void
dssd_osd_free_percpu(void __percpu *__pdata)
{
    free_percpu(__pdata);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_free_percpu);
