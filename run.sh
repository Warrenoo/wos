#!/bin/bash

if (( $(id -u) != 0 ))
then
    echo "ERROR: This script must be run as root" 1>&2
    exit 1
fi
 
GRUBFILEDIR=./grub/boot/grub
IMAGE=myimage
LOOPDEV=$(losetup -f)
 
dd if=/dev/zero of=${IMAGE}.img bs=512 count=2880
 
if [[ -d ${IMAGE} ]]
then
    rm -rf ${IMAGE}
fi
mkdir -p ${IMAGE}/boot/grub
 
cp ${GRUBFILEDIR}/stage1 ${IMAGE}/boot/grub
cp ${GRUBFILEDIR}/stage2 ${IMAGE}/boot/grub
losetup ${LOOPDEV} ${IMAGE}.img
mke2fs ${LOOPDEV}
mount ${LOOPDEV} -o loop /mnt
chmod 777 /mnt
cp -aR ${IMAGE}/* /mnt
umount /mnt
 
cat <<EOF | grub --batch --device-map=/dev/null
device (fd0) ${LOOPDEV}
root (fd0)
setup (fd0)
quit
EOF
 
losetup -d ${LOOPDEV}
 
read -n1 -p "Use QEMU to boot the image (Y/N) "
echo
if [[ $REPLY = [yY] ]]
then
    qemu -fda ${IMAGE}.img -nographic
fi
 
exit 0
