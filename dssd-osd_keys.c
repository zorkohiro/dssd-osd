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
 * @brief   dssd_osd kernel module: mm-related functions.
 */

#include <include/dssd-osd_common.h>

/*
 * Includes specific to this file.
 */

#include <keys/user-type.h>

/*
 * Exported functions.
 */

void
dssd_osd_user_describe(const struct key *key, struct seq_file *m)
{
    user_describe(key, m);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_user_describe);

int
dssd_osd_user_match(const struct key *key, const void *description)
{
    return (user_match(key, description));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_user_match);

int
dssd_osd_key_validate(struct key *key)
{
    return (key_validate(key));
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_key_validate);

void
dssd_osd_key_revoke(struct key *key)
{
    key_revoke(key);
}
DSSD_OSD_EXPORT_SYMBOL(dssd_osd_key_revoke);
