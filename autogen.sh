#!/bin/sh
# Taken from The Tor Project

set -e

# Run this to generate all the initial makefiles, etc.
aclocal && \
    autoheader && \
    autoconf && \
    automake --add-missing --copy
