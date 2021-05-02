/*
 * Copyright 2015, 2016, Cumulus Networks, Inc.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program - see the file COPYING.
 *
 * This program is for debugging, it dumps the map file contents.
 * Author: olson@cumulusnetworks.com>
 */

#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <libaudit.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <stdio.h>

#include "map_tacplus_user.h"


static const char *mapfile = MAP_TACPLUS_FILE;

int dump_mapfile(const char *fname)
{
    struct tacacs_mapping map;
    int fd, cnt, entry=0;

    fd = open(fname, O_RDONLY, 0600);
    if(fd == -1) {
	fprintf(stderr, "Can't open mapfile %s: %s\n", fname, strerror(errno));
	return 1;
    }

    while((cnt=read(fd, &map, sizeof map)) == sizeof map) {
	if (entry)
		putchar('\n');
	printf("Entry=%d: version=%d flags=0x%x, mapuid=%u, session=%u\n",
	       entry, map.tac_mapversion, map.tac_mapflags,
	       map.tac_mapuid, map.tac_session);
	printf("   ts=%lu.%06lu, logname=%s, mappedname=%s\n   rhost=%s\n",
	       map.tac_tv.tv_sec, map.tac_tv.tv_usec, map.tac_logname,
	       map.tac_mappedname, map.tac_rhost);
	entry++;
    }
    if (cnt == -1)
	fprintf(stderr, "Read error on mapfile %s: %s\n", fname,
		strerror(errno));
    else if (cnt)
	fprintf(stderr, "Short read of %d vs %d on mapfile %s\n", cnt,
		(int)sizeof map, fname);

    close(fd);
    return 0;
}

int main(int cnt, char **args)
{
	int ret;

	ret = dump_mapfile(mapfile);
	return ret;
}
