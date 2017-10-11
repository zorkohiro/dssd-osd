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
 * @brief   dssd_osd kernel module: blkdev-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <linux/blkdev.h>
#include <trace/events/block.h>

/*
 * Exported functions.
 */

void
dssd_osd_blk_queue_flush(struct request_queue *q, unsigned int flush)
{
    blk_queue_flush(q, flush);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_blk_queue_flush);

void
dssd_osd_part_round_stats(int cpu, struct hd_struct *part)
{
    part_round_stats(cpu, part);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_part_round_stats);

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 76) || \
    defined(CONFIG_SUSE_KERNEL)
void
dssd_osd_trace_block_bio_complete(struct request_queue *q,
    struct bio *bio, int rc)
{
    trace_block_bio_complete(q, bio, rc);
}
#else
void
dssd_osd_trace_block_bio_complete(struct request_queue *q, struct bio *bio)
{
    trace_block_bio_complete(q, bio);
}
#endif
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_trace_block_bio_complete);
