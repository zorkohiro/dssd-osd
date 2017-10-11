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
 * @brief   Basic module entry/exit functions of dssd_osd kernel module.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#ifndef MODULE_NAME
#define MODULE_NAME     "dssd-osd"
#endif /* MODULE_NAME */

#ifndef VP_VENDOR
#define VP_VENDOR       "distributed"
#endif /* VP_VENDOR */

#ifndef VP_VERSION
#define VP_VERSION      "distributed"
#endif /* VP_VERSION */

/**
 * dssd_osd_mod_init() handles module initialization upon load
 *
 * This function requires no arguments.
 *
 * @return      0 = Module successfully initialized.
 * @return      !0 = Module initialization failure occurred..
 */
static int __init
dssd_osd_mod_init(void)
{
    printk(KERN_INFO "%s mod built %s %s %s\n", MODULE_NAME,
           BUILD_DATE, BUILD_TIME, VP_VERSION);

    return (0);
}

/**
 * dssd_osd_mod_init() handles module termination upon removal
 *
 * This function requires no arguments.
 *
 * @return      None.
 */
static void __exit
dssd_osd_mod_exit(void)
{
    printk(KERN_INFO "%s mod exit\n", MODULE_NAME);
}

/* Linux kernel module declarations. */
module_init(dssd_osd_mod_init);
module_exit(dssd_osd_mod_exit);
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR(VP_VENDOR);
MODULE_DESCRIPTION("DSSD OSD");
MODULE_VERSION(VP_VERSION);
