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
 * @brief   Shared definitions for the dssd-osd kernel module.
 */

#ifndef _DSSD_OSD_H_
#define _DSSD_OSD_H_

#include <linux/version.h>
#include <linux/dmi.h>

#ifdef RHEL_RELEASE_CODE
#define DSSD_OSD_OS_RHEL		1
#define DSSD_OSD_OS_RELEASE_VERSION(X, Y)	RHEL_RELEASE_VERSION((X), (Y))
#else
#define DSSD_OSD_OS_RHEL		0
#define DSSD_OSD_OS_RELEASE_VERSION(X, Y)	0
#endif /* RHEL_RELEASE_CODE */

#ifndef KMOD_OSD_ENABLED
#define OSD(F)	F
#else
#define OSD(F)	dssd_osd_ ## F


/*
 * blkdev
 */

#ifdef _LINUX_BLKDEV_H

extern void dssd_osd_blk_queue_flush(struct request_queue *q, unsigned int flush);

extern void dssd_osd_part_round_stats(int cpu, struct hd_struct *part);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,76)
extern void dssd_osd_trace_block_bio_complete(struct request_queue *q, struct bio *bio, int rc);
#else
extern void dssd_osd_trace_block_bio_complete(struct request_queue *q, struct bio *bio);
#endif

#endif /* _LINUX_BLKDEV_H */

/*
 * class/device
 */

#define __class_create(owner, name, key)	dssd_osd__class_create(owner, name, key)

extern struct class * __must_check dssd_osd__class_create(struct module *owner, const char *name, struct lock_class_key *key);

extern void dssd_osd_class_destroy(struct class *cls);

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 9, 0)
extern struct device *dssd_osd_class_find_device(struct class *class, struct device *start, void *data, int (*match)(struct device *, void *));
#else
extern struct device *dssd_osd_class_find_device(struct class *class, struct device *start, const void *data, int (*match)(struct device *, const void *));
#endif

extern struct device *dssd_osd_device_create(struct class *cls, struct device *parent, dev_t devt, void *drvdata, const char *fmt, ...) __attribute__((__format__(__printf__, 5, 6)));

extern int __must_check dssd_osd_device_create_file(struct device *device, struct device_attribute *entry);

extern void dssd_osd_device_destroy(struct class *cls, dev_t devt);

extern void dssd_osd_device_remove_file(struct device *dev, struct device_attribute *attr);

extern void dssd_osd_put_device(struct device *dev);

/*
 * eventfd
 */

extern struct eventfd_ctx *dssd_osd_eventfd_ctx_fdget(int fd);

extern void dssd_osd_eventfd_ctx_put(struct eventfd_ctx *ctx);

extern int dssd_osd_eventfd_signal(struct eventfd_ctx *ctx, int n);

/*
 * interrupt
 */

extern int dssd_osd_irq_set_affinity_hint(unsigned int irq, const struct cpumask *m);

/*
 * iommu
 */

#ifdef __LINUX_IOMMU_H

extern int dssd_osd_iommu_attach_device(struct iommu_domain *domain, struct device *dev);

extern void dssd_osd_iommu_detach_device(struct iommu_domain *domain, struct device *dev);

extern struct iommu_domain *dssd_osd_iommu_domain_alloc(void);

extern void dssd_osd_iommu_domain_free(struct iommu_domain *domain);

extern int dssd_osd_iommu_domain_has_cap(struct iommu_domain *domain, unsigned long cap);

extern bool dssd_osd_iommu_found(void);

extern phys_addr_t dssd_osd_iommu_iova_to_phys(struct iommu_domain *domain, unsigned long iova);

extern int dssd_osd_iommu_map(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, int gfp_order, int prot);

extern int dssd_osd_iommu_map_range(struct iommu_domain *domain, unsigned long iova, phys_addr_t paddr, size_t size, int prot);

extern int dssd_osd_iommu_unmap(struct iommu_domain *domain, unsigned long iova, int gfp_order);

extern void dssd_osd_iommu_unmap_range(struct iommu_domain *domain, unsigned long iova, size_t size);

#endif /* __LINUX_IOMMU_H */

/*
 * keys
 */

#ifdef _LINUX_KEY_H

extern void dssd_osd_user_describe(const struct key *key, struct seq_file *m);

extern int dssd_osd_user_match(const struct key *key, const void *description);

extern int dssd_osd_key_validate(struct key *key);

extern void dssd_osd_key_revoke(struct key *key);

#endif /* _LINUX_KEY_H */

/*
 * mm
 */

extern int dssd_osd_get_user_pages_fast(unsigned long start, int nr_pages, int write, struct page **pages);

extern pgprot_t dssd_osd_pgprot_writecombine(pgprot_t prot);

/*
 * pci/aer
 */

#ifdef LINUX_PCI_H

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 16, 0) && \
    (!DSSD_OSD_OS_RHEL || \
    (RHEL_RELEASE_CODE < DSSD_OSD_OS_RELEASE_VERSION(7, 2)))
extern int __must_check dssd_osd_pci_bus_add_device(struct pci_dev *dev);
#else
extern void dssd_osd_pci_bus_add_device(struct pci_dev *dev);
#endif

extern int dssd_osd_pci_cleanup_aer_uncorrect_error_status(struct pci_dev *dev);

extern int dssd_osd_pci_find_ext_capability(struct pci_dev *dev, int cap);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 33) && defined(RHEL_RELEASE_CODE)
extern int dssd_osd_pci_pcie_cap(struct pci_dev *dev);
#else
#define dssd_osd_pci_pcie_cap pci_pcie_cap
#endif

#endif /* LINUX_PCI_H */

/*
 * percpu
 */

#define __alloc_percpu(size, align)	dssd_osd__alloc_percpu(size, align)

extern void __percpu *dssd_osd__alloc_percpu(size_t size, size_t align);

extern void dssd_osd_free_percpu(void __percpu *__pdata);

/*
 * rcupdate
 */

extern void dssd_osd_synchronize_rcu(void);

/*
 * sched
 */

extern int dssd_osd_set_cpus_allowed_ptr(struct task_struct *p, const struct cpumask *new_mask);
extern int dssd_osd_flush_work(struct work_struct *work);

/*
 * dmi
 */

extern int dssd_osd_dmi_walk(void (*decode)(const struct dmi_header *, void *),
    void *private_data);

#endif /* KMOD_OSD_ENABLED */
#endif /* _DSSD_OSD_H_ */
