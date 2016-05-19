make clean

make

scp psoc_spimod.ko hotplug_psoc_spi_device.ko insmodSpiPSoC.sh rmmodSpiPSoC.sh spi_init.service Semesterprojekt3.service root@10.9.8.2:
ssh root@10.9.8.2 'mv *.service /etc/systemd/system; systemctl enable Semesterprojekt3.service'

make clean
