	
	sed -f sed_samba-3.0.8_script config.h > config.1
	sed 's/\#define HAVE_CHFLAGS 1/\#undef HAVE_CHFLAGS/' config.1 > config.h
##	sed 's/\/\* #undef HAVE_KERNEL_OPLOCKS_LINUX \*\//\#define HAVE_KERNEL_OPLOCKS_LINUX 1/' config.h > config.1
##	mv -f config.1 config.h 	
	