# $Id: Makefile,v 1.1.1.1 2006/04/03 08:40:42 amos_lee Exp $
# Makefile for the Sun Boot PROM interface library under
# Linux.
#

lib-y := bootstr.o devmap.o devops.o init.o memory.o misc.o mp.o \
	 palloc.o ranges.o segment.o console.o printf.o tree.o

lib-$(CONFIG_SUN4) += sun4prom.o
