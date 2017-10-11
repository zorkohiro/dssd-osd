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
 * @brief   dssd_osd kernel module: iommu-related functions.
 */

#include "include/dssd-osd_common.h"

/*
 * Includes specific to this file.
 */

#include <linux/iommu.h>
#include <linux/pci.h>

/*
 * Local macros.
 */

/*
 * EL 6.6 backported some later IOMMU kernel interfaces
 * so we cannot solely rely on kernel version below.
 */
#if defined(RHEL_RELEASE_CODE)
#if RHEL_RELEASE_CODE < RHEL_RELEASE_VERSION(6, 6)
#define RHEL_OLD_IOMMU  1
#else
#define RHEL_OLD_IOMMU  0
#endif
#else
#define RHEL_OLD_IOMMU  0
#endif

/*
 * Exported functions.
 */

int
dssd_osd_iommu_attach_device(struct iommu_domain *domain, struct device *dev)
{
    return (iommu_attach_device(domain, dev));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_attach_device);

void
dssd_osd_iommu_detach_device(struct iommu_domain *domain, struct device *dev)
{
    iommu_detach_device(domain, dev);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_detach_device);

struct iommu_domain *
dssd_osd_iommu_domain_alloc(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 2, 0)
    return (iommu_domain_alloc());
#else
    return (iommu_domain_alloc(&pci_bus_type));
#endif
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_domain_alloc);

void
dssd_osd_iommu_domain_free(struct iommu_domain *domain)
{
    iommu_domain_free(domain);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_domain_free);

#ifdef CONFIG_IOMMU_API    /* XXX is this ifdef necessary? */
int
dssd_osd_iommu_domain_has_cap(struct iommu_domain *domain, unsigned long cap)
{
    return (iommu_domain_has_cap(domain, cap));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_domain_has_cap);
#endif

bool
dssd_osd_iommu_found(void)
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 2, 0)
    return (iommu_found());
#else
    return (iommu_present(&pci_bus_type));
#endif
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_found);

phys_addr_t
dssd_osd_iommu_iova_to_phys(struct iommu_domain *domain, unsigned long iova)
{
    return (iommu_iova_to_phys(domain, iova));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_iova_to_phys);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35) && (RHEL_OLD_IOMMU == 1)
int
dssd_osd_iommu_map(struct iommu_domain *domain, unsigned long iova,
    phys_addr_t paddr, size_t size, int prot)
{
    return (iommu_map_range(domain, iova, paddr, size, prot));
}
#else
int
dssd_osd_iommu_map(struct iommu_domain *domain, unsigned long iova,
    phys_addr_t paddr, int gfp_order, int prot)
{
    return (iommu_map(domain, iova, paddr, gfp_order, prot));
}
#endif
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_map);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35)
int
dssd_osd_iommu_map_range(struct iommu_domain *domain, unsigned long iova,
    phys_addr_t paddr, size_t size, int prot)
{
    return (iommu_map_range(domain, iova, paddr, size, prot));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_map_range);
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35) && (RHEL_OLD_IOMMU == 1)
int
dssd_osd_iommu_unmap(struct iommu_domain *domain, unsigned long iova,
    size_t size)
{
    iommu_unmap_range(domain, iova, size);
    return (0);
}
#else
int
dssd_osd_iommu_unmap(struct iommu_domain *domain, unsigned long iova,
    int gfp_order)
{
    return (iommu_unmap(domain, iova, gfp_order));
}
#endif
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_unmap);

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35)
void
dssd_osd_iommu_unmap_range(struct iommu_domain *domain, unsigned long iova,
    size_t size)
{
    iommu_unmap_range(domain, iova, size);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_iommu_unmap_range);
#endif
