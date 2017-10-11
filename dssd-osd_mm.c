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
 * @brief   dssd_osd kernel module: mm-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/mm.h>

/*
 * Exported functions.
 */

int
dssd_osd_get_user_pages_fast(unsigned long start, int nr_pages, int write,
    struct page **pages)
{
    return (get_user_pages_fast(start, nr_pages, write, pages));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_get_user_pages_fast);

pgprot_t
dssd_osd_pgprot_writecombine(pgprot_t prot)
{
    return (pgprot_writecombine(prot));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_pgprot_writecombine);
