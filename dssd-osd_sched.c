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
 * @brief   dssd_osd kernel module: sched-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/sched.h>
#include <linux/workqueue.h>

/*
 * Exported functions.
 */

int
dssd_osd_set_cpus_allowed_ptr(struct task_struct *p,
    const struct cpumask *new_mask)
{
    return (set_cpus_allowed_ptr(p, new_mask));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_set_cpus_allowed_ptr);

int
dssd_osd_flush_work(struct work_struct *work)
{
    return (flush_work(work));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_flush_work);
