make clean

make

sudo ifdown usb0
sudo ifup usb0

scp psoc_spimod.ko hotplug_psoc_spi_device.ko insmodSpiPSoC.sh rmmodSpiPSoC.sh testspi root@10.9.8.2:
scp *service root@10.9.8.2:
ssh root@10.9.8.2 'mv *.service /etc/systemd/system; systemctl enable Semesterprojekt3.service'