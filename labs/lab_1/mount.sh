#!/bin/bash

echo "1 - for mount, 2 - for unmount"
read option
if [[ $option = 1 ]]; then
sudo guestmount -a ~/Desktop/some/4_sem/APK/tools/virtual-machine/DOS2.vhd -m /dev/sda1 -w /mnt/DOS -o allow_other
exit
fi
sudo guestunmount /mnt/DOS/
exit
