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
 * @brief   dssd_osd kernel module: pci/aer-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/pci.h>
#include <linux/aer.h>

/*
 * Exported functions.
 */

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0) && \
    (!DSSD_OSD_OS_RHEL || \
    (RHEL_RELEASE_CODE < DSSD_OSD_OS_RELEASE_VERSION(7, 2)))
int __must_check
dssd_osd_pci_bus_add_device(struct pci_dev *dev)
{
    return (pci_bus_add_device(dev));
}
#else
void
dssd_osd_pci_bus_add_device(struct pci_dev *dev)
{
    pci_bus_add_device(dev);
}
#endif
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_pci_bus_add_device);

int
dssd_osd_pci_cleanup_aer_uncorrect_error_status(struct pci_dev *dev)
{
    return (pci_cleanup_aer_uncorrect_error_status(dev));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_pci_cleanup_aer_uncorrect_error_status);

int
dssd_osd_pci_find_ext_capability(struct pci_dev *dev, int cap)
{
    return (pci_find_ext_capability(dev, cap));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_pci_find_ext_capability);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 33) && defined(RHEL_RELEASE_CODE)
int
dssd_osd_pci_pcie_cap(struct pci_dev *dev)
{
    return (pci_pcie_cap(dev));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_pci_pcie_cap);
#endif
