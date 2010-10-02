# Basic Makefile for torwalltray

AM_CFLAGS=-Wall -g \
            `pkg-config --cflags gtk+-2.0 libnotify` \
            -Iinclude -DCONFDIR=$(sysconfdir)
AM_LDFLAGS=`pkg-config --libs gtk+-2.0 libnotify`

bin_PROGRAMS = torwalld torwalltray
torwalld_SOURCES=tdaemon.c socket.c torlog.c list.c iptables.c file_config.c tor_cmd.c file_torexits.c utils.c \
					   torlog.h \
				   list.h \
				   iptables.h \
				   netapi.h \
                   socket.h \
				   file_config.h \
				   tor_cmd.h \
				   file_torexits.h \
                   utils.h \
                   config_defines.h

torwalltray_SOURCES=torwalltray.c notify.c menu.c tray.c socket_client.c torlog.c \
                   torwalltray.h \
				   tray.h \
				   notify.h \
				   socket_client.h \
				   torlog.h \
				   menu.h

Torwallconfigdir= $(sysconfdir)/torwall
Torwallconfig_DATA = ../config/torwallrc ../config/torrules ../config/resolv.conf
Torwalliptablesdir= $(sysconfdir)/torwall/iptables
Torwalliptables_DATA = ../config/README 

Pixmapsdir = $(datadir)/../pixmaps
Pixmaps_DATA = ../pixmaps/torwallActive.png ../pixmaps/torwallInactive.png ../pixmaps/de_on.png ../pixmaps/de.png ../pixmaps/us.png ../pixmaps/us_on.png ../pixmaps/about.png ../pixmaps/exit.png ../pixmaps/exitnodes.png ../pixmaps/preferences.png
