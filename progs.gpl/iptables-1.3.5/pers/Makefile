#! /usr/bin/make 

ifdef ELBOX_PROGS_GPL_IPPERSONALITY

EXTRA_INSTALLS+=$(DESTDIR)$(LIBDIR)/iptables/libipt_PERS.so
PERSOBJ=pers/pers_asm_sh.o pers/pers_tab_sh.o pers/pers_yy_sh.o
EXTRAS+=$(PERSOBJ) pers/libipt_PERS.so pers/libipt_PERS_sh.o\
        pers/pers_yy.c pers/pers_tab.c pers/pers_tab.h \
        pers/perscc.o pers/perscc
LEX=flex
LEXFLAGS=
YACC=bison
YACCFLAGS=-d

ifndef TOPLEVEL_INCLUDED
local:
	cd .. && $(MAKE) $(SHARED_LIBS)
endif

$(DESTDIR)$(LIBDIR)/iptables/libipt_PERS.so: pers/libipt_PERS.so
	@[ -d $(DESTDIR)$(LIBDIR)/iptables ] || mkdir -p $(DESTDIR)$(LIBDIR)/iptables
	cp $< $@

pers/perscc: pers/perscc.o $(PERSOBJ)

pers/pers_tab.h: pers/pers_tab.c
pers/pers_tab.c: pers/pers.y pers/pers.h
	$(YACC) $(YACCFLAGS) -o $@ $<

pers/pers_yy.c: pers/pers.l
	$(LEX) $(LEXFLAGS) -o$@ $<

pers/pers_yy.o: pers/pers_yy.c pers/pers.h pers/pers_tab.h
pers/pers_tab.o: pers/pers_tab.c pers/pers_tab.h pers/pers.h

pers/libipt_PERS.so: pers/libipt_PERS_sh.o $(PERSOBJ)
	$(LD) -shared -o $@ $< $(PERSOBJ)
endif
