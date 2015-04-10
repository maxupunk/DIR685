#!/bin/sh
# vi: set sw=4 ts=4:
cd defconfig
FILES=`ls *.config`
cd ..

MCFG="mconfig.in"

echo "mainmenu \"ELBOX Configuration\""				> $MCFG
echo "choice"										>> $MCFG
echo "	prompt \"Select Available Models\""			>> $MCFG
echo "	default ELBOX_MODEL_MANUAL"					>> $MCFG
echo ""												>> $MCFG
echo "	config ELBOX_MODEL_MANUAL"					>> $MCFG
echo "  bool \"Create Manually\""					>> $MCFG

for i in $FILES ; do
	MODEL=`echo $i | sed s/.config//`
	echo "	config ELBOX_$MODEL"					>> $MCFG
	echo "	bool $MODEL"							>> $MCFG
	echo ""											>> $MCFG
done

echo "endchoice"									>> $MCFG

for i in $FILES; do
	MODEL=`echo $i | sed s/.config//`
	echo "config ELBOX_DEFCONFIG"					>> $MCFG
	echo "depends ELBOX_$MODEL"						>> $MCFG
	echo "string"									>> $MCFG
	echo "default $i"								>> $MCFG
	echo ""											>> $MCFG
done

rm -f .config .config.cmd .tmpconfig.h selected.config
make -C config
./config/mconf $MCFG

if [ -f .config ] ; then
	source .config
	if [ -f defconfig/$ELBOX_DEFCONFIG ]; then
		cp defconfig/$ELBOX_DEFCONFIG ./selected.config
	fi
fi
rm -f .config .config.cmd .tmpconfig.h $MCFG
