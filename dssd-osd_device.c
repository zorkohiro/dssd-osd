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
 * @brief   dssd_osd kernel module: device/class-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/device.h>
#include <linux/slab.h>

/*
 * Exported functions.
 */

struct class *
dssd_osd__class_create(struct module *owner, const char *name,
    struct lock_class_key *key)
{
    return (__class_create(owner, name, key));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd__class_create);

void
dssd_osd_class_destroy(struct class *cls)
{
    class_destroy(cls);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_class_destroy);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 9, 0)
struct device *
dssd_osd_class_find_device(struct class *class, struct device *start,
    void *data, int (*match)(struct device *, void *))
#else
struct device *
dssd_osd_class_find_device(struct class *class, struct device *start,
    const void *data, int (*match)(struct device *, const void *))
#endif
{
    return (class_find_device(class, start, data, match));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_class_find_device);

int __must_check
dssd_osd_device_create_file(struct device *device,
    struct device_attribute *entry)
{
    return (device_create_file(device, entry));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_device_create_file);

void
dssd_osd_device_destroy(struct class *class, dev_t devt)
{
    device_destroy(class, devt);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_device_destroy);

struct device *
dssd_osd_device_create(struct class *class, struct device *parent, dev_t devt,
    void *drvdata, const char *fmt, ...)
{
    va_list args;
    char *devname;
    struct device *dev = NULL;

    va_start(args, fmt);
    devname = kvasprintf(GFP_KERNEL, fmt, args);
    va_end(args);
    if (devname != NULL) {
        dev = device_create(class, parent, devt, drvdata, devname);
        kfree(devname);
    }
    return (dev);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_device_create);

void
dssd_osd_device_remove_file(struct device *dev, struct device_attribute *attr)
{
    device_remove_file(dev, attr);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_device_remove_file);

void
dssd_osd_put_device(struct device *dev)
{
    put_device(dev);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_put_device);
