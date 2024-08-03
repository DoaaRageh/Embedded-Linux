# BusyBox with Inittab
Integrate BusyBox with inittab to manage system boot and initialization effectively within the QEMU virtual environment.

## Install BusyBox
**Clone the BusyBox Repository**
```
git clone https://github.com/mirror/busybox.git
```
**Navigate to the BusyBox Directory**
```
cd busybox/
```
**Set the cross compiler into the environment**
```
export CROSS_COMPILE=~/x-tools/arm-cortexa9_neon-linux-musleabihf/bin/arm-cortexa9_neon-linux-musleabihf-
```
**Set the ARCH environment variable to arm**
```
export ARCH=arm
```
It specifies that the build process should target the ARM architecture.

**Customize the Configuration**

```
make menuconfig
```
- Configure busybox to be static build  
Go to **Settings**, and select **Build static binary** by pressing **Space**.
![Screenshot from 2024-07-29 16-56-57](https://github.com/user-attachments/assets/bb55bd54-baa3-4e27-ae40-6c8dc400add7)

**Build the BusyBox**
```
 make
 ```

**Generate the rootfs**
```
make install
```
This will create folder named _install which has all binaries


##  Create the rootfs
**Go out from BusyBox directory**
```
cd ..
```
**create rootfs directory**
```
mkdir rootfs
```
**Copy the content inside the _install into rootfs**
```
cp -rp ~/busybox/_install/ ~/rootfs
```
**Navigate to the rootfs Directory**
```
cd rootfs
```
 **Create the rest directories for rootfs.**
```
mkdir dev proc sys etc boot root home mnt srv
```
**Mount rootfs**
Create init.d Directory Inside etc
```
mkdir etc/init.d
```
Create rcs Script
```
touch etc/init.d/rcs
```
- in rcs write script to Mount Essential System Filesystems during Boot
![Screenshot from 2024-07-31 11-44-00](https://github.com/user-attachments/assets/175cadee-b3da-410f-a97f-4155ce767998)

- Make the script executable
    ```
    chmod +x etc/init.d/rcs
    ```
**Create Inittab Script**
```
touch etc/inittab
```
Configure System Initialization and Process Management in inittab![Screenshot from 2024-07-31 12-05-32](https://github.com/user-attachments/assets/1932c3e8-4a99-47ba-9f9e-7ff565c18520)
-   The `rcs` script is executed during system startup to handle initial configuration tasks.
-   On the `ttyAMA0` console, a shell is started, but the system waits for user input before proceeding.
-   If the `init` process is restarted, the system will re-execute the `init` program to continue managing system initialization and process management.

**Change owner of rootfs directory**  
Set the owner to root to allow the Embedded Linux board to write and execute commands.
```
chown -R root:root ~/rootfs
```
**Copy the content of the rootfs directory into rootfs partition**
```
cp -rp ~/rootfs/* /media/doaa/rootfs
```
## Start QEMU
```
sudo qemu-system-arm -M vexpress-a9 -nographic -net nic -net tap,script=./tapScript -kernel u-boot -sd ~/sd.img
```
**Edit the bootcmd Environment Variable**
```
editenv bootcmd
fatload mmc 0:1 $kernel_addr_r zImage; fatload mmc 0:1 $fdt_addr_r vexpress-v2p-ca9.dtb; bootz $kernel_addr_r - $fdt_addr_r
```
Load the kernel image and device tree from the MMC into memory, then boot the kernel.

**Edit the bootargs Environment Variable**
```
editenv bootargs
console=ttyAMA0 root=/dev/mmcblk0p2 rootfstype=ext4 rw rootwait init=/sbin/init
```
Set kernel parameters to
- Use `ttyAMA0` for console output.
- Specify the root filesystem on `/dev/mmcblk0p2` with `ext4` type.
- Enable read-write access.
- Wait for the root filesystem to become available.
- Use `/sbin/init` as the initial program.

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

![Screenshot from 2024-08-03 17-00-30](https://github.com/user-attachments/assets/970136fe-b063-4005-9335-463ce53ef5ef)

![Screenshot from 2024-08-02 17-18-46](https://github.com/user-attachments/assets/ff80f6bf-586c-4350-8117-c2585b82d671)
