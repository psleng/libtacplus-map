###########################################################################
##
## Copyright 2014, 2015, 2016 Cumulus Networks, Inc.  All rights reserved.
## Author: Dave Olson <olson@cumulusnetworks.com>
##
###########################################################################

ACLOCAL_AMFLAGS = -I config
AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libtacplus_map.la

libtacplus_map_la_SOURCES = map_tacplus_user.h  \
	map_tacplus_user.c
libtacplus_map_la_CFLAGS = $(AM_CFLAGS) -Ilibtac/include -Wno-error=address -Wno-error=stringop-truncation
libtacplus_map_la_LDFLAGS = -version-info 1:0:0 -shared -Wl,--no-undefined
libtacplus_map_la_LIBADD = -L.libs -laudit

libtacplus_map_includedir = $(oldincludedir)/tacplus

libtacplus_map_include_HEADERS = \
	map_tacplus_user.h

MAINTAINERCLEANFILES = Makefile.in config.h.in configure aclocal.m4 \
                       config/config.guess  config/config.sub  config/depcomp \
                       config/install-sh config/ltmain.sh config/missing

clean-generic:
	rm -rf autom4te*.cache
	rm -f *.rej *.orig *.lang dumpmap

sudoersd = $(DESTDIR)$(sysconfdir)/sudoers.d
install-data-hook:
	$(mkinstalldirs) $(sudoersd)
	${INSTALL} -m 644 tacplus.sudo $(sudoersd)/tacplus

# This is for debugging only, not normally built, and not installed
dumpmap: dumpmap.c map_tacplus_user.h
	$(CC) $(CFLAGS) $@.c -ltacplus_map -o $@
