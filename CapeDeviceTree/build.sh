echo "Compiling the overlay from .dts to .dtbo"

dtc -O dtb -o GMETER-GPIO-00A0.dtbo -b 0 -@ GMETER-GPIO-00A0.dts

cp GMETER-GPIO-00A0.dtbo /lib/firmware/

echo GMETER-GPIO > $SLOTS

cat $SLOTS
