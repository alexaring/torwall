# Basic Makefile for torwalltray

AM_CFLAGS=-Wall -g \
            `pkg-config --cflags gtk+-2.0 libnotify` \
            -Iinclude -DCONFDIR=$(sysconfdir)
AM_LDFLAGS=`pkg-config --libs gtk+-2.0 libnotify`

bin_PROGRAMS = torwalld torwalltray
torwalld_SOURCES=src/tdaemon.c src/socket.c src/torlog.c src/list.c src/iptables.c src/file_config.c src/tor_cmd.c src/file_torexits.c \
                   src/torlog.h \
				   src/list.h \
				   src/iptables.h \
				   src/netapi.h \
                   src/socket.h \
				   src/file_config.h \
				   src/tor_cmd.h \
				   src/file_torexits.h

torwalltray_SOURCES=src/torwalltray.c src/notify.c src/menu.c src/tray.c src/socket_client.c src/torlog.c \
                   src/torwalltray.h \
				   src/tray.h \
				   src/notify.h \
				   src/socket_client.h \
				   src/torlog.h \
				   src/menu.h

dist_noinst_SCRIPTS = autogen.sh

Torwallconfigdir= $(sysconfdir)/torwall
Torwallconfig_DATA = config/torwallrc config/torrules config/resolv.conf
Torwalliptablesdir= $(sysconfdir)/torwall/iptables
Torwalliptables_DATA = config/README 

Pixmapsdir = $(datadir)/pixmaps
Pixmaps_DATA = pixmaps/torwallActive.png pixmaps/torwallInactive.png pixmaps/de_on.png pixmaps/de.png pixmaps/us.png pixmaps/us_on.png pixmaps/about.png pixmaps/exit.png pixmaps/exitnodes.png pixmaps/preferences.png
