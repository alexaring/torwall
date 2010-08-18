# Basic Makefile for torwalltray

AM_CFLAGS=-Wall -g \
            `pkg-config --cflags gtk+-2.0 libnotify` \
            -Iinclude
AM_LDFLAGS=`pkg-config --libs gtk+-2.0 libnotify`

bin_PROGRAMS = torwalldaemon torwalltray
torwalldaemon_SOURCES=src/tdaemon.c src/socket.c src/torlog.c src/list.c src/iptables.c \
                   src/torlog.h \
				   src/list.h \
				   src/iptables.h \
				   src/netapi.h \
                   src/socket.h

torwalltray_SOURCES=src/torwalltray.c src/notify.c src/menu.c src/tray.c src/socket_client.c \
                   src/torwalltray.h \
				   src/tray.h \
				   src/notify.h \
				   src/socket_client.h \
				   src/menu.h

dist_noinst_SCRIPTS = autogen.sh

Pixmapsdir = $(datadir)/pixmaps
Pixmaps_DATA = torwallActive.png torwallInactive.png
