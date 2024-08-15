# Dual Boot System with Initramfs
Set up a dual boot system that lets users choose between **rootfs1** and **rootfs2** at boot time, using a custom initramfs and boot script to determine which root filesystem the kernel will load.

## Create the rootfs2 Partition
```
cfdisk sd.img
```
Resize the **rootfs1** partition to 412 MB, then create a new **rootfs2** partition with a size of 411 MB in the freed space.

![Screenshot from 2024-08-07 21-55-18](https://github.com/user-attachments/assets/a558e973-9cfe-4a62-a6ee-95cef064d727)

**Set Up Loop Device**
```
sudo losetup -f --show --partscan sd.img
```
![Screenshot from 2024-08-07 21-59-01](https://github.com/user-attachments/assets/b65ec5f4-7ffb-4476-9218-08a62c34da68)

**Format the rootfs partition**
```
sudo mkfs.ext4 -L rootfs2 /dev/loop20p3
```

## Create a Script to Manage Boot Selection
**Navigate to the Root Filesystem Directory and Create bootScript**
```
cd ~/rootfs
touch bootScript
vim bootScript
```
Inside the **bootScript**, write a Bash script that prompts the user to choose which root filesystem to boot from rootfs1 or rootfs2. Depending on the user's choice, the script mounts the selected root filesystem and switches the root to it using chroot.
```
#!/bin/bash

echo "Choose the root filesystem to boot:"
echo "1) rootfs1"
echo "2) rootfs2"
read -p "Enter choice: " choice

case "$choice" in
    1)
        mkdir -p /mnt/rootfs1
        mount -t ext4 /dev/mmcblk0p2 /mnt/rootfs1
        chroot /mnt/rootfs1
        ;;
    2)
        mkdir -p /mnt/rootfs2
        mount -t ext4 /dev/mmcblk0p3 /mnt/rootfs2
        chroot /mnt/rootfs2
        ;;
    *)
        echo "Invalid Option"
        ;;
esac
```
**Add the Script to the Init System**

Edit **rcS** to include the script so that it runs during startup.
```
vim etc/init.d/rcS
```
Add this line to run your script.
```
sh /bootScript
```
![Screenshot from 2024-08-15 21-26-29](https://github.com/user-attachments/assets/1cb2239b-0233-4525-9145-1dac96c57ec1)


## Copy Content to rootfs2 Partition
**Copy rootfs Content**
```
sudo cp -rp rootfs/* /media/doaa/rootfs2
```
**Create Identification Files**


Create a simple file in each root filesystem to identify which rootfs the kernel booted from.
```
touch /media/doaa/rootfs1/rootfs1
touch /media/doaa/rootfs2/rootfs2
```

## Create the Initramfs Image
Navigate to the **rootfs** directory and create a **cpio** archive.
```
cd ~/rootfs
find . | cpio -H newc -ov --owner root:root > ../initramfs.cpio
```
Compress the **cpio** archive using gzip.
```
cd ..
gzip initramfs.cpio
```
Use mkimage to create a U-Boot-compatible **initramfs** image.
```
mkimage -A arm -O linux -T ramdisk -d initramfs.cpio.gz uRamdisk
```
Copy the generated **uRamdisk** image to the boot partition.
```
cp uRamdisk /media/doaa/boot
```
## Start QEMU
```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./tapScript -kernel u-boot/u-boot -sd ~/sd.img
```
**Edit the bootcmd Environment Variable**
```
editenv bootcmd
fatload mmc 0:1 $kernel_addr_r zImage; fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; fatload mmc 0:1 $initramfs uRamdisk; bootz $kernel_addr_r $initramfs $fdt_addr_r
```
Load the kernel, device tree blob (DTB), and initramfs image, then boot the system.

**Edit the bootargs Environment Variable**
```
editenv bootargs
console=ttyAMA0  rdinit=/sbin/init
```
Set kernel parameters to:

- Use **ttyAMA0** for console output.
- Set **/sbin/init** as the initial program from the **initramfs** to handle the boot process.

**Save the Environment Variables**
```
saveenv
```
Save the changes to ensure they persist across reboots.

**Reboot QEMU**
```
reset
```
Restart QEMU to apply the changes.

![Screenshot from 2024-08-10 03-55-41](https://github.com/user-attachments/assets/aee44540-f0ae-439e-9b8d-4074188e4ca0)

![Screenshot from 2024-08-10 03-56-34](https://github.com/user-attachments/assets/cc4f32c0-3949-49f4-8528-92941b1f7246)

