# Basic Makefile for torwalltray

AM_CFLAGS=-Wall -g

bin_PROGRAMS = torwalldaemon
torwalldaemon_SOURCES=src/tdaemon.c src/socket.c src/torlog.c \
                   src/torlog.h \
                   src/socket.h

dist_noinst_SCRIPTS = autogen.sh

#Pixmapsdir = $(datadir)/pixmaps
#Pixmaps_DATA = torwallActive.png torwallInactive.png
